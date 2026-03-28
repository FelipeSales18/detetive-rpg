#include "../include/TextLoader.hpp"
#include <fstream>
#include <iostream>

std::string TextLoader::getTexto(const std::string& tag) {
    if(dicionario.count(tag) > 0) {
        std::string textoCru = dicionario[tag];
        return pintarLetra(textoCru); // Devolve o texto já formatado!
    }
    return "[ERRO]";
}

    bool TextLoader::carregarArquivo(const std::string&caminho){ // const significa que nao sera alterada
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
    std::string TextLoader::pintarLetra(std::string texto){
        size_t pNew = texto.find("[NEW]");

        if(pNew!= std::string::npos){
            texto.replace(pNew, 5, "\033[1;33m[NEW]\033[0m");

        }
        size_t pOver = texto.find("[GAME_OVER]");

        if(pOver != std::string::npos){
            texto.replace(pOver, 11, "\033[1;31m[GAME_OVER]\033[0m");

        }
        return texto;


    }
