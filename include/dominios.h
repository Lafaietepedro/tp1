// dominios.h - Classes de dominio

#ifndef DOMINIOS_H
#define DOMINIOS_H

#include <string>
#include <stdexcept>

using namespace std;

// Capacidade de quarto (1, 2, 3 ou 4)
class Capacidade {
private:
    int valor;
    void validar(int);

public:
    void set(int);
    int get() const;
};

// Cartao de credito (16 digitos com validacao Luhn)
class Cartao {
private:
    string numero;
    void validar(string);
    bool validarLuhn(string);

public:
    void set(string);
    string get() const;
};

// Codigo alfanumerico de 10 caracteres
class Codigo {
private:
    string valor;
    void validar(string);

public:
    void set(string);
    string get() const;
};

// Data no formato DD-MMM-AAAA
class Data {
private:
    string valor;
    void validar(string);
    bool ehBissexto(int ano);
    int diasNoMes(int mes, int ano);

public:
    void set(string);
    string get() const;
};

// Valor monetario (armazenado em centavos)
class Dinheiro {
private:
    int centavos;
    void validar(int);

public:
    void set(int);
    int get() const;
    string getFormatado() const;
};

// Email valido
class Email {
private:
    string valor;
    void validar(string);

public:
    void set(string);
    string get() const;
};

// Endereco (5 a 30 caracteres)
class Endereco {
private:
    string valor;
    void validar(string);

public:
    void set(string);
    string get() const;
};

// Nome (5 a 20 caracteres, primeiro maiusculo)
class Nome {
private:
    string valor;
    void validar(string);

public:
    void set(string);
    string get() const;
};

// Numero de quarto (001 a 999)
class Numero {
private:
    int valor;
    void validar(int);

public:
    void set(int);
    int get() const;
    string getFormatado() const;
};

// Ramal telefonico (00 a 50)
class Ramal {
private:
    int valor;
    void validar(int);

public:
    void set(int);
    int get() const;
    string getFormatado() const;
};

// Senha (5 caracteres com regras especificas)
class Senha {
private:
    string valor;
    void validar(string);

public:
    void set(string);
    string get() const;
};

// Telefone no formato +DDDDDDDDDDDDDD
class Telefone {
private:
    string valor;
    void validar(string);

public:
    void set(string);
    string get() const;
};

#endif // DOMINIOS_H
