#include "headers/Index.hpp"
int main() {
    Index::Index index;
    index.loadData("catalogo_produtos.json");
    index.calculateDocumentVectors();

    while (true) {
        std::string input;
        std::cout <<"\n" << "\e[1m" << "> Digite aqui sua consulta:" << "\e[0m ";
        std::getline(std::cin, input);
        if (input == ":quit") return 0;
        index.processQuery(input);
    }
}