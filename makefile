CC=g++-4.7
CFLAGS=-o NQLi

all: ./NQL/main.cpp ./NQL/Tokenizer.cpp ./NQL/ast.cpp ./NQL/Parser.cpp
	$(CC) $(CFLAGS) ./NQL/main.cpp ./NQL/Tokenizer.cpp ./NQL/ast.cpp ./NQL/Parser.cpp 

