#include "Parser.h"

extern std::map<std::string, node*> vars;

std::string convertInt(int number)
{
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

std::vector<int> buildNumList(node* n)
{
    std::vector<int> numList;
    //populate number list. if n is an ATOM then just pop that onto the numList for returning the identity
    if(n->type == ATOM)
    {
        numList.push_back(atoi(n->val.c_str()));
    }
    else if(n->type == VAR)
    {
        node* ptr = vars[n->val];
        numList.push_back(atoi(ptr->val.c_str()));
    }
    else
    {
        for(int i = 0; i < n->next.size(); i++)
        {
            if(n->next[i]->type == SYMBOL)
            {
                numList.push_back(eval(n->next[i]));
            }
            else if(n->next[i]->type == VAR)
            {
                node* ptr = vars[n->next[i]->val];
                numList.push_back(atoi(ptr->val.c_str()));
            }
            if(n->next[i]->type == ATOM)
            {
                numList.push_back(atoi(n->next[i]->val.c_str()));
            }
        }
    }
    return numList;
}

std::vector<std::string> buildArgsList(node* n)
{
    std::vector<std::string> argsList;
    for(int i = 0; i < n->next.size(); i++)
    {
        if(n->next[i]->type == VAR)
        {
            node* ptr = vars[n->next[i]->val];
            argsList.push_back(ptr->val);
        }
        else
        {
            argsList.push_back(n->next[i]->val);
        }
    }
    return argsList;
}

int eval(node* n)
{
    //now figure out what op to do, because we use strings, we have to use if, luckily, large if's
    //are converted to a jump table for us by the compiler
    if(n->val == "+")
    {
        return add(buildNumList(n));
    }
    else if(n->val == "-")
    {
        return sub(buildNumList(n));
    }
    else if(n->val == "*")
    {
        return mul(buildNumList(n));
    }
    else if(n->val == "/")
    {
        return div(buildNumList(n));
    }
    else if(n->val == "%")
    {
        return mod(buildNumList(n));
    }
    else if(n->val == "^")
    {
        return pow(buildNumList(n));
    }
    else if(n->val == "&")
    {
        return _and(buildNumList(n));
    }
    else if(n->val == "|")
    {
        return _or(buildNumList(n));
    }
    else if(n->val == "!")
    {
        return _not(buildNumList(n));
    }
    else if(n->val == "<")
    {
        return _lt(buildNumList(n));
    }
    else if(n->val == ">")
    {
        return _gt(buildNumList(n));
    }
    else if(n->val == "=")
    {
        return _eq(buildNumList(n));
    }
    else if(n->val == "print")
    {
        return print(buildArgsList(n));
    }
    else if(n->val == "if")
    {
        if(eval(n->next[0]))
            return eval(n->next[1]);
        else
            return eval(n->next[2]);
    }
    else if(n->val == "let")
    {
        if(n->next[1]->val == "eval")
        {
            node* ev = new node;
            ev->type = ATOM;
            ev->val = convertInt(eval(n->next[1]));
            vars[n->next[0]->val] = ev;
        }
        else
        {
            vars[n->next[0]->val] = n->next[1];
        }
    }
    else if(n->val == "eval")
    {
        if(n->next[0]->type == VAR)
        {
            std::string key = n->next[0]->val;
            return eval(vars[key]);
        }
        else
        {
            return eval(n->next[0]);
        }
    }
    else //if we fucked up, then just try to return the identity of the current node
    {
        std::vector<int> identity = buildNumList(n);
        return identity[0];
    }
    
    return 0;
}

int add(std::vector<int> numList)
{
    int tmp = numList[0];
    for(int i = 1; i < numList.size(); i++)
    {
        tmp = tmp + numList[i];
    }
    return tmp;
}

int sub(std::vector<int> numList)
{
    int tmp = numList[0];
    for(int i = 1; i < numList.size(); i++)
    {
        tmp = tmp - numList[i];
    }
    return tmp;
}

int mul(std::vector<int> numList)
{
    int tmp = numList[0];
    for(int i = 1; i < numList.size(); i++)
    {
        tmp = tmp * numList[i];
    }
    return tmp;
}

int div(std::vector<int> numList)
{
    int tmp = numList[0];
    for(int i = 1; i < numList.size(); i++)
    {
        tmp = tmp / numList[i];
    }
    return tmp;
}

int mod(std::vector<int> numList)
{
    int tmp = numList[0];
    for(int i = 1; i < numList.size(); i++)
    {
        tmp = tmp % numList[i];
    }
    return tmp;
}

int pow(std::vector<int> numList)
{
    int tmp = numList[0];
    for(int i = 1; i < numList.size(); i++)
    {
        tmp = pow(tmp, numList[i]);
    }
    return tmp;
}

int print(std::vector<std::string> argsList)
{
    std::string tmp = "";
    for(int i = 0; i < argsList.size(); i++)
    {
        //strip out the quotation marks
        if(argsList[i][0] == '"')
            tmp = argsList[i].substr(1, argsList[i].size() - 2);
        else
            tmp = argsList[i];
        std::cout << tmp;
    }
    std::cout << std::endl; //start a new line so it doesn't look like we tacked on a 0 to the string.
    return 0;
}

int _and(std::vector<int> numList)
{
    bool b = convertIntToBool(numList[0]);
    for(int i = 1; i < numList.size(); i++)
    {
        b = b && convertIntToBool(numList[i]);
    }
    return b;
}

int _or(std::vector<int> numList)
{
    bool b = convertIntToBool(numList[0]);
    for(int i = 1; i < numList.size(); i++)
    {
        b = b || convertIntToBool(numList[i]);
    }
    return b;
}


//the following take a specific number of arguments
int _not(std::vector<int> numList)
{
    return !convertIntToBool(numList[0]);
}

int _lt(std::vector<int> numList)
{
    return numList[0] < numList[1];
}

int _gt(std::vector<int> numList)
{
    return numList[0] > numList[1];
}

int _eq(std::vector<int> numList)
{
    return numList[0] == numList[1];
}

bool convertIntToBool(int val)
{
    return !!val;
}