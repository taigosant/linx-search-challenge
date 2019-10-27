//
// Created by taigo on 10/26/19.
//

#include <string>
#include <bits/unordered_map.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "../libs/rapidjson/include/rapidjson/document.h"
#include "../libs/rapidjson/include/rapidjson/error/en.h"

namespace Index {

    typedef std::unordered_map<std::string, std::vector<int>> InverseList;

    struct SimpleProduct {
        std::string id;
        std::string name;

        explicit SimpleProduct(const std::string &id, const std::string &name) : id(id), name(name) {}
    };

    class Index {
    public:
        std::vector<SimpleProduct> productsList;

        void loadData(const std::string &path) {
            std::ifstream ifs(path);
            std::string jsonStr;

            while (std::getline(ifs, jsonStr)) {
                rapidjson::Document currentJson;
                if (currentJson.Parse(jsonStr.c_str()).HasParseError()) {
                    throw "Erro ao ler json: " + std::string(GetParseError_En(currentJson.GetParseError()));
                }

                if (currentJson.HasMember("id") && currentJson.HasMember("name")){
                    std::string id =  currentJson["id"].GetString();
                    std::string name =  currentJson["name"].GetString();
                    this->productsList.emplace_back(SimpleProduct(id, name));
                }
            }
        }

        void head(){
            for (int i = 0; i < 5; ++i) {
                std::cout << this->productsList[i].id << " " << this->productsList[i].name << std::endl;
            }
        }
    };

}
