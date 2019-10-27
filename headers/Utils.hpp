//
// Created by taigo on 10/27/19.
//

#ifndef LINX_SEARCH_CHALLENGE_UTILS_H
#define LINX_SEARCH_CHALLENGE_UTILS_H

#include "../libs/string/libstring.h"


namespace StringUtils {

    inline StringFormatter formatter;

    inline const std::vector<char> UNDESIRED_CHARACTERS_VECTOR = {',', '.', '-', '\"', '\'', '`', '(', ')', '{', '}',
                                                                  '/', '\\',
                                                                  '@', ';'};

    inline static std::vector<std::string> split(std::string &toSplit, std::string &&delimiter);

    /// remove toda as ocorrências de caracteres de `toRemoveAll` na string `str`
    inline static void purgeAll(std::string &str, const std::vector<char> &toRemoveAll);

    inline static std::vector<std::string> processDocument(std::string document);
}

#endif //LINX_SEARCH_CHALLENGE_UTILS_H
