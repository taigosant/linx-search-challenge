//
// Created by taigo on 10/26/19.
//
// 5787 produtos
#include <string>
#include <unordered_map>
#include <fstream>
#include <numeric>
#include <iostream>
#include <cmath>
#include <map>
#include <chrono>
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/error/en.h"
#include "Utils.hpp"


namespace Index {


    struct SimpleProduct { // estrutura para representar um produto
        std::string id;
        std::string name;

        explicit SimpleProduct(const std::string &id, const std::string &name) : id(id), name(name) {}
    };

    struct Candidate { // estrutura para representar um candidato no ranking
        double similarity;
        unsigned code;

        explicit Candidate(double similarity, unsigned int code) : similarity(similarity), code(code) {}
    };

    // estrutura da lista invertida: mapa(termo -> mapa(documento -> frequencia do termo no documento))
    typedef std::unordered_map<std::string, std::unordered_map<unsigned, unsigned>> InverseList;

    class Index { // classe com uma simples implementação de um processador de consultas baseado no modelo vetorial
    public:
        std::vector<SimpleProduct> productsList; // lista para armazenar
        std::unordered_map<std::string, unsigned> vocabulary; // mapa(termo -> indice do termo) -> {aviao: 1, macbook: 2, ...}
        InverseList inverseList; // lista invertida
        std::vector<std::vector<double>> documentVectors; // lista das representações vetoriais de cada documento
        std::vector<std::vector<std::string>> documentList; // lista de documentos com seus termos já processados

        Index() = default;
        // função responsavel por carregar o arquivo .json e montar o indice
        void loadData(const std::string &path);

        // idf = log (numero total de documentos) / (numero de documentos em que um termo aparece)
        double idf(std::string &term);

        // frequencia de um termo em um documento
        unsigned tf(std::string &term, unsigned doc);

        // monta o vocabulario e a lista invertida
        // @param idx : indice/codigo do documento
        // @param document: documento cru
        void emplaceDocumentOnIndex(unsigned idx, std::string &document);

        void calculateDocumentVectors();

        std::vector<double> calculateQueryVector(std::vector<std::string> &queryTerms);

        void calculatePartialSimilarity(std::vector<std::string> &queryTerms,
                                        std::vector<double> &queryVector,
                                        std::vector<Candidate> &ranking);

        void processQuery(std::string &query);
    };
}
