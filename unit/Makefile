# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11

# Каталоги и файлы
SRCDIR = .
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = tests

# Флаги и библиотеки
LDFLAGS = -lcryptopp -lUnitTest++ 

# Правила
all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean
