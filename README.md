# linx-search-challenge

Repositório feito para o desafio técnico da Linx. Contém uma simples implementação de um processador de consultas baseado no Modelo Vetorial [[1]](https://en.wikipedia.org/wiki/Vector_space_model).
Projeto implementado em C++ 17 usando GCC 7.4 e CMake 3.15.
## Estrutura do repositório

```
linx-search-challenge
├── headers             // pasta que reune os headers do projeto
│   └── Index.hpp      
|        ...
├── src                 // pasta que reune os arquivos .cpp 
│   └── Index.cpp       
|        ...
├── libs                // bibliotecas utilizadas
│   ├── rapidjson       // biblioteca para tratar arquivos .json     
│   └── string          // biblioteca para normalizar strings
|
├── main.cpp                // arquivo principal
├── catalogo_produtos.json  // arquivo com os dados a serem indexados
├── CMakeLists.txt          // configurações para compilação
├── .gitignore              // arquivo gitignore 
└── README.md               // arquivo readme

```

## Execução 

Para compilar o projeto você precirá do CMake [[2]](Phttps://cmake.org/) instalado.
Para compilar bastar rodar os comandos:
```
cmake .
make
```

Após isso você poderá rodar o executável:
```
./processador
```

