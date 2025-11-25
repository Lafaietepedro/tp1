// servico.cpp - Implementacao da camada de servico

#include "servico.h"
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif

using namespace std;

// ========== CONTAINER GERENTES ==========

ContainerGerentes::ContainerGerentes() {
    // Criar diretorio data se nao existir
    mkdir("data", 0755);
    carregar();
}

void ContainerGerentes::salvar() {
    ofstream file(arquivo);
    if (file.is_open()) {
        for (const auto& g : gerentes) {
            file << g.getEmail().get() << "|"
                 << g.getNome().get() << "|"
                 << g.getSenha().get() << "\n";
        }
        file.close();
    }
}

void ContainerGerentes::carregar() {
    gerentes.clear();
    ifstream file(arquivo);
    if (file.is_open()) {
        string linha;
        while (getline(file, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string email_str, nome_str, senha_str;
            
            getline(ss, email_str, '|');
            getline(ss, nome_str, '|');
            getline(ss, senha_str, '|');
            
            if (!email_str.empty() && !nome_str.empty() && !senha_str.empty()) {
                try {
                    Email email; email.set(email_str);
                    Nome nome; nome.set(nome_str);
                    Senha senha; senha.set(senha_str);
                    
                    Gerente gerente;
                    gerente.setEmail(email);
                    gerente.setNome(nome);
                    gerente.setSenha(senha);
                    
                    gerentes.push_back(gerente);
                } catch (...) {
                    // Ignorar linhas invalidas
                }
            }
        }
        file.close();
    }
}

bool ContainerGerentes::adicionar(const Gerente& gerente) {
    // Verificar se email ja existe
    for (const auto& g : gerentes) {
        if (g.getEmail().get() == gerente.getEmail().get()) {
            return false;
        }
    }
    gerentes.push_back(gerente);
    salvar();
    return true;
}

bool ContainerGerentes::buscar(const Email& email, Gerente& gerente) {
    for (const auto& g : gerentes) {
        if (g.getEmail().get() == email.get()) {
            gerente = g;
            return true;
        }
    }
    return false;
}

bool ContainerGerentes::atualizar(const Gerente& gerente) {
    for (auto& g : gerentes) {
        if (g.getEmail().get() == gerente.getEmail().get()) {
            g = gerente;
            salvar();
            return true;
        }
    }
    return false;
}

bool ContainerGerentes::remover(const Email& email) {
    auto it = remove_if(gerentes.begin(), gerentes.end(),
        [&email](const Gerente& g) { return g.getEmail().get() == email.get(); });
    
    if (it != gerentes.end()) {
        gerentes.erase(it, gerentes.end());
        salvar();
        return true;
    }
    return false;
}

vector<Gerente> ContainerGerentes::listar() {
    return gerentes;
}

// ========== CONTAINER HOTEIS ==========

ContainerHoteis::ContainerHoteis() {
    mkdir("data", 0755);
    carregar();
}

void ContainerHoteis::salvar() {
    ofstream file(arquivo);
    if (file.is_open()) {
        for (const auto& h : hoteis) {
            file << h.getCodigo().get() << "|"
                 << h.getNome().get() << "|"
                 << h.getEndereco().get() << "|"
                 << h.getTelefone().get() << "|"
                 << h.getEmailGerente().get() << "\n";
        }
        file.close();
    }
}

void ContainerHoteis::carregar() {
    hoteis.clear();
    ifstream file(arquivo);
    if (file.is_open()) {
        string linha;
        while (getline(file, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string codigo_str, nome_str, endereco_str, telefone_str, email_str;
            
            getline(ss, codigo_str, '|');
            getline(ss, nome_str, '|');
            getline(ss, endereco_str, '|');
            getline(ss, telefone_str, '|');
            getline(ss, email_str, '|');
            
            if (!codigo_str.empty() && !nome_str.empty()) {
                try {
                    Codigo codigo; codigo.set(codigo_str);
                    Nome nome; nome.set(nome_str);
                    Endereco endereco; endereco.set(endereco_str);
                    Telefone telefone; telefone.set(telefone_str);
                    Email email; email.set(email_str);
                    
                    Hotel hotel;
                    hotel.setCodigo(codigo);
                    hotel.setNome(nome);
                    hotel.setEndereco(endereco);
                    hotel.setTelefone(telefone);
                    hotel.setEmailGerente(email);
                    
                    hoteis.push_back(hotel);
                } catch (...) {
                    // Ignorar linhas invalidas
                }
            }
        }
        file.close();
    }
}

bool ContainerHoteis::adicionar(const Hotel& hotel) {
    // Verificar se codigo ja existe
    for (const auto& h : hoteis) {
        if (h.getCodigo().get() == hotel.getCodigo().get()) {
            return false;
        }
    }
    hoteis.push_back(hotel);
    salvar();
    return true;
}

bool ContainerHoteis::buscar(const Codigo& codigo, Hotel& hotel) {
    for (const auto& h : hoteis) {
        if (h.getCodigo().get() == codigo.get()) {
            hotel = h;
            return true;
        }
    }
    return false;
}

bool ContainerHoteis::atualizar(const Hotel& hotel) {
    for (auto& h : hoteis) {
        if (h.getCodigo().get() == hotel.getCodigo().get()) {
            h = hotel;
            salvar();
            return true;
        }
    }
    return false;
}

bool ContainerHoteis::remover(const Codigo& codigo) {
    auto it = remove_if(hoteis.begin(), hoteis.end(),
        [&codigo](const Hotel& h) { return h.getCodigo().get() == codigo.get(); });
    
    if (it != hoteis.end()) {
        hoteis.erase(it, hoteis.end());
        salvar();
        return true;
    }
    return false;
}

vector<Hotel> ContainerHoteis::listar() {
    return hoteis;
}

vector<Hotel> ContainerHoteis::listarPorGerente(const Email& email) {
    vector<Hotel> resultado;
    for (const auto& h : hoteis) {
        if (h.getEmailGerente().get() == email.get()) {
            resultado.push_back(h);
        }
    }
    return resultado;
}

// ========== CONTAINER QUARTOS ==========

ContainerQuartos::ContainerQuartos() {
    mkdir("data", 0755);
    carregar();
}

void ContainerQuartos::salvar() {
    ofstream file(arquivo);
    if (file.is_open()) {
        for (const auto& q : quartos) {
            file << q.getNumero().get() << "|"
                 << q.getCodigoHotel().get() << "|"
                 << q.getCapacidade().get() << "|"
                 << q.getDiaria().get() << "|"
                 << q.getRamal().get() << "\n";
        }
        file.close();
    }
}

void ContainerQuartos::carregar() {
    quartos.clear();
    ifstream file(arquivo);
    if (file.is_open()) {
        string linha;
        while (getline(file, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string numero_str, codigo_str, capacidade_str, diaria_str, ramal_str;
            
            getline(ss, numero_str, '|');
            getline(ss, codigo_str, '|');
            getline(ss, capacidade_str, '|');
            getline(ss, diaria_str, '|');
            getline(ss, ramal_str, '|');
            
            if (!numero_str.empty() && !codigo_str.empty()) {
                try {
                    Numero numero; numero.set(stoi(numero_str));
                    Codigo codigo; codigo.set(codigo_str);
                    Capacidade capacidade; capacidade.set(stoi(capacidade_str));
                    Dinheiro diaria; diaria.set(stoll(diaria_str));
                    Ramal ramal; ramal.set(stoi(ramal_str));
                    
                    Quarto quarto;
                    quarto.setNumero(numero);
                    quarto.setCodigoHotel(codigo);
                    quarto.setCapacidade(capacidade);
                    quarto.setDiaria(diaria);
                    quarto.setRamal(ramal);
                    
                    quartos.push_back(quarto);
                } catch (...) {
                    // Ignorar linhas invalidas
                }
            }
        }
        file.close();
    }
}

bool ContainerQuartos::adicionar(const Quarto& quarto) {
    // Verificar se numero ja existe no hotel
    for (const auto& q : quartos) {
        if (q.getNumero().get() == quarto.getNumero().get() &&
            q.getCodigoHotel().get() == quarto.getCodigoHotel().get()) {
            return false;
        }
    }
    quartos.push_back(quarto);
    salvar();
    return true;
}

bool ContainerQuartos::buscar(const Numero& numero, const Codigo& codigoHotel, Quarto& quarto) {
    for (const auto& q : quartos) {
        if (q.getNumero().get() == numero.get() &&
            q.getCodigoHotel().get() == codigoHotel.get()) {
            quarto = q;
            return true;
        }
    }
    return false;
}

bool ContainerQuartos::atualizar(const Quarto& quarto) {
    for (auto& q : quartos) {
        if (q.getNumero().get() == quarto.getNumero().get() &&
            q.getCodigoHotel().get() == quarto.getCodigoHotel().get()) {
            q = quarto;
            salvar();
            return true;
        }
    }
    return false;
}

bool ContainerQuartos::remover(const Numero& numero, const Codigo& codigoHotel) {
    auto it = remove_if(quartos.begin(), quartos.end(),
        [&numero, &codigoHotel](const Quarto& q) {
            return q.getNumero().get() == numero.get() &&
                   q.getCodigoHotel().get() == codigoHotel.get();
        });
    
    if (it != quartos.end()) {
        quartos.erase(it, quartos.end());
        salvar();
        return true;
    }
    return false;
}

vector<Quarto> ContainerQuartos::listar() {
    return quartos;
}

vector<Quarto> ContainerQuartos::listarPorHotel(const Codigo& codigoHotel) {
    vector<Quarto> resultado;
    for (const auto& q : quartos) {
        if (q.getCodigoHotel().get() == codigoHotel.get()) {
            resultado.push_back(q);
        }
    }
    return resultado;
}

int ContainerQuartos::contarPorHotel(const Codigo& codigoHotel) {
    int count = 0;
    for (const auto& q : quartos) {
        if (q.getCodigoHotel().get() == codigoHotel.get()) {
            count++;
        }
    }
    return count;
}

// ========== CONTAINER RESERVAS ==========

ContainerReservas::ContainerReservas() {
    mkdir("data", 0755);
    carregar();
}

void ContainerReservas::salvar() {
    ofstream file(arquivo);
    if (file.is_open()) {
        for (const auto& r : reservas) {
            file << r.getCodigo().get() << "|"
                 << r.getNumeroQuarto().get() << "|"
                 << r.getCodigoHotel().get() << "|"
                 << r.getChegada().get() << "|"
                 << r.getPartida().get() << "|"
                 << r.getValor().get() << "\n";
        }
        file.close();
    }
}

void ContainerReservas::carregar() {
    reservas.clear();
    ifstream file(arquivo);
    if (file.is_open()) {
        string linha;
        while (getline(file, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string codigo_str, numero_str, codigo_hotel_str, chegada_str, partida_str, valor_str;
            
            getline(ss, codigo_str, '|');
            getline(ss, numero_str, '|');
            getline(ss, codigo_hotel_str, '|');
            getline(ss, chegada_str, '|');
            getline(ss, partida_str, '|');
            getline(ss, valor_str, '|');
            
            if (!codigo_str.empty()) {
                try {
                    Codigo codigo; codigo.set(codigo_str);
                    Numero numero; numero.set(stoi(numero_str));
                    Codigo codigoHotel; codigoHotel.set(codigo_hotel_str);
                    Data chegada; chegada.set(chegada_str);
                    Data partida; partida.set(partida_str);
                    Dinheiro valor; valor.set(stoll(valor_str));
                    
                    Reserva reserva;
                    reserva.setCodigo(codigo);
                    reserva.setNumeroQuarto(numero);
                    reserva.setCodigoHotel(codigoHotel);
                    reserva.setChegada(chegada);
                    reserva.setPartida(partida);
                    reserva.setValor(valor);
                    
                    reservas.push_back(reserva);
                } catch (...) {
                    // Ignorar linhas invalidas
                }
            }
        }
        file.close();
    }
}

bool ContainerReservas::adicionar(const Reserva& reserva) {
    // Verificar se codigo ja existe
    for (const auto& r : reservas) {
        if (r.getCodigo().get() == reserva.getCodigo().get()) {
            return false;
        }
    }
    reservas.push_back(reserva);
    salvar();
    return true;
}

bool ContainerReservas::buscar(const Codigo& codigo, Reserva& reserva) {
    for (const auto& r : reservas) {
        if (r.getCodigo().get() == codigo.get()) {
            reserva = r;
            return true;
        }
    }
    return false;
}

bool ContainerReservas::atualizar(const Reserva& reserva) {
    for (auto& r : reservas) {
        if (r.getCodigo().get() == reserva.getCodigo().get()) {
            r = reserva;
            salvar();
            return true;
        }
    }
    return false;
}

bool ContainerReservas::remover(const Codigo& codigo) {
    auto it = remove_if(reservas.begin(), reservas.end(),
        [&codigo](const Reserva& r) { return r.getCodigo().get() == codigo.get(); });
    
    if (it != reservas.end()) {
        reservas.erase(it, reservas.end());
        salvar();
        return true;
    }
    return false;
}

vector<Reserva> ContainerReservas::listar() {
    return reservas;
}

vector<Reserva> ContainerReservas::listarPorQuarto(const Numero& numeroQuarto, const Codigo& codigoHotel) {
    vector<Reserva> resultado;
    for (const auto& r : reservas) {
        if (r.getNumeroQuarto().get() == numeroQuarto.get() &&
            r.getCodigoHotel().get() == codigoHotel.get()) {
            resultado.push_back(r);
        }
    }
    return resultado;
}

int ContainerReservas::contarPorQuarto(const Numero& numeroQuarto, const Codigo& codigoHotel) {
    int count = 0;
    for (const auto& r : reservas) {
        if (r.getNumeroQuarto().get() == numeroQuarto.get() &&
            r.getCodigoHotel().get() == codigoHotel.get()) {
            count++;
        }
    }
    return count;
}

// ========== CONTAINER HOSPEDES ==========

ContainerHospedes::ContainerHospedes() {
    mkdir("data", 0755);
    carregar();
}

void ContainerHospedes::salvar() {
    ofstream file(arquivo);
    if (file.is_open()) {
        for (const auto& h : hospedes) {
            file << h.getCartao().get() << "|"
                 << h.getEndereco().get() << "|"
                 << h.getCodigoReserva().get() << "\n";
        }
        file.close();
    }
}

void ContainerHospedes::carregar() {
    hospedes.clear();
    ifstream file(arquivo);
    if (file.is_open()) {
        string linha;
        while (getline(file, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string cartao_str, endereco_str, codigo_str;
            
            getline(ss, cartao_str, '|');
            getline(ss, endereco_str, '|');
            getline(ss, codigo_str, '|');
            
            if (!cartao_str.empty() && !endereco_str.empty()) {
                try {
                    Cartao cartao; cartao.set(cartao_str);
                    Endereco endereco; endereco.set(endereco_str);
                    Codigo codigo; codigo.set(codigo_str);
                    
                    Hospede hospede;
                    hospede.setCartao(cartao);
                    hospede.setEndereco(endereco);
                    hospede.setCodigoReserva(codigo);
                    
                    hospedes.push_back(hospede);
                } catch (...) {
                    // Ignorar linhas invalidas
                }
            }
        }
        file.close();
    }
}

bool ContainerHospedes::adicionar(const Hospede& hospede) {
    // Verificar se cartao ja existe
    for (const auto& h : hospedes) {
        if (h.getCartao().get() == hospede.getCartao().get()) {
            return false;
        }
    }
    hospedes.push_back(hospede);
    salvar();
    return true;
}

bool ContainerHospedes::buscar(const Cartao& cartao, Hospede& hospede) {
    for (const auto& h : hospedes) {
        if (h.getCartao().get() == cartao.get()) {
            hospede = h;
            return true;
        }
    }
    return false;
}

bool ContainerHospedes::atualizar(const Hospede& hospede) {
    for (auto& h : hospedes) {
        if (h.getCartao().get() == hospede.getCartao().get()) {
            h = hospede;
            salvar();
            return true;
        }
    }
    return false;
}

bool ContainerHospedes::remover(const Cartao& cartao) {
    auto it = remove_if(hospedes.begin(), hospedes.end(),
        [&cartao](const Hospede& h) { return h.getCartao().get() == cartao.get(); });
    
    if (it != hospedes.end()) {
        hospedes.erase(it, hospedes.end());
        salvar();
        return true;
    }
    return false;
}

vector<Hospede> ContainerHospedes::listar() {
    return hospedes;
}

int ContainerHospedes::contarPorReserva(const Codigo& codigoReserva) {
    int count = 0;
    for (const auto& h : hospedes) {
        if (h.getCodigoReserva().get() == codigoReserva.get()) {
            count++;
        }
    }
    return count;
}

// ========== CONTROLADORA SERVICO AUTENTICACAO ==========

ControladoraServicoAutenticacao::ControladoraServicoAutenticacao(ContainerGerentes* container) {
    this->containerGerentes = container;
}

bool ControladoraServicoAutenticacao::autenticar(const Email& email, const Senha& senha) {
    Gerente gerente;
    if (containerGerentes->buscar(email, gerente)) {
        return gerente.getSenha().get() == senha.get();
    }
    return false;
}

bool ControladoraServicoAutenticacao::criarConta(const Gerente& gerente) {
    return containerGerentes->adicionar(gerente);
}

// ========== CONTROLADORA SERVICO GERENTE ==========

ControladoraServicoGerente::ControladoraServicoGerente(ContainerGerentes* container) {
    this->containerGerentes = container;
}

bool ControladoraServicoGerente::buscar(const Email& email, Gerente& gerente) {
    return containerGerentes->buscar(email, gerente);
}

bool ControladoraServicoGerente::atualizar(const Gerente& gerente) {
    return containerGerentes->atualizar(gerente);
}

bool ControladoraServicoGerente::remover(const Email& email) {
    return containerGerentes->remover(email);
}

vector<Gerente> ControladoraServicoGerente::listar() {
    return containerGerentes->listar();
}

// ========== CONTROLADORA SERVICO HOTEL ==========

ControladoraServicoHotel::ControladoraServicoHotel(ContainerHoteis* containerH, ContainerQuartos* containerQ) {
    this->containerHoteis = containerH;
    this->containerQuartos = containerQ;
}

bool ControladoraServicoHotel::criar(const Hotel& hotel) {
    return containerHoteis->adicionar(hotel);
}

bool ControladoraServicoHotel::buscar(const Codigo& codigo, Hotel& hotel) {
    return containerHoteis->buscar(codigo, hotel);
}

bool ControladoraServicoHotel::atualizar(const Hotel& hotel) {
    return containerHoteis->atualizar(hotel);
}

bool ControladoraServicoHotel::remover(const Codigo& codigo) {
    // Verificar se ha quartos associados
    if (containerQuartos->contarPorHotel(codigo) > 0) {
        return false; // Nao pode remover hotel com quartos
    }
    return containerHoteis->remover(codigo);
}

vector<Hotel> ControladoraServicoHotel::listar() {
    return containerHoteis->listar();
}

vector<Hotel> ControladoraServicoHotel::listarPorGerente(const Email& email) {
    return containerHoteis->listarPorGerente(email);
}

// ========== CONTROLADORA SERVICO QUARTO ==========

ControladoraServicoQuarto::ControladoraServicoQuarto(ContainerQuartos* containerQ, ContainerReservas* containerR) {
    this->containerQuartos = containerQ;
    this->containerReservas = containerR;
}

bool ControladoraServicoQuarto::criar(const Quarto& quarto) {
    return containerQuartos->adicionar(quarto);
}

bool ControladoraServicoQuarto::buscar(const Numero& numero, const Codigo& codigoHotel, Quarto& quarto) {
    return containerQuartos->buscar(numero, codigoHotel, quarto);
}

bool ControladoraServicoQuarto::atualizar(const Quarto& quarto) {
    return containerQuartos->atualizar(quarto);
}

bool ControladoraServicoQuarto::remover(const Numero& numero, const Codigo& codigoHotel) {
    // Verificar se ha reservas associadas
    if (containerReservas->contarPorQuarto(numero, codigoHotel) > 0) {
        return false; // Nao pode remover quarto com reservas
    }
    return containerQuartos->remover(numero, codigoHotel);
}

vector<Quarto> ControladoraServicoQuarto::listar() {
    return containerQuartos->listar();
}

vector<Quarto> ControladoraServicoQuarto::listarPorHotel(const Codigo& codigoHotel) {
    return containerQuartos->listarPorHotel(codigoHotel);
}

// ========== CONTROLADORA SERVICO RESERVA ==========

ControladoraServicoReserva::ControladoraServicoReserva(ContainerReservas* containerR, ContainerHospedes* containerH) {
    this->containerReservas = containerR;
    this->containerHospedes = containerH;
}

bool ControladoraServicoReserva::criar(const Reserva& reserva) {
    return containerReservas->adicionar(reserva);
}

bool ControladoraServicoReserva::buscar(const Codigo& codigo, Reserva& reserva) {
    return containerReservas->buscar(codigo, reserva);
}

bool ControladoraServicoReserva::atualizar(const Reserva& reserva) {
    return containerReservas->atualizar(reserva);
}

bool ControladoraServicoReserva::remover(const Codigo& codigo) {
    // Verificar se ha hospedes associados
    if (containerHospedes->contarPorReserva(codigo) > 0) {
        return false; // Nao pode remover reserva com hospedes
    }
    return containerReservas->remover(codigo);
}

vector<Reserva> ControladoraServicoReserva::listar() {
    return containerReservas->listar();
}

bool ControladoraServicoReserva::verificarConflito(const Numero& numeroQuarto, const Codigo& codigoHotel,
                                                    const Data& chegada, const Data& partida,
                                                    const Codigo& codigoReservaIgnorar) {
    // Implementacao simplificada - verifica conflito de datas
    // Para implementacao completa, seria necessario comparar datas adequadamente
    vector<Reserva> reservas = containerReservas->listarPorQuarto(numeroQuarto, codigoHotel);
    
    for (const auto& r : reservas) {
        // Ignorar a propria reserva (para edicao)
        if (r.getCodigo().get() == codigoReservaIgnorar.get()) {
            continue;
        }
        
        // Verificar sobreposicao de datas (simplificado)
        // Conflito se: nova chegada < partida existente E nova partida > chegada existente
        // Aqui usamos comparacao de strings (funciona para formato DD-MMM-AAAA se ordenado)
        if (chegada.get() < r.getPartida().get() && partida.get() > r.getChegada().get()) {
            return true; // Ha conflito
        }
    }
    
    return false; // Sem conflito
}

// ========== CONTROLADORA SERVICO HOSPEDE ==========

ControladoraServicoHospede::ControladoraServicoHospede(ContainerHospedes* container) {
    this->containerHospedes = container;
}

bool ControladoraServicoHospede::criar(const Hospede& hospede) {
    return containerHospedes->adicionar(hospede);
}

bool ControladoraServicoHospede::buscar(const Cartao& cartao, Hospede& hospede) {
    return containerHospedes->buscar(cartao, hospede);
}

bool ControladoraServicoHospede::atualizar(const Hospede& hospede) {
    return containerHospedes->atualizar(hospede);
}

bool ControladoraServicoHospede::remover(const Cartao& cartao) {
    return containerHospedes->remover(cartao);
}

vector<Hospede> ControladoraServicoHospede::listar() {
    return containerHospedes->listar();
}
