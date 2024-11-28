# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/local/include -I/path/to/UnitTest++/include

# Каталоги и файлы
SRCDIR = .
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = tests

# Флаги и библиотеки
LDFLAGS = -L/usr/local/lib -lcryptopp -lUnitTest++ -lpthread

# Правила
all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean
