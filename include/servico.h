// servico.h - Camada de servico

#ifndef SERVICO_H
#define SERVICO_H

#include "interfaces.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// ========== CONTAINERS ==========

// Container de gerentes
class ContainerGerentes {
private:
    vector<Gerente> gerentes;
    const string arquivo = "data/gerentes.txt";
    void salvar();
    void carregar();

public:
    ContainerGerentes();
    bool adicionar(const Gerente&);
    bool buscar(const Email&, Gerente&);
    bool atualizar(const Gerente&);
    bool remover(const Email&);
    vector<Gerente> listar();
};

// Container de hoteis
class ContainerHoteis {
private:
    vector<Hotel> hoteis;
    const string arquivo = "data/hoteis.txt";
    void salvar();
    void carregar();

public:
    ContainerHoteis();
    bool adicionar(const Hotel&);
    bool buscar(const Codigo&, Hotel&);
    bool atualizar(const Hotel&);
    bool remover(const Codigo&);
    vector<Hotel> listar();
    vector<Hotel> listarPorGerente(const Email&);
};

// Container de quartos
class ContainerQuartos {
private:
    vector<Quarto> quartos;
    const string arquivo = "data/quartos.txt";
    void salvar();
    void carregar();

public:
    ContainerQuartos();
    bool adicionar(const Quarto&);
    bool buscar(const Numero&, const Codigo&, Quarto&);
    bool atualizar(const Quarto&);
    bool remover(const Numero&, const Codigo&);
    vector<Quarto> listar();
    vector<Quarto> listarPorHotel(const Codigo&);
    int contarPorHotel(const Codigo&);
};

// Container de reservas
class ContainerReservas {
private:
    vector<Reserva> reservas;
    const string arquivo = "data/reservas.txt";
    void salvar();
    void carregar();

public:
    ContainerReservas();
    bool adicionar(const Reserva&);
    bool buscar(const Codigo&, Reserva&);
    bool atualizar(const Reserva&);
    bool remover(const Codigo&);
    vector<Reserva> listar();
    vector<Reserva> listarPorQuarto(const Numero&, const Codigo&);
    int contarPorQuarto(const Numero&, const Codigo&);
};

// Container de hospedes
class ContainerHospedes {
private:
    vector<Hospede> hospedes;
    const string arquivo = "data/hospedes.txt";
    void salvar();
    void carregar();

public:
    ContainerHospedes();
    bool adicionar(const Hospede&);
    bool buscar(const Cartao&, Hospede&);
    bool atualizar(const Hospede&);
    bool remover(const Cartao&);
    vector<Hospede> listar();
    int contarPorReserva(const Codigo&);
};

// ========== CONTROLADORAS DE SERVICO ==========

// Controladora de servico de autenticacao
class ControladoraServicoAutenticacao : public IServicoAutenticacao {
private:
    ContainerGerentes* containerGerentes;

public:
    ControladoraServicoAutenticacao(ContainerGerentes*);
    bool autenticar(const Email&, const Senha&) override;
    bool criarConta(const Gerente&) override;
};

// Controladora de servico de gerente
class ControladoraServicoGerente : public IServicoGerente {
private:
    ContainerGerentes* containerGerentes;

public:
    ControladoraServicoGerente(ContainerGerentes*);
    bool buscar(const Email&, Gerente&) override;
    bool atualizar(const Gerente&) override;
    bool remover(const Email&) override;
    vector<Gerente> listar() override;
};

// Controladora de servico de hotel
class ControladoraServicoHotel : public IServicoHotel {
private:
    ContainerHoteis* containerHoteis;
    ContainerQuartos* containerQuartos;

public:
    ControladoraServicoHotel(ContainerHoteis*, ContainerQuartos*);
    bool criar(const Hotel&) override;
    bool buscar(const Codigo&, Hotel&) override;
    bool atualizar(const Hotel&) override;
    bool remover(const Codigo&) override;
    vector<Hotel> listar() override;
    vector<Hotel> listarPorGerente(const Email&) override;
};

// Controladora de servico de quarto
class ControladoraServicoQuarto : public IServicoQuarto {
private:
    ContainerQuartos* containerQuartos;
    ContainerReservas* containerReservas;

public:
    ControladoraServicoQuarto(ContainerQuartos*, ContainerReservas*);
    bool criar(const Quarto&) override;
    bool buscar(const Numero&, const Codigo&, Quarto&) override;
    bool atualizar(const Quarto&) override;
    bool remover(const Numero&, const Codigo&) override;
    vector<Quarto> listar() override;
    vector<Quarto> listarPorHotel(const Codigo&) override;
};

// Controladora de servico de reserva
class ControladoraServicoReserva : public IServicoReserva {
private:
    ContainerReservas* containerReservas;
    ContainerHospedes* containerHospedes;

public:
    ControladoraServicoReserva(ContainerReservas*, ContainerHospedes*);
    bool criar(const Reserva&) override;
    bool buscar(const Codigo&, Reserva&) override;
    bool atualizar(const Reserva&) override;
    bool remover(const Codigo&) override;
    vector<Reserva> listar() override;
    bool verificarConflito(const Numero&, const Codigo&, const Data&, const Data&, const Codigo&) override;
};

// Controladora de servico de hospede
class ControladoraServicoHospede : public IServicoHospede {
private:
    ContainerHospedes* containerHospedes;

public:
    ControladoraServicoHospede(ContainerHospedes*);
    bool criar(const Hospede&) override;
    bool buscar(const Cartao&, Hospede&) override;
    bool atualizar(const Hospede&) override;
    bool remover(const Cartao&) override;
    vector<Hospede> listar() override;
};

#endif // SERVICO_H
