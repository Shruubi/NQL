#include <string>
#include <iostream>
#include <map>

#include "ast.h"
#include "Tokenizer.h"
#include "Parser.h"

std::map<std::string, node*> vars;

int main(int argc, char* argv[])
{
    std::string c = "";
    while(c != "q")
    {
        std::getline(std::cin, c);
        auto v = readAndTokenize(format(c));
        auto t = buildTree(v);
        std::cout << eval(t) << std::endl;
    }
    return 0;
}