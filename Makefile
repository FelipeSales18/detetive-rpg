# escolhe o compilador
CXX = g++
# Define as flags de aviso e a versao do C++
CXXFLAGS = -Wall -Wextra -std=c++11

# Define o executavel
TARGET = build/DETETIVE_RPG
# Define quais arquivos .cpp precisam ser compilados
SRC = src/main.cpp src/GameManager.cpp src/TextLoader.cpp

# A regra padrao que roda quando voce digita "make"
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Regra para limpar a pasta build (comando: make clean)
clean:
	rm -f build/*