// dominios.cpp - Implementacao das classes de dominio

#include "dominios.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <map>

// ========== CAPACIDADE ==========

void Capacidade::validar(int valor) {
    if (valor < 1 || valor > 4) {
        throw invalid_argument("Capacidade deve ser 1, 2, 3 ou 4");
    }
}

void Capacidade::set(int valor) {
    validar(valor);
    this->valor = valor;
}

int Capacidade::get() const {
    return valor;
}

// ========== CARTAO ==========

bool Cartao::validarLuhn(string numero) {
    int soma = 0;
    bool alternar = false;
    
    // Percorre da direita para esquerda
    for (int i = numero.length() - 1; i >= 0; i--) {
        int digito = numero[i] - '0';
        
        if (alternar) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }
        
        soma += digito;
        alternar = !alternar;
    }
    
    return (soma % 10) == 0;
}

void Cartao::validar(string numero) {
    // Verificar tamanho
    if (numero.length() != 16) {
        throw invalid_argument("Cartao deve ter exatamente 16 digitos");
    }
    
    // Verificar se todos sao digitos
    for (char c : numero) {
        if (!isdigit(c)) {
            throw invalid_argument("Cartao deve conter apenas digitos");
        }
    }
    
    // Validar algoritmo de Luhn
    if (!validarLuhn(numero)) {
        throw invalid_argument("Numero de cartao invalido (falha na validacao Luhn)");
    }
}

void Cartao::set(string numero) {
    validar(numero);
    this->numero = numero;
}

string Cartao::get() const {
    return numero;
}

// ========== CODIGO ==========

void Codigo::validar(string valor) {
    // Verificar tamanho
    if (valor.length() != 10) {
        throw invalid_argument("Codigo deve ter exatamente 10 caracteres");
    }
    
    // Verificar se todos sao alfanumericos (a-z ou 0-9)
    for (char c : valor) {
        if (!isalnum(c) || isupper(c)) {
            throw invalid_argument("Codigo deve conter apenas letras minusculas (a-z) ou digitos (0-9)");
        }
    }
}

void Codigo::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Codigo::get() const {
    return valor;
}

// ========== DATA ==========

bool Data::ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int Data::diasNoMes(int mes, int ano) {
    static const int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && ehBissexto(ano)) {
        return 29;
    }
    return dias[mes];
}

void Data::validar(string valor) {
    // Formato esperado: DD-MMM-AAAA (ex: 15-JAN-2025)
    if (valor.length() != 11) {
        throw invalid_argument("Data deve estar no formato DD-MMM-AAAA");
    }
    
    if (valor[2] != '-' || valor[6] != '-') {
        throw invalid_argument("Data deve conter hifens nas posicoes corretas (DD-MMM-AAAA)");
    }
    
    // Extrair componentes
    string diaStr = valor.substr(0, 2);
    string mesStr = valor.substr(3, 3);
    string anoStr = valor.substr(7, 4);
    
    // Verificar se dia e ano sao numericos
    for (char c : diaStr) {
        if (!isdigit(c)) {
            throw invalid_argument("Dia deve conter apenas digitos");
        }
    }
    for (char c : anoStr) {
        if (!isdigit(c)) {
            throw invalid_argument("Ano deve conter apenas digitos");
        }
    }
    
    // Converter para inteiros
    int dia = stoi(diaStr);
    int ano = stoi(anoStr);
    
    // Validar ano
    if (ano < 2000 || ano > 2999) {
        throw invalid_argument("Ano deve estar entre 2000 e 2999");
    }
    
    // Validar mes
    static const map<string, int> meses = {
        {"JAN", 1}, {"FEV", 2}, {"MAR", 3}, {"ABR", 4},
        {"MAI", 5}, {"JUN", 6}, {"JUL", 7}, {"AGO", 8},
        {"SET", 9}, {"OUT", 10}, {"NOV", 11}, {"DEZ", 12}
    };
    
    auto it = meses.find(mesStr);
    if (it == meses.end()) {
        throw invalid_argument("Mes invalido (use JAN, FEV, MAR, ABR, MAI, JUN, JUL, AGO, SET, OUT, NOV, DEZ)");
    }
    int mes = it->second;
    
    // Validar dia
    if (dia < 1 || dia > diasNoMes(mes, ano)) {
        throw invalid_argument("Dia invalido para o mes e ano especificados");
    }
}

void Data::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Data::get() const {
    return valor;
}

// ========== DINHEIRO ==========

void Dinheiro::validar(int centavos) {
    if (centavos < 1 || centavos > 100000000) {
        throw invalid_argument("Valor deve estar entre 0,01 e 1.000.000,00");
    }
}

