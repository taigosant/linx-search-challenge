//
// Created by taigo on 10/27/19.
//

#ifndef LINX_SEARCH_CHALLENGE_UTILS_HPP
#define LINX_SEARCH_CHALLENGE_UTILS_HPP

#include <vector>
#include <algorithm>
#include <set>
#include "../libs/string/libstring.h"


namespace StringUtils {

    inline static StringFormatter formatter;

    inline static std::set<std::string> STOPWORDS = {"de","a","o","que","e","do","da","em","um","para","com","uma","os","no","se","na","por","mais","as","dos","mas","ao","das","tem","ou"};

    inline static std::vector<char> UNDESIRED_CHARACTERS_VECTOR = {',', '.', '-', '\"', '\'', '`', '(', ')', '{', '}',
                                                                  '/', '\\',
                                                                  '@', ';'};

    inline static std::vector<std::string> split(std::string &toSplit, std::string &&delimiter);

    /// remove toda as ocorrências de caracteres de `toRemoveAll` na string `str`
    inline static void purgeAll(std::string &str, const std::vector<char> &toRemoveAll);

    inline static void purge(std::vector<std::string> &vec, const std::string& toRemove);

    std::vector<std::string> processDocument(std::string document);
}

#endif //LINX_SEARCH_CHALLENGE_UTILS_HPP
