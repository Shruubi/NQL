CC=g++
CFLAGS=-o NQL

all: ./NQL/main.cpp ./NQL/Tokenizer.cpp ./NQL/ast.cpp ./NQL/Parser.cpp
	$(CC) $(CFLAGS) ./NQL/main.cpp ./NQL/Tokenizer.cpp ./NQL/ast.cpp ./NQL/Parser.cpp 
