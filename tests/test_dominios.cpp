/**
 * @file test_dominios.cpp
 * @brief Testes das classes de dominio
 */

#include "../include/dominios.h"
#include <iostream>
#include <cassert>

using namespace std;

void testarCapacidade() {
    cout << "Testando Capacidade..." << endl;
    
    Capacidade cap;
    
    // Teste valido
    try {
        cap.set(2);
        assert(cap.get() == 2);
        cout << "  [OK] Capacidade valida: 2" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Capacidade valida falhou: " << e.what() << endl;
    }
    
    // Teste invalido
    try {
        cap.set(5);
        cout << "  [ERRO] Capacidade invalida nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Capacidade invalida rejeitada: " << e.what() << endl;
    }
}

void testarCartao() {
    cout << "\nTestando Cartao..." << endl;
    
    Cartao cartao;
    
    // Teste valido (numero com Luhn valido)
    try {
        cartao.set("4532015112830366"); // Numero valido com Luhn
        assert(cartao.get() == "4532015112830366");
        cout << "  [OK] Cartao valido" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Cartao valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (tamanho errado)
    try {
        cartao.set("123456789");
        cout << "  [ERRO] Cartao com tamanho invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Cartao com tamanho invalido rejeitado: " << e.what() << endl;
    }
}

void testarCodigo() {
    cout << "\nTestando Codigo..." << endl;
    
    Codigo codigo;
    
    // Teste valido
    try {
        codigo.set("abc1234567");
        assert(codigo.get() == "abc1234567");
        cout << "  [OK] Codigo valido" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Codigo valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (tamanho errado)
    try {
        codigo.set("abc123");
        cout << "  [ERRO] Codigo com tamanho invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Codigo com tamanho invalido rejeitado: " << e.what() << endl;
    }
}

void testarData() {
    cout << "\nTestando Data..." << endl;
    
    Data data;
    
    // Teste valido
    try {
        data.set("15-JAN-2025");
        assert(data.get() == "15-JAN-2025");
        cout << "  [OK] Data valida" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Data valida falhou: " << e.what() << endl;
    }
    
    // Teste invalido (dia invalido)
    try {
        data.set("32-JAN-2025");
        cout << "  [ERRO] Data com dia invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Data com dia invalido rejeitada: " << e.what() << endl;
    }
    
    // Teste ano bissexto
    try {
        data.set("29-FEV-2024"); // 2024 eh bissexto
        assert(data.get() == "29-FEV-2024");
        cout << "  [OK] Data em ano bissexto valida" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Data em ano bissexto falhou: " << e.what() << endl;
    }
}

void testarDinheiro() {
    cout << "\nTestando Dinheiro..." << endl;
    
    Dinheiro dinheiro;
    
    // Teste valido
    try {
        dinheiro.set(10000); // R$ 100,00
        assert(dinheiro.get() == 10000);
        cout << "  [OK] Dinheiro valido: " << dinheiro.getFormatado() << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Dinheiro valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (valor muito alto)
    try {
        dinheiro.set(200000000);
        cout << "  [ERRO] Dinheiro com valor invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Dinheiro com valor invalido rejeitado: " << e.what() << endl;
    }
}

void testarEmail() {
    cout << "\nTestando Email..." << endl;
    
    Email email;
    
    // Teste valido
    try {
        email.set("usuario@dominio.com");
        assert(email.get() == "usuario@dominio.com");
        cout << "  [OK] Email valido" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Email valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (sem @)
    try {
        email.set("usuariodominio.com");
        cout << "  [ERRO] Email sem @ nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Email sem @ rejeitado: " << e.what() << endl;
    }
}

void testarEndereco() {
    cout << "\nTestando Endereco..." << endl;
    
    Endereco endereco;
    
    // Teste valido
    try {
        endereco.set("Rua A, 123");
        assert(endereco.get() == "Rua A, 123");
        cout << "  [OK] Endereco valido" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Endereco valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (muito curto)
    try {
        endereco.set("Rua");
        cout << "  [ERRO] Endereco muito curto nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Endereco muito curto rejeitado: " << e.what() << endl;
    }
}

void testarNome() {
    cout << "\nTestando Nome..." << endl;
    
    Nome nome;
    
    // Teste valido
    try {
        nome.set("Joao Silva");
        assert(nome.get() == "Joao Silva");
        cout << "  [OK] Nome valido" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Nome valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (nao comeca com maiuscula)
    try {
        nome.set("joao silva");
        cout << "  [ERRO] Nome sem maiuscula nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Nome sem maiuscula rejeitado: " << e.what() << endl;
    }
}

void testarNumero() {
    cout << "\nTestando Numero..." << endl;
    
    Numero numero;
    
    // Teste valido
    try {
        numero.set(101);
        assert(numero.get() == 101);
        assert(numero.getFormatado() == "101");
        cout << "  [OK] Numero valido: " << numero.getFormatado() << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Numero valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (fora do range)
    try {
        numero.set(1000);
        cout << "  [ERRO] Numero invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Numero invalido rejeitado: " << e.what() << endl;
    }
}

void testarRamal() {
    cout << "\nTestando Ramal..." << endl;
    
    Ramal ramal;
    
    // Teste valido
    try {
        ramal.set(25);
        assert(ramal.get() == 25);
        assert(ramal.getFormatado() == "25");
        cout << "  [OK] Ramal valido: " << ramal.getFormatado() << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Ramal valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (fora do range)
    try {
        ramal.set(51);
        cout << "  [ERRO] Ramal invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Ramal invalido rejeitado: " << e.what() << endl;
    }
}

void testarSenha() {
    cout << "\nTestando Senha..." << endl;
    
    Senha senha;
    
    // Teste valido
    try {
        senha.set("A1b2#");
        assert(senha.get() == "A1b2#");
        cout << "  [OK] Senha valida" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Senha valida falhou: " << e.what() << endl;
    }
    
    // Teste invalido (tamanho errado)
    try {
        senha.set("A1b2");
        cout << "  [ERRO] Senha com tamanho invalido nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Senha com tamanho invalido rejeitada: " << e.what() << endl;
    }
}

void testarTelefone() {
    cout << "\nTestando Telefone..." << endl;
    
    Telefone telefone;
    
    // Teste valido
    try {
        telefone.set("+55119876543210");
        assert(telefone.get() == "+55119876543210");
        cout << "  [OK] Telefone valido" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [ERRO] Telefone valido falhou: " << e.what() << endl;
    }
    
    // Teste invalido (sem +)
    try {
        telefone.set("55119876543210");
        cout << "  [ERRO] Telefone sem + nao lancou excecao" << endl;
    } catch (const invalid_argument& e) {
        cout << "  [OK] Telefone sem + rejeitado: " << e.what() << endl;
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "  TESTES DE DOMINIOS" << endl;
    cout << "========================================" << endl;
    
    testarCapacidade();
    testarCartao();
    testarCodigo();
    testarData();
    testarDinheiro();
    testarEmail();
    testarEndereco();
    testarNome();
    testarNumero();
    testarRamal();
    testarSenha();
    testarTelefone();
    
    cout << "\n========================================" << endl;
    cout << "  TODOS OS TESTES CONCLUIDOS" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
