#pragma once
#include <string>
#include <map>

class TextLoader {
private:
    std::map<std::string,std::string>dicionario; // o dicionario é o cojunto da chave + tag.

public:
bool carregarArquivo(const std::string&caminho); // coloquei pra chave e outro pro valor.
std::string getTexto(const std::string&tag);

};