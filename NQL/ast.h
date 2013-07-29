//
//  ast.h
//  my_simple_lisp
//
//  Created by Damon Swayn on 24/07/13.
//  Copyright (c) 2013 Damon Swayn. All rights reserved.
//

#ifndef AST_H
#define AST_H

#include <string>
#include <stack>
#include <vector>
#include <algorithm>

enum NODE_TYPE {
    SYMBOL,
    ATOM,
    BLOCKSTART,
    BLOCKEND,
    VAR
    };

typedef struct node
{
    NODE_TYPE type;
    std::string val;
    std::vector<node*> next; //there can be more than one argument
};

bool isAtom(std::string token);
node* buildTree(std::vector<std::string> tokens);

#endif
