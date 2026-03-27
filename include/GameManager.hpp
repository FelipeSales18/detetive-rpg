#pragma once
#include <cstdlib>
#include <string>
#include "TextLoader.hpp"

enum CenarioJogo{
    MAPA,
    DELEGACIA,
    HOSPITAL,
    CASA,
    CENA_DO_CRIME,
    BAR
};

class GameManager {
private:CenarioJogo cena;



private:
    bool isRunning;
    bool achouAgulha;
    bool pegouCracha;
    TextLoader leitor;
    
    // Funcoes internas que ajudam a organizar o codigo
    void printTypewriter(const std::string& text, int delay_ms);
    void exibirMenu();
    void processarEscolha(int escolha);


    void limpaTerminal();

    void exibirIntroducao();

    void menuMapa();
    void processarMapa(int escolha);

    void menuDelegacia();
    void processarDelegacia(int escolha);

    void menuHospital();
    void processarHospital(int escolha);

    void menuCasa();
    void processarCasa(int escolha);

    void menuCena();
    void processarCena(int escolha);

    void menuBar();
    void processarBar(int escolha);
    
public:
    GameManager(); // Construtor
    void iniciarInvestigacao(); // Funcao que a main vai chamar
};