#include "ast.h"
#include <algorithm>

//if a token is surrounded by quotes then we'll treat it as an atom to keep everything working as is
bool isAtom(std::string token)
{
    if(std::all_of(token.begin(), token.end(), ::isdigit))
        return true;
    else if(token[0] == '"' && token[token.size() - 1] == '"')
        return true;
    else if(token == "t" || token == "f")
        return true;
    return false;
}



//I DON'T FUCKING CARE MY AST FUCKING WORKS MOTHERFUCKERS!
node* buildTree(std::vector<std::string> tokens)
{
    node* tree = NULL;
    std::vector<node*> nodeList;
    for(int i = 0; i < tokens.size(); i++)
    {
        node* tmp = new node;
        tmp->val = tokens[i];
        
        if(tokens[i] == "(")
        {
            tmp->type = BLOCKSTART;
        }
        else if(tokens[i] == ")")
        {
            tmp->type = BLOCKEND;
        }
        //seems a little perl-ish but if a token has a $ at the start we will call that a variable
        else if(tokens[i][0] == '$')
        {
            tmp->type = VAR;
            tmp->val = tokens[i].substr(1, tokens[i].size() - 1);
        }
        else if(isAtom(tokens[i]))
        {
            //convert true/false values into internal numerical representation
            if(tokens[i] == "t")
                tmp->val = "1";
            else if(tokens[i] == "f")
                tmp->val = "0";
            
            tmp->type = ATOM;
        }
        else
        {
            tmp->type = SYMBOL;
        }
        nodeList.push_back(tmp);
    }
    
    //we can assume that the first value in the tree will be a BLOCKSTART symbol therefore tree root
    //will always be nodeList[1]
    tree = nodeList[1];
    std::stack<node*> stk;
    node* ptr = tree;
    for(int i = 2; i < nodeList.size(); i++)
    {
        if(nodeList[i]->type == BLOCKSTART)
        {
            ptr->next.push_back(new node); //create blank node to move to
            stk.push(ptr); //push the current ptr to the stack
            ptr = ptr->next[ptr->next.size() - 1]; //the blank node will be the last in the list
        }
        else if(nodeList[i]->type == BLOCKEND)
        {
            if(stk.size() > 0)
            {
                ptr = stk.top();
                stk.pop();
            }
        }
        else if (nodeList[i]->type == SYMBOL)
        {
            ptr->val = nodeList[i]->val;
            ptr->type = SYMBOL;
        }
        else //ATOM
        {
            ptr->next.push_back(nodeList[i]);
        }
    }
    
    return tree;
}
