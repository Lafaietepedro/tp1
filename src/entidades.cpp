// entidades.cpp - Implementacao das classes de entidade

#include "entidades.h"

// ========== PESSOA ==========

void Pessoa::setNome(const Nome& nome) {
    this->nome = nome;
}

Nome Pessoa::getNome() const {
    return nome;
}

void Pessoa::setEmail(const Email& email) {
    this->email = email;
}

Email Pessoa::getEmail() const {
    return email;
}

// ========== GERENTE ==========

void Gerente::setSenha(const Senha& senha) {
    this->senha = senha;
}

Senha Gerente::getSenha() const {
    return senha;
}

// ========== HOTEL ==========

void Hotel::setNome(const Nome& nome) {
    this->nome = nome;
}

Nome Hotel::getNome() const {
    return nome;
}

void Hotel::setEndereco(const Endereco& endereco) {
    this->endereco = endereco;
}

Endereco Hotel::getEndereco() const {
    return endereco;
}

void Hotel::setTelefone(const Telefone& telefone) {
    this->telefone = telefone;
}

Telefone Hotel::getTelefone() const {
    return telefone;
}

void Hotel::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;
}

Codigo Hotel::getCodigo() const {
    return codigo;
}

void Hotel::setEmailGerente(const Email& email) {
    this->emailGerente = email;
}

Email Hotel::getEmailGerente() const {
    return emailGerente;
}

// ========== QUARTO ==========

void Quarto::setNumero(const Numero& numero) {
    this->numero = numero;
}

Numero Quarto::getNumero() const {
    return numero;
}

void Quarto::setCapacidade(const Capacidade& capacidade) {
    this->capacidade = capacidade;
}

Capacidade Quarto::getCapacidade() const {
    return capacidade;
}

void Quarto::setDiaria(const Dinheiro& diaria) {
    this->diaria = diaria;
}

Dinheiro Quarto::getDiaria() const {
    return diaria;
}

void Quarto::setRamal(const Ramal& ramal) {
    this->ramal = ramal;
}

Ramal Quarto::getRamal() const {
    return ramal;
}

void Quarto::setCodigoHotel(const Codigo& codigo) {
    this->codigoHotel = codigo;
}

Codigo Quarto::getCodigoHotel() const {
    return codigoHotel;
}

// ========== RESERVA ==========

void Reserva::setChegada(const Data& chegada) {
    this->chegada = chegada;
}

Data Reserva::getChegada() const {
    return chegada;
}

void Reserva::setPartida(const Data& partida) {
    this->partida = partida;
}

Data Reserva::getPartida() const {
    return partida;
}

void Reserva::setValor(const Dinheiro& valor) {
    this->valor = valor;
}

Dinheiro Reserva::getValor() const {
    return valor;
}

void Reserva::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;
}

Codigo Reserva::getCodigo() const {
    return codigo;
}

void Reserva::setNumeroQuarto(const Numero& numero) {
    this->numeroQuarto = numero;
}

Numero Reserva::getNumeroQuarto() const {
    return numeroQuarto;
}

void Reserva::setCodigoHotel(const Codigo& codigo) {
    this->codigoHotel = codigo;
}

Codigo Reserva::getCodigoHotel() const {
    return codigoHotel;
}

// ========== HOSPEDE ==========

void Hospede::setEndereco(const Endereco& endereco) {
    this->endereco = endereco;
}

Endereco Hospede::getEndereco() const {
    return endereco;
}

void Hospede::setCartao(const Cartao& cartao) {
    this->cartao = cartao;
}

Cartao Hospede::getCartao() const {
    return cartao;
}

void Hospede::setCodigoReserva(const Codigo& codigo) {
    this->codigoReserva = codigo;
}

Codigo Hospede::getCodigoReserva() const {
    return codigoReserva;
}
