// apresentacao.cpp - Implementacao da camada de apresentacao

#include "apresentacao.h"

// ========== FUNCOES AUXILIARES ==========

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPressione ENTER para continuar...";
    limparBuffer();
    cin.get();
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ========== CONTROLADORA APRESENTACAO AUTENTICACAO ==========

ControladoraApresentacaoAutenticacao::ControladoraApresentacaoAutenticacao(IServicoAutenticacao* servico) {
    this->servicoAutenticacao = servico;
}

bool ControladoraApresentacaoAutenticacao::executar(Email& emailAutenticado) {
    int opcao;
    
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  SISTEMA DE GESTAO DE HOTEIS" << endl;
        cout << "========================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Criar Conta" << endl;
        cout << "0. Sair" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            return false;
        } else if (opcao == 1) {
            // Login
            string emailStr, senhaStr;
            
            cout << "\n--- LOGIN ---" << endl;
            cout << "Email: ";
            getline(cin, emailStr);
            cout << "Senha: ";
            getline(cin, senhaStr);
            
            try {
                Email email;
                email.set(emailStr);
                
                Senha senha;
                senha.set(senhaStr);
                
                if (servicoAutenticacao->autenticar(email, senha)) {
                    emailAutenticado = email;
                    cout << "\nLogin realizado com sucesso!" << endl;
                    pausar();
                    return true;
                } else {
                    cout << "\nEmail ou senha incorretos!" << endl;
                    pausar();
                }
            } catch (const invalid_argument& e) {
                cout << "\nErro: " << e.what() << endl;
                pausar();
            }
            
        } else if (opcao == 2) {
            // Criar conta
            string nomeStr, emailStr, senhaStr;
            
            cout << "\n--- CRIAR CONTA ---" << endl;
            cout << "Nome: ";
            getline(cin, nomeStr);
            cout << "Email: ";
            getline(cin, emailStr);
            cout << "Senha (5 caracteres com letra minuscula, maiuscula, digito e especial): ";
            getline(cin, senhaStr);
            
            try {
                Nome nome;
                nome.set(nomeStr);
                
                Email email;
                email.set(emailStr);
                
                Senha senha;
                senha.set(senhaStr);
                
                Gerente gerente;
                gerente.setNome(nome);
                gerente.setEmail(email);
                gerente.setSenha(senha);
                
                if (servicoAutenticacao->criarConta(gerente)) {
                    cout << "\nConta criada com sucesso!" << endl;
                    pausar();
                } else {
                    cout << "\nEmail ja cadastrado!" << endl;
                    pausar();
                }
            } catch (const invalid_argument& e) {
                cout << "\nErro: " << e.what() << endl;
                pausar();
            }
        }
    }
}

// ========== CONTROLADORA APRESENTACAO GERENTE ==========

ControladoraApresentacaoGerente::ControladoraApresentacaoGerente(IServicoGerente* servico) {
    this->servicoGerente = servico;
}

void ControladoraApresentacaoGerente::executar(const Email& emailGerente) {
    int opcao;
    
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  GERENCIAMENTO DE PERFIL" << endl;
        cout << "========================================" << endl;
        cout << "1. Editar Perfil" << endl;
        cout << "0. Voltar" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            editarPerfil(emailGerente);
        }
    }
}

