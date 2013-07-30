#include <string>
#include <iostream>
#include <map>

#include "Tokenizer.h"
#include "ast.h"
#include "Parser.h"

std::map<std::string, node*> vars;

int main(int argc, char* argv[])
{
    std::string code = "";
    std::getline(std::cin, code);
    while(code != "(quit)")
    {
        std::string formatted_code = format(code);
        std::vector<std::string> tokens = readAndTokenize(formatted_code);
        node* ast = buildTree(tokens);
        std::cout << eval(ast) << std::endl;
        std::getline(std::cin, code);
    }
    return 0;
}
