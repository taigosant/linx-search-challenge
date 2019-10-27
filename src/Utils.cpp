//
// Created by taigo on 10/27/19.
//

#include "../headers/Utils.hpp"

namespace StringUtils {


    inline static std::vector<std::string> split(std::string &toSplit, std::string &&delimiter) {
        std::string buffer = toSplit;
        std::vector<std::string> splitted;

        auto pos = std::string::npos;

        while ((pos = buffer.find(delimiter)) != std::string::npos) {
            splitted.emplace_back(buffer.substr(0, pos));
            buffer.erase(buffer.begin(), buffer.begin() + (pos + delimiter.size()));
        }

        if (!buffer.empty()) {
            splitted.emplace_back(buffer);
        }

        return splitted;
    }

    // remove todas as ocorrencias de 'toRemoveAll' em uma string
    inline static void purgeAll(std::string &str, const std::vector<char> &toRemoveAll) {
        for (char toRemove : toRemoveAll) {
            str.erase(std::remove(str.begin(), str.end(), toRemove), str.end());
        }
    }

    // Remove todas as ocorrências do `toRemove` da string
    inline static void purge(std::vector<std::string> &vec, const std::string& toRemove) {
        vec.erase(std::remove(vec.begin(), vec.end(), toRemove), vec.end());
    }

    // processa um documento e retorna uma lista de termos purificados
    std::vector<std::string> processDocument(std::string document) {
        std::transform(document.begin(), document.end(), document.begin(), ::tolower); // lower case
        StringUtils::purgeAll(document, StringUtils::UNDESIRED_CHARACTERS_VECTOR); // removendo ruido

        auto splitted = StringUtils::split(document, " "); // separando os termos por espaço

        for (auto &term : splitted) { // normaliza um termo: àgua -> agua
            formatter.normalize(term);
        }

        for (auto &stopword : StringUtils::STOPWORDS) { // removendo stopwords
            purge(splitted, stopword);
        }

        return splitted;
    }


}