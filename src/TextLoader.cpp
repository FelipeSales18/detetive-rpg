#include "../include/TextLoader.hpp"
#include <fstream>
#include <iostream>

std::string TextLoader::getTexto(const std:: string&tag){
    if(dicionario.count(tag)> 0){
        return dicionario[tag]; // retorna o texto a tag da fala ex:[CORONEL]

    }
    return "[ERRO]";
}

    bool TextLoader::carregarArquivo(const std::string&caminho){
        std::ifstream arquivo(caminho);

        if(!arquivo.is_open()){
            std::cout<<"ERRO\n";
            return false;

        }
        std::string linha;

        while(std::getline(arquivo, linha)){
            if(linha.empty()){
                continue;

            }
            size_t posicaoFecha = linha.find("]");
            if(posicaoFecha != std::string::npos){ //npos significa um valor impossivel de acontecer
                std::string tag = linha.substr(0, posicaoFecha + 1); // ele vai recortar do dialogos.txt a tag [CORONEL]
                std::string texto = linha.substr(posicaoFecha + 2); // vai recortar a fala/texto 
                dicionario[tag] = texto; // a tag corresponde as texto ao lado
 
            }
            


        }

        
        arquivo.close();
        return true;


    }