void Dinheiro::set(int centavos) {
    validar(centavos);
    this->centavos = centavos;
}

int Dinheiro::get() const {
    return centavos;
}

string Dinheiro::getFormatado() const {
    int reais = centavos / 100;
    int cents = centavos % 100;
    
    ostringstream oss;
    oss << "R$ " << reais << "," << setfill('0') << setw(2) << cents;
    return oss.str();
}

// ========== EMAIL ==========

void Email::validar(string valor) {
    // Verificar presenca de @
    size_t posArroba = valor.find('@');
    if (posArroba == string::npos) {
        throw invalid_argument("Email deve conter @");
    }
    
    // Verificar se ha apenas um @
    if (valor.find('@', posArroba + 1) != string::npos) {
        throw invalid_argument("Email deve conter apenas um @");
    }
    
    string parteLocal = valor.substr(0, posArroba);
    string dominio = valor.substr(posArroba + 1);
    
    // Validar parte local
    if (parteLocal.empty() || parteLocal.length() > 64) {
        throw invalid_argument("Parte local do email deve ter de 1 a 64 caracteres");
    }
    
    // Parte local nao pode comecar ou terminar com ponto ou hifen
    if (parteLocal[0] == '.' || parteLocal[0] == '-' ||
        parteLocal[parteLocal.length()-1] == '.' || parteLocal[parteLocal.length()-1] == '-') {
        throw invalid_argument("Parte local nao pode iniciar ou terminar com ponto ou hifen");
    }
    
    // Validar caracteres da parte local
    for (size_t i = 0; i < parteLocal.length(); i++) {
        char c = parteLocal[i];
        if (!isalnum(c) && c != '.' && c != '-') {
            throw invalid_argument("Parte local pode conter apenas letras, digitos, ponto ou hifen");
        }
        // Ponto ou hifen nao pode ser seguido por ponto ou hifen
        if ((c == '.' || c == '-') && i + 1 < parteLocal.length()) {
            char proximo = parteLocal[i + 1];
            if (proximo == '.' || proximo == '-') {
                throw invalid_argument("Ponto ou hifen deve ser seguido por letra ou digito");
            }
        }
    }
    
    // Validar dominio
    if (dominio.empty() || dominio.length() > 255) {
        throw invalid_argument("Dominio do email deve ter de 1 a 255 caracteres");
    }
    
    // Dominio nao pode comecar ou terminar com hifen
    if (dominio[0] == '-' || dominio[dominio.length()-1] == '-') {
        throw invalid_argument("Dominio nao pode iniciar ou terminar com hifen");
    }
    
    // Validar partes do dominio separadas por ponto
    size_t pos = 0;
    size_t posPonto;
    
    while ((posPonto = dominio.find('.', pos)) != string::npos) {
        string parte = dominio.substr(pos, posPonto - pos);
        if (parte.empty()) {
            throw invalid_argument("Dominio nao pode ter pontos consecutivos");
        }
        for (char c : parte) {
            if (!isalnum(c) && c != '-') {
                throw invalid_argument("Partes do dominio podem conter apenas letras, digitos ou hifen");
            }
        }
        pos = posPonto + 1;
    }
    
    // Validar ultima parte do dominio
    string ultimaParte = dominio.substr(pos);
    if (ultimaParte.empty()) {
        throw invalid_argument("Dominio nao pode terminar com ponto");
    }
    for (char c : ultimaParte) {
        if (!isalnum(c) && c != '-') {
            throw invalid_argument("Partes do dominio podem conter apenas letras, digitos ou hifen");
        }
    }
}

void Email::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Email::get() const {
    return valor;
}

// ========== ENDERECO ==========

void Endereco::validar(string valor) {
    // Verificar tamanho
    if (valor.length() < 5 || valor.length() > 30) {
        throw invalid_argument("Endereco deve ter de 5 a 30 caracteres");
    }
    
    // Verificar caracteres validos
    for (char c : valor) {
        if (!isalnum(c) && c != ',' && c != '.' && c != ' ') {
            throw invalid_argument("Endereco pode conter apenas letras, digitos, virgula, ponto ou espaco");
        }
    }
    
    // Primeiro e ultimo caractere nao podem ser virgula, ponto ou espaco
    char primeiro = valor[0];
    char ultimo = valor[valor.length() - 1];
    if (primeiro == ',' || primeiro == '.' || primeiro == ' ' ||
        ultimo == ',' || ultimo == '.' || ultimo == ' ') {
        throw invalid_argument("Endereco nao pode iniciar ou terminar com virgula, ponto ou espaco");
    }
}

void Endereco::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Endereco::get() const {
    return valor;
}

// ========== NOME ==========

