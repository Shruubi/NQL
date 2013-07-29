#include "Tokenizer.h"

std::vector<std::string> readAndTokenize(std::string code)
{
    std::vector<std::string> ret;
    std::string temp = "";
    for(int i = 0; i < code.size(); i++)
    {
        //this line takes care of strings, we're just going to treat them as atoms (not spec compliant)
        //for the simple fact that much like you can't really redefine that the number 2 has the value
        //2, you cannot redefine the meaning of a sentence.
        if(code[i] == '"')
        {
            temp += code[i];
            i++;
            while(code[i] != '"')
            {
                temp += code[i];
                i++;
            }
        }
        if(code[i] == ' ')
        {
            ret.push_back(temp);
            temp = "";
        }
        else
        {
            temp += code[i];
        }
    }
    ret.push_back(temp); //catch left behind values
    return ret;
}

std::string format(std::string code)
{
    std::string tmp = "";
    for(int i = 0; i < code.size(); i++)
    {
        if(code[i] == '(')
        {
            tmp += "( ";
        }
        else if(code[i] == ')')
        {
            tmp += " )";
        }
        else
        {
            tmp += code[i];
        }
    }
    
    return tmp;
}