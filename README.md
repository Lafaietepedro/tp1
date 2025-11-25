# Sistema de Gestão de Hotéis

Sistema desenvolvido em C++ para gerenciamento de pequenos hotéis, implementando arquitetura em camadas com validação rigorosa de dados.

## 📋 Descrição

Este sistema permite que gerentes de hotéis realizem operações completas de CRUD (Create, Read, Update, Delete) para:
- Gerentes (autenticação e perfil)
- Hotéis
- Quartos
- Reservas
- Hóspedes

## 🏗️ Arquitetura

O sistema utiliza **arquitetura em camadas** composta por 4 módulos principais:

1. **Módulo de Domínios**: Validação de tipos de dados
2. **Módulo de Entidades**: Representação de conceitos do negócio
3. **Módulo de Serviço**: Lógica de negócio e armazenamento
4. **Módulo de Apresentação**: Interface com usuário (console)

Para detalhes completos, consulte [docs/arquitetura.pdf](docs/arquitetura.pdf).

## 🔧 Compilação

### Requisitos
- g++ (C++11 ou superior)
- make

### Compilar
```bash
make
```

### Executar
```bash
make run
# ou
./bin/sistema_hoteis
```

### Limpar
```bash
make clean
```

## 🧪 Testes

### Compilar e executar testes de domínios
```bash
g++ -std=c++11 -Iinclude tests/test_dominios.cpp src/dominios.cpp -o bin/test_dominios
./bin/test_dominios
```

## 📚 Documentação

### Gerar documentação Doxygen
```bash
doxygen docs/Doxyfile
```

A documentação HTML será gerada em `docs/html/index.html`.

### Documentos disponíveis
- **Arquitetura**: `docs/arquitetura.pdf` - Modelo completo de arquitetura com diagrama UML
- **Doxygen HTML**: `docs/html/` - Documentação de todas as classes
- **Diagrama UML**: `docs/arquitetura_uml.png` - Diagrama visual da arquitetura

## 📁 Estrutura de Diretórios

```
TP1-Sistema-Gestao-Hoteis/
├── include/           # Arquivos de cabeçalho (.h)
│   ├── dominios.h
│   ├── entidades.h
│   ├── interfaces.h
│   ├── servico.h
│   └── apresentacao.h
├── src/               # Arquivos de implementação (.cpp)
│   ├── dominios.cpp
│   ├── entidades.cpp
│   ├── servico.cpp
│   ├── apresentacao.cpp
│   └── main.cpp
├── tests/             # Testes unitários
│   └── test_dominios.cpp
├── docs/              # Documentação
│   ├── Doxyfile
│   ├── arquitetura.md
│   ├── arquitetura.pdf
│   ├── arquitetura.puml
│   ├── arquitetura_uml.png
│   └── html/          # Documentação Doxygen
├── bin/               # Executáveis (gerado)
├── obj/               # Arquivos objeto (gerado)
├── Makefile
└── README.md
```

## 🎯 Funcionalidades

### Autenticação
- Criar conta de gerente (nome, email, senha)
- Login com email e senha

### Gerenciamento de Hotéis
- Criar hotel (nome, endereço, telefone, código)
- Listar hotéis do gerente
- Editar informações do hotel
- Excluir hotel (se não houver quartos)

### Gerenciamento de Quartos
- Criar quarto (número, capacidade, diária, ramal)
- Listar quartos por hotel
- Editar informações do quarto
- Excluir quarto (se não houver reservas)

### Gerenciamento de Reservas
- Criar reserva (datas, valor, código)
- Listar todas as reservas
- Editar reserva (com validação de conflitos)
- Excluir reserva (se não houver hóspedes)

### Gerenciamento de Hóspedes
- Criar hóspede (endereço, cartão, reserva)
- Listar hóspedes
- Editar informações do hóspede
- Excluir hóspede

## ✅ Validações Implementadas

### Domínios
- **Capacidade**: 1, 2, 3 ou 4
- **Cartão**: 16 dígitos com validação Luhn
- **Código**: 10 caracteres alfanuméricos (a-z, 0-9)
- **Data**: DD-MMM-AAAA com validação de anos bissextos
- **Dinheiro**: 0,01 a 1.000.000,00 (armazenado em centavos)
- **Email**: formato parte-local@domínio
- **Endereço**: 5 a 30 caracteres
- **Nome**: 5 a 20 caracteres, primeiro maiúsculo
- **Número**: 001 a 999
- **Ramal**: 00 a 50
- **Senha**: 5 caracteres (letra minúscula, maiúscula, dígito, especial)
- **Telefone**: +DDDDDDDDDDDDDD (14 dígitos)

### Regras de Negócio
- Não permitir exclusão de hotel com quartos
- Não permitir exclusão de quarto com reservas
- Não permitir exclusão de reserva com hóspedes
- Não permitir sobreposição de datas em reservas
- Não permitir duplicação de chaves primárias

## 👥 Autores

Desenvolvido como Trabalho Prático 1 da disciplina de Técnicas de Programação I.

## 📄 Licença

Este projeto foi desenvolvido para fins acadêmicos.

## 🔍 Observações

- O sistema armazena dados em memória (não há persistência após encerramento)
- Interface de console (cin/cout)
- Validações não consideram acentuação nem letra ç
- Compatível com Code::Blocks
