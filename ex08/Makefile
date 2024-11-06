# Compilador a ser utilizado
CXX = g++

# Flags que vamos passar para o compilador
# -Wall -> habilita warning
# -std=c++11 garante a utilizacao do standard C++11
CXXFLAGS = -Wall -std=c++11

# Nome do executavel a ser criado
TARGET = main

# Source files
# Lista de todos os arquivos .cpp que precisam ser compilados
SRCS = main.cpp Graph.cpp Node.cpp Edge.cpp

# Object files
# Arquivos .o a serem criados pela compilação
OBJS = $(SRCS:.cpp=.o)

# O target que será chamado ao invocarmos 'make'
# Compila o programa e linka os objetos criando o executavel
all: $(TARGET)

# Regra para criacao do executavel final
# $@ refere-se ao target (o executavel final -> $(TARGET))
# $^ refere-se as dependencias (os object files $(OBJS))
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

# Regra para compilar os arquivos .cpp em .o
# $< o arquivo .cpp
# a flag -c apenas compila sem linkar
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para remoção usando make clean
# Remove os object files e o executavel final
clean:
	rm -f $(OBJS) $(TARGET)

# Ignora arquivos de nome "all" e "clean"
.PHONY: all clean