void ControladoraApresentacaoGerente::editarPerfil(const Email& emailGerente) {
    Gerente gerente;
    
    if (!servicoGerente->buscar(emailGerente, gerente)) {
        cout << "\nErro ao buscar perfil!" << endl;
        pausar();
        return;
    }
    
    cout << "\n--- EDITAR PERFIL ---" << endl;
    cout << "Nome atual: " << gerente.getNome().get() << endl;
    cout << "Email atual: " << gerente.getEmail().get() << endl;
    
    string nomeStr, senhaStr;
    
    cout << "\nNovo nome (ou ENTER para manter): ";
    getline(cin, nomeStr);
    
    cout << "Nova senha (ou ENTER para manter): ";
    getline(cin, senhaStr);
    
    try {
        if (!nomeStr.empty()) {
            Nome nome;
            nome.set(nomeStr);
            gerente.setNome(nome);
        }
        
        if (!senhaStr.empty()) {
            Senha senha;
            senha.set(senhaStr);
            gerente.setSenha(senha);
        }
        
        if (servicoGerente->atualizar(gerente)) {
            cout << "\nPerfil atualizado com sucesso!" << endl;
        } else {
            cout << "\nErro ao atualizar perfil!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

// ========== CONTROLADORA APRESENTACAO HOTEL ==========

ControladoraApresentacaoHotel::ControladoraApresentacaoHotel(IServicoHotel* servico) {
    this->servicoHotel = servico;
}

void ControladoraApresentacaoHotel::executar(const Email& emailGerente) {
    int opcao;
    
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  GERENCIAMENTO DE HOTEIS" << endl;
        cout << "========================================" << endl;
        cout << "1. Criar Hotel" << endl;
        cout << "2. Listar Hoteis" << endl;
        cout << "3. Editar Hotel" << endl;
        cout << "4. Excluir Hotel" << endl;
        cout << "0. Voltar" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            criarHotel(emailGerente);
        } else if (opcao == 2) {
            listarHoteis(emailGerente);
        } else if (opcao == 3) {
            editarHotel();
        } else if (opcao == 4) {
            excluirHotel();
        }
    }
}

void ControladoraApresentacaoHotel::criarHotel(const Email& emailGerente) {
    cout << "\n--- CRIAR HOTEL ---" << endl;
    
    string nomeStr, enderecoStr, telefoneStr, codigoStr;
    
    cout << "Nome: ";
    getline(cin, nomeStr);
    cout << "Endereco: ";
    getline(cin, enderecoStr);
    cout << "Telefone (+DDDDDDDDDDDDDD): ";
    getline(cin, telefoneStr);
    cout << "Codigo (10 caracteres alfanumericos): ";
    getline(cin, codigoStr);
    
    try {
        Nome nome;
        nome.set(nomeStr);
        
        Endereco endereco;
        endereco.set(enderecoStr);
        
        Telefone telefone;
        telefone.set(telefoneStr);
        
        Codigo codigo;
        codigo.set(codigoStr);
        
        Hotel hotel;
        hotel.setNome(nome);
        hotel.setEndereco(endereco);
        hotel.setTelefone(telefone);
        hotel.setCodigo(codigo);
        hotel.setEmailGerente(emailGerente);
        
        if (servicoHotel->criar(hotel)) {
            cout << "\nHotel criado com sucesso!" << endl;
        } else {
            cout << "\nCodigo ja cadastrado!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoHotel::listarHoteis(const Email& emailGerente) {
    cout << "\n--- LISTA DE HOTEIS ---" << endl;
    
    vector<Hotel> hoteis = servicoHotel->listarPorGerente(emailGerente);
    
    if (hoteis.empty()) {
        cout << "Nenhum hotel cadastrado." << endl;
    } else {
        for (const auto& h : hoteis) {
            cout << "\nCodigo: " << h.getCodigo().get() << endl;
            cout << "Nome: " << h.getNome().get() << endl;
            cout << "Endereco: " << h.getEndereco().get() << endl;
            cout << "Telefone: " << h.getTelefone().get() << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    
    pausar();
}

void ControladoraApresentacaoHotel::editarHotel() {
    cout << "\n--- EDITAR HOTEL ---" << endl;
    
    string codigoStr;
    cout << "Codigo do hotel: ";
    getline(cin, codigoStr);
    
    try {
        Codigo codigo;
        codigo.set(codigoStr);
        
        Hotel hotel;
        if (!servicoHotel->buscar(codigo, hotel)) {
            cout << "\nHotel nao encontrado!" << endl;
            pausar();
            return;
        }
        
        cout << "\nDados atuais:" << endl;
        cout << "Nome: " << hotel.getNome().get() << endl;
        cout << "Endereco: " << hotel.getEndereco().get() << endl;
        cout << "Telefone: " << hotel.getTelefone().get() << endl;
        
        string nomeStr, enderecoStr, telefoneStr;
        
        cout << "\nNovo nome (ou ENTER para manter): ";
        getline(cin, nomeStr);
        cout << "Novo endereco (ou ENTER para manter): ";
        getline(cin, enderecoStr);
        cout << "Novo telefone (ou ENTER para manter): ";
        getline(cin, telefoneStr);
        
        if (!nomeStr.empty()) {
            Nome nome;
            nome.set(nomeStr);
            hotel.setNome(nome);
        }
        
        if (!enderecoStr.empty()) {
            Endereco endereco;
            endereco.set(enderecoStr);
            hotel.setEndereco(endereco);
        }
        
        if (!telefoneStr.empty()) {
            Telefone telefone;
            telefone.set(telefoneStr);
            hotel.setTelefone(telefone);
        }
        
        if (servicoHotel->atualizar(hotel)) {
            cout << "\nHotel atualizado com sucesso!" << endl;
        } else {
            cout << "\nErro ao atualizar hotel!" << endl;
        }
        
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoHotel::excluirHotel() {
    cout << "\n--- EXCLUIR HOTEL ---" << endl;
    
    string codigoStr;
    cout << "Codigo do hotel: ";
    getline(cin, codigoStr);
    
    try {
        Codigo codigo;
        codigo.set(codigoStr);
        
        if (servicoHotel->remover(codigo)) {
            cout << "\nHotel excluido com sucesso!" << endl;
        } else {
            cout << "\nNao foi possivel excluir o hotel (pode haver quartos associados)!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

// ========== CONTROLADORA APRESENTACAO QUARTO ==========

ControladoraApresentacaoQuarto::ControladoraApresentacaoQuarto(IServicoQuarto* servicoQ, IServicoHotel* servicoH) {
    this->servicoQuarto = servicoQ;
    this->servicoHotel = servicoH;
}

void ControladoraApresentacaoQuarto::executar(const Email& emailGerente) {
    int opcao;
    
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  GERENCIAMENTO DE QUARTOS" << endl;
        cout << "========================================" << endl;
        cout << "1. Criar Quarto" << endl;
        cout << "2. Listar Quartos" << endl;
        cout << "3. Editar Quarto" << endl;
        cout << "4. Excluir Quarto" << endl;
        cout << "0. Voltar" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            criarQuarto(emailGerente);
        } else if (opcao == 2) {
            listarQuartos(emailGerente);
        } else if (opcao == 3) {
            editarQuarto();
        } else if (opcao == 4) {
            excluirQuarto();
        }
    }
}

void ControladoraApresentacaoQuarto::criarQuarto(const Email& emailGerente) {
    cout << "\n--- CRIAR QUARTO ---" << endl;
    
    // Listar hoteis do gerente
    vector<Hotel> hoteis = servicoHotel->listarPorGerente(emailGerente);
    
    if (hoteis.empty()) {
        cout << "Voce nao possui hoteis cadastrados!" << endl;
        pausar();
        return;
    }
    
    cout << "Hoteis disponiveis:" << endl;
    for (const auto& h : hoteis) {
        cout << "- " << h.getCodigo().get() << ": " << h.getNome().get() << endl;
    }
    
    string codigoHotelStr;
    int numeroInt, capacidadeInt, diariaInt, ramalInt;
    
    cout << "\nCodigo do hotel: ";
    getline(cin, codigoHotelStr);
    cout << "Numero do quarto (1-999): ";
    cin >> numeroInt;
    cout << "Capacidade (1-4): ";
    cin >> capacidadeInt;
    cout << "Diaria em centavos (ex: 10000 = R$ 100,00): ";
    cin >> diariaInt;
    cout << "Ramal (0-50): ";
    cin >> ramalInt;
    limparBuffer();
    
    try {
        Codigo codigoHotel;
        codigoHotel.set(codigoHotelStr);
        
        Numero numero;
        numero.set(numeroInt);
        
        Capacidade capacidade;
        capacidade.set(capacidadeInt);
        
        Dinheiro diaria;
        diaria.set(diariaInt);
        
        Ramal ramal;
        ramal.set(ramalInt);
        
        Quarto quarto;
        quarto.setNumero(numero);
        quarto.setCapacidade(capacidade);
        quarto.setDiaria(diaria);
        quarto.setRamal(ramal);
        quarto.setCodigoHotel(codigoHotel);
        
        if (servicoQuarto->criar(quarto)) {
            cout << "\nQuarto criado com sucesso!" << endl;
        } else {
            cout << "\nNumero de quarto ja cadastrado neste hotel!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoQuarto::listarQuartos(const Email& emailGerente) {
    cout << "\n--- LISTA DE QUARTOS ---" << endl;
    
    vector<Hotel> hoteis = servicoHotel->listarPorGerente(emailGerente);
    
    if (hoteis.empty()) {
        cout << "Voce nao possui hoteis cadastrados!" << endl;
        pausar();
        return;
    }
    
    for (const auto& hotel : hoteis) {
        cout << "\nHotel: " << hotel.getNome().get() << " (" << hotel.getCodigo().get() << ")" << endl;
        cout << "----------------------------------------" << endl;
        
        vector<Quarto> quartos = servicoQuarto->listarPorHotel(hotel.getCodigo());
        
        if (quartos.empty()) {
            cout << "Nenhum quarto cadastrado." << endl;
        } else {
            for (const auto& q : quartos) {
                cout << "Numero: " << q.getNumero().getFormatado() << endl;
                cout << "Capacidade: " << q.getCapacidade().get() << " pessoa(s)" << endl;
                cout << "Diaria: " << q.getDiaria().getFormatado() << endl;
                cout << "Ramal: " << q.getRamal().getFormatado() << endl;
                cout << "---" << endl;
            }
        }
    }
    
    pausar();
}

void ControladoraApresentacaoQuarto::editarQuarto() {
    cout << "\n--- EDITAR QUARTO ---" << endl;
    
    string codigoHotelStr;
    int numeroInt;
    
    cout << "Codigo do hotel: ";
    getline(cin, codigoHotelStr);
    cout << "Numero do quarto: ";
    cin >> numeroInt;
    limparBuffer();
    
    try {
        Codigo codigoHotel;
        codigoHotel.set(codigoHotelStr);
        
        Numero numero;
        numero.set(numeroInt);
        
        Quarto quarto;
        if (!servicoQuarto->buscar(numero, codigoHotel, quarto)) {
            cout << "\nQuarto nao encontrado!" << endl;
            pausar();
            return;
        }
        
        cout << "\nDados atuais:" << endl;
        cout << "Capacidade: " << quarto.getCapacidade().get() << endl;
        cout << "Diaria: " << quarto.getDiaria().getFormatado() << endl;
        cout << "Ramal: " << quarto.getRamal().get() << endl;
        
        int capacidadeInt, diariaInt, ramalInt;
        string input;
        
        cout << "\nNova capacidade (ou 0 para manter): ";
        cin >> capacidadeInt;
        cout << "Nova diaria em centavos (ou 0 para manter): ";
        cin >> diariaInt;
        cout << "Novo ramal (ou -1 para manter): ";
        cin >> ramalInt;
        limparBuffer();
        
        if (capacidadeInt > 0) {
            Capacidade capacidade;
            capacidade.set(capacidadeInt);
            quarto.setCapacidade(capacidade);
        }
        
        if (diariaInt > 0) {
            Dinheiro diaria;
            diaria.set(diariaInt);
            quarto.setDiaria(diaria);
        }
        
        if (ramalInt >= 0) {
            Ramal ramal;
            ramal.set(ramalInt);
            quarto.setRamal(ramal);
        }
        
        if (servicoQuarto->atualizar(quarto)) {
            cout << "\nQuarto atualizado com sucesso!" << endl;
        } else {
            cout << "\nErro ao atualizar quarto!" << endl;
        }
        
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoQuarto::excluirQuarto() {
    cout << "\n--- EXCLUIR QUARTO ---" << endl;
    
    string codigoHotelStr;
    int numeroInt;
    
    cout << "Codigo do hotel: ";
    getline(cin, codigoHotelStr);
    cout << "Numero do quarto: ";
    cin >> numeroInt;
    limparBuffer();
    
    try {
        Codigo codigoHotel;
        codigoHotel.set(codigoHotelStr);
        
        Numero numero;
        numero.set(numeroInt);
        
        if (servicoQuarto->remover(numero, codigoHotel)) {
            cout << "\nQuarto excluido com sucesso!" << endl;
        } else {
            cout << "\nNao foi possivel excluir o quarto (pode haver reservas associadas)!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

// Continua na proxima parte...

// ========== CONTROLADORA APRESENTACAO RESERVA ==========

ControladoraApresentacaoReserva::ControladoraApresentacaoReserva(IServicoReserva* servicoR, IServicoHotel* servicoH, IServicoQuarto* servicoQ) {
    this->servicoReserva = servicoR;
    this->servicoHotel = servicoH;
    this->servicoQuarto = servicoQ;
}

void ControladoraApresentacaoReserva::executar(const Email& emailGerente) {
    int opcao;
    
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  GERENCIAMENTO DE RESERVAS" << endl;
        cout << "========================================" << endl;
        cout << "1. Criar Reserva" << endl;
        cout << "2. Listar Reservas" << endl;
        cout << "3. Editar Reserva" << endl;
        cout << "4. Excluir Reserva" << endl;
        cout << "0. Voltar" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            criarReserva(emailGerente);
        } else if (opcao == 2) {
            listarReservas();
        } else if (opcao == 3) {
            editarReserva();
        } else if (opcao == 4) {
            excluirReserva();
        }
    }
}

void ControladoraApresentacaoReserva::criarReserva(const Email& emailGerente) {
    cout << "\n--- CRIAR RESERVA ---" << endl;
    
    vector<Hotel> hoteis = servicoHotel->listarPorGerente(emailGerente);
    
    if (hoteis.empty()) {
        cout << "Voce nao possui hoteis cadastrados!" << endl;
        pausar();
        return;
    }
    
    cout << "Hoteis disponiveis:" << endl;
    for (const auto& h : hoteis) {
        cout << "- " << h.getCodigo().get() << ": " << h.getNome().get() << endl;
    }
    
    string codigoHotelStr, chegadaStr, partidaStr, codigoStr;
    int numeroInt, valorInt;
    
    cout << "\nCodigo do hotel: ";
    getline(cin, codigoHotelStr);
    cout << "Numero do quarto: ";
    cin >> numeroInt;
    limparBuffer();
    cout << "Data de chegada (DD-MMM-AAAA): ";
    getline(cin, chegadaStr);
    cout << "Data de partida (DD-MMM-AAAA): ";
    getline(cin, partidaStr);
    cout << "Valor em centavos: ";
    cin >> valorInt;
    limparBuffer();
    cout << "Codigo da reserva (10 caracteres): ";
    getline(cin, codigoStr);
    
    try {
        Codigo codigoHotel;
        codigoHotel.set(codigoHotelStr);
        
        Numero numero;
        numero.set(numeroInt);
        
        Data chegada;
        chegada.set(chegadaStr);
        
        Data partida;
        partida.set(partidaStr);
        
        Dinheiro valor;
        valor.set(valorInt);
        
        Codigo codigo;
        codigo.set(codigoStr);
        
        // Verificar se quarto existe
        Quarto quarto;
        if (!servicoQuarto->buscar(numero, codigoHotel, quarto)) {
            cout << "\nQuarto nao encontrado!" << endl;
            pausar();
            return;
        }
        
        // Verificar conflito de datas
        Codigo codigoVazio;
        codigoVazio.set("0000000000");
        if (servicoReserva->verificarConflito(numero, codigoHotel, chegada, partida, codigoVazio)) {
            cout << "\nConflito de datas! Ja existe reserva para este quarto no periodo informado." << endl;
            pausar();
            return;
        }
        
        Reserva reserva;
        reserva.setChegada(chegada);
        reserva.setPartida(partida);
        reserva.setValor(valor);
        reserva.setCodigo(codigo);
        reserva.setNumeroQuarto(numero);
        reserva.setCodigoHotel(codigoHotel);
        
        if (servicoReserva->criar(reserva)) {
            cout << "\nReserva criada com sucesso!" << endl;
        } else {
            cout << "\nCodigo de reserva ja cadastrado!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoReserva::listarReservas() {
    cout << "\n--- LISTA DE RESERVAS ---" << endl;
    
    vector<Reserva> reservas = servicoReserva->listar();
    
    if (reservas.empty()) {
        cout << "Nenhuma reserva cadastrada." << endl;
    } else {
        for (const auto& r : reservas) {
            cout << "\nCodigo: " << r.getCodigo().get() << endl;
            cout << "Hotel: " << r.getCodigoHotel().get() << endl;
            cout << "Quarto: " << r.getNumeroQuarto().getFormatado() << endl;
            cout << "Chegada: " << r.getChegada().get() << endl;
            cout << "Partida: " << r.getPartida().get() << endl;
            cout << "Valor: " << r.getValor().getFormatado() << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    
    pausar();
}

void ControladoraApresentacaoReserva::editarReserva() {
    cout << "\n--- EDITAR RESERVA ---" << endl;
    
    string codigoStr;
    cout << "Codigo da reserva: ";
    getline(cin, codigoStr);
    
    try {
        Codigo codigo;
        codigo.set(codigoStr);
        
        Reserva reserva;
        if (!servicoReserva->buscar(codigo, reserva)) {
            cout << "\nReserva nao encontrada!" << endl;
            pausar();
            return;
        }
        
        cout << "\nDados atuais:" << endl;
        cout << "Chegada: " << reserva.getChegada().get() << endl;
        cout << "Partida: " << reserva.getPartida().get() << endl;
        cout << "Valor: " << reserva.getValor().getFormatado() << endl;
        
        string chegadaStr, partidaStr;
        int valorInt;
        
        cout << "\nNova data de chegada (ou ENTER para manter): ";
        getline(cin, chegadaStr);
        cout << "Nova data de partida (ou ENTER para manter): ";
        getline(cin, partidaStr);
        cout << "Novo valor em centavos (ou 0 para manter): ";
        cin >> valorInt;
        limparBuffer();
        
        if (!chegadaStr.empty()) {
            Data chegada;
            chegada.set(chegadaStr);
            reserva.setChegada(chegada);
        }
        
        if (!partidaStr.empty()) {
            Data partida;
            partida.set(partidaStr);
            reserva.setPartida(partida);
        }
        
        if (valorInt > 0) {
            Dinheiro valor;
            valor.set(valorInt);
            reserva.setValor(valor);
        }
        
        // Verificar conflito
        if (servicoReserva->verificarConflito(reserva.getNumeroQuarto(), reserva.getCodigoHotel(),
                                               reserva.getChegada(), reserva.getPartida(), codigo)) {
            cout << "\nConflito de datas! Ja existe outra reserva para este quarto no periodo informado." << endl;
            pausar();
            return;
        }
        
        if (servicoReserva->atualizar(reserva)) {
            cout << "\nReserva atualizada com sucesso!" << endl;
        } else {
            cout << "\nErro ao atualizar reserva!" << endl;
        }
        
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoReserva::excluirReserva() {
    cout << "\n--- EXCLUIR RESERVA ---" << endl;
    
    string codigoStr;
    cout << "Codigo da reserva: ";
    getline(cin, codigoStr);
    
    try {
        Codigo codigo;
        codigo.set(codigoStr);
        
        if (servicoReserva->remover(codigo)) {
            cout << "\nReserva excluida com sucesso!" << endl;
        } else {
            cout << "\nNao foi possivel excluir a reserva (pode haver hospedes associados)!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

// ========== CONTROLADORA APRESENTACAO HOSPEDE ==========

ControladoraApresentacaoHospede::ControladoraApresentacaoHospede(IServicoHospede* servicoH, IServicoReserva* servicoR) {
    this->servicoHospede = servicoH;
    this->servicoReserva = servicoR;
}

void ControladoraApresentacaoHospede::executar(const Email& emailGerente) {
    int opcao;
    
    while (true) {
        limparTela();
        cout << "========================================" << endl;
        cout << "  GERENCIAMENTO DE HOSPEDES" << endl;
        cout << "========================================" << endl;
        cout << "1. Criar Hospede" << endl;
        cout << "2. Listar Hospedes" << endl;
        cout << "3. Editar Hospede" << endl;
        cout << "4. Excluir Hospede" << endl;
        cout << "0. Voltar" << endl;
        cout << "========================================" << endl;
        cout << "Opcao: ";
        
        cin >> opcao;
        limparBuffer();
        
        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            criarHospede();
        } else if (opcao == 2) {
            listarHospedes();
        } else if (opcao == 3) {
            editarHospede();
        } else if (opcao == 4) {
            excluirHospede();
        }
    }
}

void ControladoraApresentacaoHospede::criarHospede() {
    cout << "\n--- CRIAR HOSPEDE ---" << endl;
    
    string enderecoStr, cartaoStr, codigoReservaStr;
    
    cout << "Endereco: ";
    getline(cin, enderecoStr);
    cout << "Cartao (16 digitos com Luhn): ";
    getline(cin, cartaoStr);
    cout << "Codigo da reserva: ";
    getline(cin, codigoReservaStr);
    
    try {
        Endereco endereco;
        endereco.set(enderecoStr);
        
        Cartao cartao;
        cartao.set(cartaoStr);
        
        Codigo codigoReserva;
        codigoReserva.set(codigoReservaStr);
        
        // Verificar se reserva existe
        Reserva reserva;
        if (!servicoReserva->buscar(codigoReserva, reserva)) {
            cout << "\nReserva nao encontrada!" << endl;
            pausar();
            return;
        }
        
        Hospede hospede;
        hospede.setEndereco(endereco);
        hospede.setCartao(cartao);
        hospede.setCodigoReserva(codigoReserva);
        
        if (servicoHospede->criar(hospede)) {
            cout << "\nHospede criado com sucesso!" << endl;
        } else {
            cout << "\nCartao ja cadastrado!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoHospede::listarHospedes() {
    cout << "\n--- LISTA DE HOSPEDES ---" << endl;
    
    vector<Hospede> hospedes = servicoHospede->listar();
    
    if (hospedes.empty()) {
        cout << "Nenhum hospede cadastrado." << endl;
    } else {
        for (const auto& h : hospedes) {
            cout << "\nCartao: " << h.getCartao().get() << endl;
            cout << "Endereco: " << h.getEndereco().get() << endl;
            cout << "Reserva: " << h.getCodigoReserva().get() << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    
    pausar();
}

void ControladoraApresentacaoHospede::editarHospede() {
    cout << "\n--- EDITAR HOSPEDE ---" << endl;
    
    string cartaoStr;
    cout << "Cartao do hospede: ";
    getline(cin, cartaoStr);
    
    try {
        Cartao cartao;
        cartao.set(cartaoStr);
        
        Hospede hospede;
        if (!servicoHospede->buscar(cartao, hospede)) {
            cout << "\nHospede nao encontrado!" << endl;
            pausar();
            return;
        }
        
        cout << "\nDados atuais:" << endl;
        cout << "Endereco: " << hospede.getEndereco().get() << endl;
        
        string enderecoStr;
        
        cout << "\nNovo endereco (ou ENTER para manter): ";
        getline(cin, enderecoStr);
        
        if (!enderecoStr.empty()) {
            Endereco endereco;
            endereco.set(enderecoStr);
            hospede.setEndereco(endereco);
        }
        
        if (servicoHospede->atualizar(hospede)) {
            cout << "\nHospede atualizado com sucesso!" << endl;
        } else {
            cout << "\nErro ao atualizar hospede!" << endl;
        }
        
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}

void ControladoraApresentacaoHospede::excluirHospede() {
    cout << "\n--- EXCLUIR HOSPEDE ---" << endl;
    
    string cartaoStr;
    cout << "Cartao do hospede: ";
    getline(cin, cartaoStr);
    
    try {
        Cartao cartao;
        cartao.set(cartaoStr);
        
        if (servicoHospede->remover(cartao)) {
            cout << "\nHospede excluido com sucesso!" << endl;
        } else {
            cout << "\nHospede nao encontrado!" << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "\nErro: " << e.what() << endl;
    }
    
    pausar();
}
