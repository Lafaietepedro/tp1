// main.cpp - Programa principal

#include "apresentacao.h"
#include "servico.h"
#include <iostream>

using namespace std;

int main() {
    // Criar containers
    ContainerGerentes containerGerentes;
    ContainerHoteis containerHoteis;
    ContainerQuartos containerQuartos;
    ContainerReservas containerReservas;
    ContainerHospedes containerHospedes;
    
    // Criar controladoras de servico
    ControladoraServicoAutenticacao servicoAutenticacao(&containerGerentes);
    ControladoraServicoGerente servicoGerente(&containerGerentes);
    ControladoraServicoHotel servicoHotel(&containerHoteis, &containerQuartos);
    ControladoraServicoQuarto servicoQuarto(&containerQuartos, &containerReservas);
    ControladoraServicoReserva servicoReserva(&containerReservas, &containerHospedes);
    ControladoraServicoHospede servicoHospede(&containerHospedes);
    
    // Criar controladoras de apresentacao
    ControladoraApresentacaoAutenticacao apresentacaoAutenticacao(&servicoAutenticacao);
    ControladoraApresentacaoGerente apresentacaoGerente(&servicoGerente);
    ControladoraApresentacaoHotel apresentacaoHotel(&servicoHotel);
    ControladoraApresentacaoQuarto apresentacaoQuarto(&servicoQuarto, &servicoHotel);
    ControladoraApresentacaoReserva apresentacaoReserva(&servicoReserva, &servicoHotel, &servicoQuarto);
    ControladoraApresentacaoHospede apresentacaoHospede(&servicoHospede, &servicoReserva);
    
    // Autenticacao
    Email emailAutenticado;
    if (!apresentacaoAutenticacao.executar(emailAutenticado)) {
        cout << "Encerrando sistema..." << endl;
        return 0;
    }
    
    // Menu principal
    int opcao;
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  MENU PRINCIPAL" << endl;
        cout << "========================================" << endl;
        cout << "Logado como: " << emailAutenticado.get() << endl;
        cout << "========================================" << endl;
        cout << "1. Gerenciar Perfil" << endl;
        cout << "2. Gerenciar Hoteis" << endl;
        cout << "3. Gerenciar Quartos" << endl;
        cout << "4. Gerenciar Reservas" << endl;
        cout << "5. Gerenciar Hospedes" << endl;
        cout << "0. Sair" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            cout << "Encerrando sistema..." << endl;
            break;
        } else if (opcao == 1) {
            apresentacaoGerente.executar(emailAutenticado);
        } else if (opcao == 2) {
            apresentacaoHotel.executar(emailAutenticado);
        } else if (opcao == 3) {
            apresentacaoQuarto.executar(emailAutenticado);
        } else if (opcao == 4) {
            apresentacaoReserva.executar(emailAutenticado);
        } else if (opcao == 5) {
            apresentacaoHospede.executar(emailAutenticado);
        }
    }
    
    return 0;
}
