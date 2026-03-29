#include "../include/GameManager.hpp"
#include <iostream>
#include <thread>
#include <chrono>

// O construtor define que o jogo comeca rodando
GameManager::GameManager() {
    isRunning = true;
    cena = PERSONAGENS;
    achouAgulha = false;
    pegouCracha = false;
    pegouDistintivo = false;
    pistaHospital = false;
    vida = 100;

    // carregando o arquivo de textos
    leitor.carregarArquivo("data/dialogos.txt");
}

// O efeito de digitacao letra por letra
void GameManager::printTypewriter(const std::string& text, int delay_ms) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    std::cout << '\n';
}
void GameManager::exibirIntroducao(){
    limpaTerminal();
    printTypewriter(leitor.getTexto("[INTRODUCAO_1]"),70);
    std::this_thread::sleep_for(std::chrono::seconds(1)); // da uma pausa pelos segundos escolidos antes de ler o proximo
    printTypewriter(leitor.getTexto("[INTRODUCAO_2]"),70);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printTypewriter(leitor.getTexto("[INTRODUCAO_3]"),70);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    printTypewriter(leitor.getTexto("[INTRODUCAO_4]"),70);

    std::cout << "\n(Pressione ENTER para ligar o carro e iniciar a investigacao...)\n";
    std::cin.ignore(); // tira qualquer coisa que alguem tenha pressionado
    std::cin.get(); // trava ate apertar enter

}

