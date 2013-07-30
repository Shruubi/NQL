NQL
===

Not Quite Lisp, a kinda-sorta Lisp like language.

About
=====

NQL was born out of boredom while waiting for my next class and is my first attempt
at building a working Abstract Syntax Tree. It represents a days worth of effort and
a few hacks to get a working language. I implemented this purely as an experiment and
while it probably isn't very good (I would expect a lot of criticism), I've learnt
quite a few cool things, and accidentally built a design that seems to work very well
in certain area's.

Quick Tute
==========

We have the basic math operands (+, -, *, /) as well as modulo (%) and exponent (^).
All math operands bar the exponent operator can have a variable amount of arguments i.e -

'''
(+ 2 2)
'''

 is just as valid as 

'''
(+ 2 2 2 2 2 2 2 2 2).
'''

There are also the following boolean operands (&, |, !, <, >, =) which represent logical
and, or and not respectively as well as the binary comparison operators less than,
greater than and equals respectively. And, or, not, greater than, less than and equals
all take two arguments whilst not only takes one.

The only conditional operator is if. It evaluates the first block, and if it evaluates
to true, then the second block is executed, otherwise the third block is executed. i.e - 

'''
(if (< 3 5) (print "less than") (print "greater than")) 
'''

will cause the REPL to print "less than".

print is the only output function you have available, it takes a variable number of
arguments and will print them onto the stdout. If variables are supplied, print will
replace them with appropriate values.

let allows you to define variables. Variables are denoted as starting with a $ character
and all variables are treated as globals (i.e - no scoping). i.e - 

'''
(let $x 5) 
'''

would define $x as the atom 5.

It is possible to define functions, because I am lazy functions came about as a byproduct
of the existing code and how code is evaluated. If you provide let with a block instead
of an atom, then the variable you define will point to the start of that block. i.e - 

'''
(let $x (+ 2 2)) 
'''

stores the block 

'''
(+ 2 2) 
'''

in the variable x, and can be evaluated by calling 

'''
(eval $x) 
'''

which will return 4.

For functions which operate on variables, another funny side effect of the code design
is that you can define a function as such - 

'''
(let $func (+ $x $y))
'''

 And so long as you define $x and $y you can call the function like you would evaluating a  regular 
block i.e - 

'''
(let $func (+ $x $y))
(let $x 5)
(let $x 4)
(eval $func)
'''

will result in 9 being printed.
