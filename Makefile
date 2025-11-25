# Makefile para Sistema de Gestao de Hoteis

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
TARGET = bin/sistema_hoteis
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Regra principal
all: $(TARGET)

# Criar diretórios
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Linkar objetos
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Executar
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
