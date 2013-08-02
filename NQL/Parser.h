//
//  Parser.h
//  my_simple_lisp
//
//  Created by Damon Swayn on 29/07/13.
//  Copyright (c) 2013 Damon Swayn. All rights reserved.
//

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stack>
#include <math.h>
#include <iostream>
#include <sstream>
#include <map>
#include "ast.h"

std::string convertInt(int number);
std::vector<int> buildNumList(node* n);
std::vector<std::string> buildArgsList(node* n);
int eval(node* n);
int add(std::vector<int> numList);
int sub(std::vector<int> numList);
int mul(std::vector<int> numList);
int div(std::vector<int> numList);
int mod(std::vector<int> numList);
int pow(std::vector<int> numList);
int _and(std::vector<int> numList);
int _or(std::vector<int> numList);
int _not(std::vector<int> numList);
int _lt(std::vector<int> numList);
int _gt(std::vector<int> numList);
int _eq(std::vector<int> numList);
int print(std::vector<std::string> numList);
bool convertIntToBool(int val);
#endif