void Nome::validar(string valor) {
    // Verificar tamanho
    if (valor.length() < 5 || valor.length() > 20) {
        throw invalid_argument("Nome deve ter de 5 a 20 caracteres");
    }
    
    // Primeiro caractere deve ser letra maiuscula
    if (!isupper(valor[0])) {
        throw invalid_argument("Primeiro caractere do nome deve ser letra maiuscula");
    }
    
    // Verificar caracteres validos
    for (char c : valor) {
        if (!isalpha(c) && c != ' ') {
            throw invalid_argument("Nome pode conter apenas letras ou espacos");
        }
    }
    
    // Espaco deve ser seguido por letra
    for (size_t i = 0; i < valor.length() - 1; i++) {
        if (valor[i] == ' ' && !isalpha(valor[i + 1])) {
            throw invalid_argument("Espaco deve ser seguido por letra");
        }
    }
    
    // Ultimo caractere nao pode ser espaco
    if (valor[valor.length() - 1] == ' ') {
        throw invalid_argument("Nome nao pode terminar com espaco");
    }
}

void Nome::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Nome::get() const {
    return valor;
}

// ========== NUMERO ==========

void Numero::validar(int valor) {
    if (valor < 1 || valor > 999) {
        throw invalid_argument("Numero deve estar entre 001 e 999");
    }
}

void Numero::set(int valor) {
    validar(valor);
    this->valor = valor;
}

int Numero::get() const {
    return valor;
}

string Numero::getFormatado() const {
    ostringstream oss;
    oss << setfill('0') << setw(3) << valor;
    return oss.str();
}

// ========== RAMAL ==========

void Ramal::validar(int valor) {
    if (valor < 0 || valor > 50) {
        throw invalid_argument("Ramal deve estar entre 00 e 50");
    }
}

void Ramal::set(int valor) {
    validar(valor);
    this->valor = valor;
}

int Ramal::get() const {
    return valor;
}

string Ramal::getFormatado() const {
    ostringstream oss;
    oss << setfill('0') << setw(2) << valor;
    return oss.str();
}

// ========== SENHA ==========

void Senha::validar(string valor) {
    // Verificar tamanho
    if (valor.length() != 5) {
        throw invalid_argument("Senha deve ter exatamente 5 caracteres");
    }
    
    // Contadores para validacao
    bool temLetraMinuscula = false;
    bool temLetraMaiuscula = false;
    bool temDigito = false;
    bool temEspecial = false;
    
    // Caracteres especiais permitidos
    string especiais = "!\"#$%&?";
    
    for (size_t i = 0; i < valor.length(); i++) {
        char c = valor[i];
        
        if (islower(c)) {
            temLetraMinuscula = true;
            // Letra nao pode ser seguida por letra
            if (i + 1 < valor.length() && isalpha(valor[i + 1])) {
                throw invalid_argument("Letra nao pode ser seguida por letra");
            }
        } else if (isupper(c)) {
            temLetraMaiuscula = true;
            // Letra nao pode ser seguida por letra
            if (i + 1 < valor.length() && isalpha(valor[i + 1])) {
                throw invalid_argument("Letra nao pode ser seguida por letra");
            }
        } else if (isdigit(c)) {
            temDigito = true;
            // Digito nao pode ser seguido por digito
            if (i + 1 < valor.length() && isdigit(valor[i + 1])) {
                throw invalid_argument("Digito nao pode ser seguido por digito");
            }
        } else if (especiais.find(c) != string::npos) {
            temEspecial = true;
        } else {
            throw invalid_argument("Senha contem caractere invalido");
        }
    }
    
    // Deve ter pelo menos uma letra minuscula, uma maiuscula, um digito e um especial
    if (!temLetraMinuscula || !temLetraMaiuscula || !temDigito || !temEspecial) {
        throw invalid_argument("Senha deve conter pelo menos uma letra minuscula, uma maiuscula, um digito e um caractere especial");
    }
}

void Senha::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Senha::get() const {
    return valor;
}

// ========== TELEFONE ==========

void Telefone::validar(string valor) {
    // Verificar tamanho (+ seguido de 14 digitos)
    if (valor.length() != 15) {
        throw invalid_argument("Telefone deve ter formato +DDDDDDDDDDDDDD (15 caracteres)");
    }
    
    // Verificar se comeca com +
    if (valor[0] != '+') {
        throw invalid_argument("Telefone deve comecar com +");
    }
    
    // Verificar se os demais sao digitos
    for (size_t i = 1; i < valor.length(); i++) {
        if (!isdigit(valor[i])) {
            throw invalid_argument("Telefone deve conter apenas digitos apos o +");
        }
    }
}

void Telefone::set(string valor) {
    validar(valor);
    this->valor = valor;
}

string Telefone::get() const {
    return valor;
}
