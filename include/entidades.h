// entidades.h - Classes de entidade

#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "dominios.h"
#include <string>

using namespace std;

// Classe base Pessoa
class Pessoa {
protected:
    Nome nome;
    Email email;

public:
    void setNome(const Nome&);
    Nome getNome() const;
    void setEmail(const Email&);
    Email getEmail() const;
};

// Gerente (herda de Pessoa)
class Gerente : public Pessoa {
private:
    Senha senha;

public:
    void setSenha(const Senha&);
    Senha getSenha() const;
};

// Hotel
class Hotel {
private:
    Nome nome;
    Endereco endereco;
    Telefone telefone;
    Codigo codigo;
    Email emailGerente; // Relacionamento com Gerente (0..*)

public:
    void setNome(const Nome&);
    Nome getNome() const;
    void setEndereco(const Endereco&);
    Endereco getEndereco() const;
    void setTelefone(const Telefone&);
    Telefone getTelefone() const;
    void setCodigo(const Codigo&);
    Codigo getCodigo() const;
    void setEmailGerente(const Email&);
    Email getEmailGerente() const;
};

// Quarto
class Quarto {
private:
    Numero numero;
    Capacidade capacidade;
    Dinheiro diaria;
    Ramal ramal;
    Codigo codigoHotel; // Relacionamento com Hotel (1)

public:
    void setNumero(const Numero&);
    Numero getNumero() const;
    void setCapacidade(const Capacidade&);
    Capacidade getCapacidade() const;
    void setDiaria(const Dinheiro&);
    Dinheiro getDiaria() const;
    void setRamal(const Ramal&);
    Ramal getRamal() const;
    void setCodigoHotel(const Codigo&);
    Codigo getCodigoHotel() const;
};

// Reserva
class Reserva {
private:
    Data chegada;
    Data partida;
    Dinheiro valor;
    Codigo codigo;
    Numero numeroQuarto; // Relacionamento com Quarto (1)
    Codigo codigoHotel;  // Para facilitar buscas

public:
    void setChegada(const Data&);
    Data getChegada() const;
    void setPartida(const Data&);
    Data getPartida() const;
    void setValor(const Dinheiro&);
    Dinheiro getValor() const;
    void setCodigo(const Codigo&);
    Codigo getCodigo() const;
    void setNumeroQuarto(const Numero&);
    Numero getNumeroQuarto() const;
    void setCodigoHotel(const Codigo&);
    Codigo getCodigoHotel() const;
};

// Hospede
class Hospede {
private:
    Endereco endereco;
    Cartao cartao;
    Codigo codigoReserva;

public:
    void setEndereco(const Endereco&);
    Endereco getEndereco() const;
    void setCartao(const Cartao&);
    Cartao getCartao() const;
    void setCodigoReserva(const Codigo&);
    Codigo getCodigoReserva() const;
};

#endif // ENTIDADES_H
