%{
#include <stdio.h>
#include <stdlib.h>
%}

%option warn 8bit nodefault noyywrap

HEXA     0x[0-9a-fA-F]+
DIGIT    [0-9]
TRUE     true
FALSE    false
FLOAT    [0-9]*({.{[0-9]*}}|([eE]{[-+]}))[0-9]*
TURTLE   I|PI|CIRCLE|POLY5
CID      [a-zA-Z\_][a-zA-Z0-9\_]*

%%

{HEXA}+   { printf("Hexa value: %s\n", yytext);}
{FLOAT}+   { printf("Float value: %s\n", yytext);}
{DIGIT}+  { printf("Integer: %i (%s)\n", atoi(yytext), yytext); }
{TRUE}+   { printf("Boolean True\n");}
{FALSE}+   { printf("Boolean False\n");}
{TURTLE}+  { printf("Turtle (%s)\n", yytext); }
{CID}+     { printf("C identifier: %s\n", yytext);}
[\n\t ]*  /* nothing */
.         { fprintf(stderr, "Unknown token: '%s'\n", yytext); ; exit(EXIT_FAILURE); }

%%

/*
0 123 10000 0x0 0x29A 0xDeadBeef 500. 500.0 5e2 5E2 5e+2 0.05 .05 5e-2 5.0e-2 I PI CIRCLE POLY5 foo foo2 _foo foo_bar Foo42Bar43

*/
