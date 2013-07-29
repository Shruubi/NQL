//
//  Tokenizer.h
//  my_simple_lisp
//
//  Created by Damon Swayn on 29/07/13.
//  Copyright (c) 2013 Damon Swayn. All rights reserved.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

std::vector<std::string> readAndTokenize(std::string code);
std::string format(std::string code);

#endif
