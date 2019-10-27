//
// Created by taigo on 10/27/19.
//

#include "../headers/Index.hpp"

namespace Index {

    void Index::loadData(const std::string &path) { // função responsavel por carregar o arquivo .json e montar o indice
        std::cout << "Building inverse index" << std::endl;
        std::ifstream ifs(path);
        std::string jsonStr;
        unsigned numDocs = 0;

        if (!ifs.is_open()) {
            throw "Não foi possivel abrir o arquivo: " + path;
        }

        while (std::getline(ifs, jsonStr)) { // lendo cada  linha do arquivo e parseando o .json
            rapidjson::Document currentJson;

            if (currentJson.Parse(jsonStr.c_str()).HasParseError()) {
                throw "Erro ao ler json: " + std::string(GetParseError_En(currentJson.GetParseError()));
            }

            if (currentJson.HasMember("id") && currentJson.HasMember("name")) {
                std::string id = currentJson["id"].GetString();
                std::string name = currentJson["name"].GetString();
                this->productsList.emplace_back(SimpleProduct(id, name)); // armazena os dados originais do produto
                emplaceDocumentOnIndex(numDocs, name); // indexa o produto
                numDocs++;
            }
        }
        ifs.close();
    }

    // idf = log (numero total de documentos) / (numero de documentos em que um termo aparece)
    double Index::idf(std::string &term) {
        auto Ntf = static_cast<int>(this->inverseList[term].size()); // numero de documentos em que tal termo aparece
        if (Ntf > 0) return log(this->documentList.size() / Ntf);
        else return 0;
    }

    // frequencia de um termo em um documento
    unsigned Index::tf(std::string &term, unsigned doc) {
        std::unordered_map<unsigned, unsigned> &documentMap = this->inverseList[term];
        auto iter = documentMap.find(doc);
        // se encontrou retorna a frequencia, se não encontrou então a frequencia nao existe retorna 0
        return (iter != documentMap.end()) ? iter->second : 0;
    }

    // monta o vocabulario e a lista invertida
    // @param idx : indice/codigo do documento
    // @param document: documento cru
    void Index::emplaceDocumentOnIndex(unsigned idx, std::string &document) {

        auto processedTerms = StringUtils::processDocument(document);
        for (const auto &term : processedTerms) {
            // se o indice for diferente de 0 é pq já foi inserido, então o indice será mantido
            // se for igual a 0 então é um termo novo, insere e registra o indice conforme o tamanho atual do vocabulario
            this->vocabulary[term] = (this->vocabulary[term] > 0) ? this->vocabulary[term] :
                                     this->vocabulary.size() + 1;
            // recupera a lista de documentos do termo
            std::unordered_map<unsigned, unsigned> &documentMap = this->inverseList[term];
            // aumenta a frequencia do termo no documento correspondente ao 'idx'
            documentMap[idx]++;
        }

        this->documentList.emplace_back(processedTerms);
    }

    void Index::calculateDocumentVectors() {
        std::cout << "Building document vectors.. May take a while" << std::endl;
        auto len = this->vocabulary.size(); // tamanho do vocabulario
        for (unsigned i = 0; i < this->documentList.size(); i++) { // para cada documento
            auto *currentDocVec = static_cast<double *>(malloc(
                    len * sizeof(double))); // aloca um vetor do tamanho do vocabulario

            for (auto term : this->documentList[i]) { // para cada termo no documento

                double wordWeight = tf(term, i) * idf(term); // calcula o peso do termo
                auto termIndexOnVoc = this->vocabulary[term] - 1; // recupera o indice do termo
                currentDocVec[termIndexOnVoc] = wordWeight; // guarda no vetor do documento conforme o indice do vocabulario
            }
            // converte para vector para depois podermos usa-lo para fazer um produto interno
            std::vector<double> converted(currentDocVec, currentDocVec + len);
            this->documentVectors.push_back(converted);
        }
    }

    std::vector<double> Index::calculateQueryVector(std::vector<std::string> &queryTerms) {
        std::unordered_map<std::string, unsigned> freqMap;
        std::vector<double> queryVector(this->vocabulary.size(), 0.0); // aloca o vetor do consulta

        for (auto &term : queryTerms) { // monta o mapa de frequencias da string de consulta
            freqMap[term]++;
        }


        for (std::string &term : queryTerms) { // para cada termo na consulta, calcula o peso do respectivo termo

            auto it = this->vocabulary.find(term);

            if (it != this->vocabulary.end()) {
                double wD = idf(term) * freqMap[term];
                auto position = it->second;
                queryVector[position] = wD; // guarda o peso na posição correspondente do vocabulario
            }
        }
        return queryVector;
    }

    void Index::calculatePartialSimilarity(std::vector<std::string> &queryTerms,
                                           std::vector<double> &queryVector,
                                           std::vector<Candidate> &ranking) {

        for (std::string &word : queryTerms) { // para cada termo, recupera a lista invertida
            auto it = this->inverseList.find(word);

            if (it != this->inverseList.end()) {
                std::unordered_map<unsigned, unsigned> &documentInvList = it->second;

                for (auto[docDoce, freq] : documentInvList) { // calcula a similaridade para cada documento na lista invertida

                    auto &curDocVec = this->documentVectors[docDoce];
                    // produto interno entre os vetores da consulta e do documento
                    double innerProd = inner_product(curDocVec.begin(),
                                                     curDocVec.end(),
                                                     queryVector.begin(), 0.0);

                    auto lenDocument = double(this->documentList[docDoce].size());

                    double similarity = innerProd / lenDocument;

                    ranking.emplace_back(Candidate(similarity, docDoce));
                }
            }
        }
        // ordenando os candidatos
        std::sort(ranking.begin(), ranking.end(),
                  [](Candidate a, Candidate b) { return a.similarity > b.similarity; });
    }

    void Index::processQuery(std::string &query) {
        auto tBegin = std::chrono::high_resolution_clock::now();
        // processando a consulta
        auto queryTerms = StringUtils::processDocument(query);
        auto queryVec = calculateQueryVector(queryTerms);
        std::vector<Candidate> ranking;
        calculatePartialSimilarity(queryTerms, queryVec, ranking);
        // fim do processamento
        auto tEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = tEnd - tBegin;
        // imprimindo os resultados

        if (!ranking.empty()) {
            std::cout << "Tempo: " << elapsed.count() << " segundos" << std::endl;

            unsigned counter = 1;
            for (auto[sim, docId] : ranking) {
                std::cout.precision(3);
                std::cout << " #" << counter << " - " << this->productsList[docId].id << " - "
                          << this->productsList[docId].name << " | Score: " << sim << std::endl;
                counter++;
                if (counter > 20) return;
            }
        } else {
            std::cout << "Não encontrei nada relacionado a \"" << query << "\"" << std::endl;
        }
    }
};