void GameManager::exibirPersonagens(){
    std::cout << "\n === CONHECA OS SEUS COLEGAS === \n";
    std::cout << "1. Coronel\n";
    std::cout << "2. Parceiro\n";
    std::cout << "3. Secretaria\n";
    std::cout << "4. Ir para cena do crime\n";

}
void GameManager::processarPersonagens(int escolha){
    if(escolha == 1){
        cena = PERSONAGENS;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[CORONEL_INTRODUCAO]"),50);
    }else if(escolha == 2){
        cena = PERSONAGENS;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[PARCEIRO_INTRODUCAO]"),50);

    }else if(escolha == 3){
        cena = PERSONAGENS;
        pegouDistintivo = true;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[SECRETARIA_INTRODUCAO]"),50);

    } else if (escolha == 4 && pegouDistintivo == true) {
        cena = CENA_DO_CRIME; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_CENA]"), 50);
    }else if(escolha == 4 && pegouDistintivo == false){
        cena = PERSONAGENS;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[PEGUE_CRACHA]"),50);

    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

void GameManager::vidaDetetive(){
    if(vida <= 0){
        printTypewriter(leitor.getTexto("[PERDEU]"),50);
        isRunning = false;

    }
}


void GameManager::exibirMenu() {
    switch (cena) {
        case PERSONAGENS: exibirPersonagens(); break;
        case MAPA: menuMapa();       break;
        case DELEGACIA: menuDelegacia();  break;
        case HOSPITAL: menuHospital(); break;
        case BAR: menuBar(); break;
        case CENA_DO_CRIME: menuCena(); break;
        case CASA: menuCasa(); break;
        default: break;
    }
}

void GameManager::processarEscolha(int escolha) {
    switch (cena) {
        case MAPA:      processarMapa(escolha);       break;
        case DELEGACIA: processarDelegacia(escolha);  break;
        case HOSPITAL: processarHospital(escolha); break;
        case BAR: processarBar(escolha); break;
        case CENA_DO_CRIME: processarCena(escolha); break;
        case CASA: processarCasa(escolha); break;
        case PERSONAGENS: processarPersonagens(escolha); break;
        default: break;
    }
}


void GameManager::menuMapa() {
    std::cout << "\n=== GPS DO CARRO: ONDE DESEJA IR? ===\n";
    std::cout << "1. Delegacia\n";
    std::cout << "2. Casa\n";
    std::cout << "3. Hospital\n";
    std::cout << "4. Cena do Crime\n";
    std::cout << "5. Bar\n";
    std::cout << "6. Sair do Carro\n";
}

void GameManager::processarMapa(int escolha) {
    if (escolha == 1) {
        cena = DELEGACIA;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_DELEGACIA]"), 50);
    } else if (escolha == 2) {
        cena = CASA;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_CASA]"), 50);
    } else if (escolha == 3 && pistaHospital == true) {
        cena = HOSPITAL;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_HOSPITAL]"), 50);
    } else if(escolha == 3 && pistaHospital == false){
        cena = MAPA;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[ACESSO_NEGADO]"),50);

    } else if (escolha == 4) {
        cena = CENA_DO_CRIME;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_CENA]"), 50);
    } else if (escolha == 5) {
        cena = BAR;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_BAR]"), 50);
    } else if (escolha == 6) {
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[MAPA_SAIR]"), 50);
        isRunning = false; 
    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

void GameManager::menuDelegacia(){
    std::cout << "\n === DELEGACIA DE POLICIA ===\n";
    std::cout << "1. Falar com o Coronel\n";
    std::cout << "2. Falar com seu Parceiro\n";
    std::cout << "3. Voltar para o carro\n";
}

void GameManager::processarDelegacia(int escolha) {
    if (escolha == 1) {
        cena = DELEGACIA;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[DELEGACIA_CORONEL]"), 50);
    } else if (escolha == 2) {
        cena = DELEGACIA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[DELEGACIA_PARCEIRO]"), 50);
    } else if (escolha == 3) {
        cena = MAPA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[GERAL_VOLTAR_CARRO]"), 50);
    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

void GameManager::menuHospital(){
    std::cout << "\n === HOSPITAL DA CIDADE ===\n";
    std::cout << "1. Perguntar pela testemunha. \n";
    std::cout << "2. Tentar entrar escondido e achar informaçoes \n";
    std::cout << "3. Voltar para o carro\n";
}

void GameManager::processarHospital(int escolha) {
    if (escolha == 1) {
        cena = HOSPITAL;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[HOSPITAL_SECRETARIA]"), 50);
    } else if (escolha == 2) {
        cena = HOSPITAL; 
        pegouCracha = true;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[HOSPITAL_CRACHA]"), 50);
    } else if (escolha == 3) {
        cena = MAPA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[GERAL_VOLTAR_CARRO]"), 50);
    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

void GameManager::menuCasa(){
    std::cout << "\n === CASA ===\n";
    std::cout << "1. Ver o Jornal.\n";
    std::cout << "2. Olhar pela janela.\n";
    std::cout << "3. Voltar para o carro\n";
}

void GameManager::processarCasa(int escolha) {
    if (escolha == 1) {
        cena = CASA;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[CASA_TV]"), 50);
    } else if (escolha == 2) {
        cena = CASA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[CASA_JANELA]"), 50);
    } else if (escolha == 3) {
        cena = MAPA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[GERAL_VOLTAR_CARRO]"), 50);
    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

void GameManager::menuCena(){
    std::cout << "\n === CENA DO CRIME===\n";
    std::cout << "1. Falar com o socorrista.\n";
    std::cout << "2. Falar com o seu parceiro.\n";
    std::cout << "3. Vasculhar o chao.\n";
    std::cout << "4. Voltar para o carro\n";
}

void GameManager::processarCena(int escolha) {
    if(escolha == 1){
        cena = CENA_DO_CRIME;
        pistaHospital = true;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[CENA_SOCORRISTA]"),50);

    } else if (escolha == 3) {
        cena = CENA_DO_CRIME;
        std::cout << '\n';
        achouAgulha = true;
        printTypewriter(leitor.getTexto("[CENA_CHAO]"), 50);
    } else if (escolha == 2) {
        cena = CENA_DO_CRIME; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[CENA_PARCEIRO]"), 50);
        vidaDetetive();
    } else if (escolha == 4) {
        cena = MAPA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[GERAL_VOLTAR_CARRO]"), 50);
    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

void GameManager::menuBar(){
    std::cout << "\n === BAR===\n";
    std::cout << "1. Intimidar o Barmen pra descobrir se a droga foi vendida no local.\n";
    std::cout << "2. Tentar persuadir o dono do bar a falar\n";
    std::cout << "3. Voltar para o carro\n";
}

void GameManager::processarBar(int escolha) {
    if (escolha == 1) {
        cena = BAR;
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[BAR_BARMEN_RUIM]"), 50);
    } else if (escolha == 2 && achouAgulha == true) {
        cena = BAR; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[BAR_BARMEN_BOM]"), 50);
    }else if(escolha == 2 && achouAgulha == false){
        cena = BAR;
        std::cout << "\n";
        printTypewriter(leitor.getTexto("[BAR_MEN_SEM_PISTA]"),50);

    } else if (escolha == 3) {
        cena = MAPA; 
        std::cout << '\n';
        printTypewriter(leitor.getTexto("[GERAL_VOLTAR_CARRO]"), 50);
    } else {
        std::cout << '\n' << leitor.getTexto("[GERAL_INVALIDO]") << '\n';
    }
}

// O coração do jogo


void GameManager::iniciarInvestigacao() {
    printTypewriter("Iniciando inicializacao do sistema...", 50);
    exibirIntroducao();
    
    while (isRunning) {
        exibirMenu();
        
        int escolha;
        std::cin >> escolha;
        
        // Tratamento de erro caso o jogador digite uma letra
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            escolha = 0; 
        }
        
        processarEscolha(escolha);
    }
}
void GameManager::limpaTerminal(){
            std::system("clear");
        }