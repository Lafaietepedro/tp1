// apresentacao.h - Camada de apresentacao

#ifndef APRESENTACAO_H
#define APRESENTACAO_H

#include "interfaces.h"
#include <iostream>
#include <limits>

using namespace std;

// ========== CONTROLADORAS DE APRESENTACAO ==========

// Controladora de apresentacao de autenticacao
class ControladoraApresentacaoAutenticacao : public IApresentacaoAutenticacao {
private:
    IServicoAutenticacao* servicoAutenticacao;
    void exibirTelaLogin();
    void exibirTelaCriarConta();

public:
    ControladoraApresentacaoAutenticacao(IServicoAutenticacao*);
    bool executar(Email&) override;
};

// Controladora de apresentacao de gerente
class ControladoraApresentacaoGerente : public IApresentacaoGerente {
private:
    IServicoGerente* servicoGerente;
    void exibirMenu();
    void listarGerentes();
    void editarPerfil(const Email&);

public:
    ControladoraApresentacaoGerente(IServicoGerente*);
    void executar(const Email&) override;
};

// Controladora de apresentacao de hotel
class ControladoraApresentacaoHotel : public IApresentacaoHotel {
private:
    IServicoHotel* servicoHotel;
    void exibirMenu();
    void criarHotel(const Email&);
    void listarHoteis(const Email&);
    void editarHotel();
    void excluirHotel();

public:
    ControladoraApresentacaoHotel(IServicoHotel*);
    void executar(const Email&) override;
};

// Controladora de apresentacao de quarto
class ControladoraApresentacaoQuarto : public IApresentacaoQuarto {
private:
    IServicoQuarto* servicoQuarto;
    IServicoHotel* servicoHotel;
    void exibirMenu();
    void criarQuarto(const Email&);
    void listarQuartos(const Email&);
    void editarQuarto();
    void excluirQuarto();

public:
    ControladoraApresentacaoQuarto(IServicoQuarto*, IServicoHotel*);
    void executar(const Email&) override;
};

// Controladora de apresentacao de reserva
class ControladoraApresentacaoReserva : public IApresentacaoReserva {
private:
    IServicoReserva* servicoReserva;
    IServicoHotel* servicoHotel;
    IServicoQuarto* servicoQuarto;
    void exibirMenu();
    void criarReserva(const Email&);
    void listarReservas();
    void editarReserva();
    void excluirReserva();

public:
    ControladoraApresentacaoReserva(IServicoReserva*, IServicoHotel*, IServicoQuarto*);
    void executar(const Email&) override;
};

// Controladora de apresentacao de hospede
class ControladoraApresentacaoHospede : public IApresentacaoHospede {
private:
    IServicoHospede* servicoHospede;
    IServicoReserva* servicoReserva;
    void exibirMenu();
    void criarHospede();
    void listarHospedes();
    void editarHospede();
    void excluirHospede();

public:
    ControladoraApresentacaoHospede(IServicoHospede*, IServicoReserva*);
    void executar(const Email&) override;
};

// Funcoes auxiliares
void limparBuffer();
void pausar();
void limparTela();

#endif // APRESENTACAO_H
