// interfaces.h - Interfaces entre modulos

#ifndef INTERFACES_H
#define INTERFACES_H

#include "entidades.h"
#include <vector>

using namespace std;

// ========== INTERFACES DE SERVICO ==========

// Interface de autenticacao
class IServicoAutenticacao {
public:
    virtual bool autenticar(const Email&, const Senha&) = 0;
    virtual bool criarConta(const Gerente&) = 0;
    virtual ~IServicoAutenticacao() {}
};

// Interface de servico de gerente
class IServicoGerente {
public:
    virtual bool buscar(const Email&, Gerente&) = 0;
    virtual bool atualizar(const Gerente&) = 0;
    virtual bool remover(const Email&) = 0;
    virtual vector<Gerente> listar() = 0;
    virtual ~IServicoGerente() {}
};

// Interface de servico de hotel
class IServicoHotel {
public:
    virtual bool criar(const Hotel&) = 0;
    virtual bool buscar(const Codigo&, Hotel&) = 0;
    virtual bool atualizar(const Hotel&) = 0;
    virtual bool remover(const Codigo&) = 0;
    virtual vector<Hotel> listar() = 0;
    virtual vector<Hotel> listarPorGerente(const Email&) = 0;
    virtual ~IServicoHotel() {}
};

// Interface de servico de quarto
class IServicoQuarto {
public:
    virtual bool criar(const Quarto&) = 0;
    virtual bool buscar(const Numero&, const Codigo&, Quarto&) = 0;
    virtual bool atualizar(const Quarto&) = 0;
    virtual bool remover(const Numero&, const Codigo&) = 0;
    virtual vector<Quarto> listar() = 0;
    virtual vector<Quarto> listarPorHotel(const Codigo&) = 0;
    virtual ~IServicoQuarto() {}
};

// Interface de servico de reserva
class IServicoReserva {
public:
    virtual bool criar(const Reserva&) = 0;
    virtual bool buscar(const Codigo&, Reserva&) = 0;
    virtual bool atualizar(const Reserva&) = 0;
    virtual bool remover(const Codigo&) = 0;
    virtual vector<Reserva> listar() = 0;
    virtual bool verificarConflito(const Numero&, const Codigo&, const Data&, const Data&, const Codigo&) = 0;
    virtual ~IServicoReserva() {}
};

// Interface de servico de hospede
class IServicoHospede {
public:
    virtual bool criar(const Hospede&) = 0;
    virtual bool buscar(const Cartao&, Hospede&) = 0;
    virtual bool atualizar(const Hospede&) = 0;
    virtual bool remover(const Cartao&) = 0;
    virtual vector<Hospede> listar() = 0;
    virtual ~IServicoHospede() {}
};

// ========== INTERFACES DE APRESENTACAO ==========

// Interface de apresentacao de autenticacao
class IApresentacaoAutenticacao {
public:
    virtual bool executar(Email&) = 0;
    virtual ~IApresentacaoAutenticacao() {}
};

// Interface de apresentacao de gerente
class IApresentacaoGerente {
public:
    virtual void executar(const Email&) = 0;
    virtual ~IApresentacaoGerente() {}
};

// Interface de apresentacao de hotel
class IApresentacaoHotel {
public:
    virtual void executar(const Email&) = 0;
    virtual ~IApresentacaoHotel() {}
};

// Interface de apresentacao de quarto
class IApresentacaoQuarto {
public:
    virtual void executar(const Email&) = 0;
    virtual ~IApresentacaoQuarto() {}
};

// Interface de apresentacao de reserva
class IApresentacaoReserva {
public:
    virtual void executar(const Email&) = 0;
    virtual ~IApresentacaoReserva() {}
};

// Interface de apresentacao de hospede
class IApresentacaoHospede {
public:
    virtual void executar(const Email&) = 0;
    virtual ~IApresentacaoHospede() {}
};

#endif // INTERFACES_H
