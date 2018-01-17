%{
#include <stdio.h>
#include <stdlib.h>
%}

%option warn 8bit nodefault noyywrap


INTEGER         (0+|[1-9][0-9]*)
TRUE            True|TRUE|true
FALSE           False|FALSE|false
HEXA            0[xX][a-fA-F0-9]{1,8}
FLOAT           (0+|[1-9][0-9]*)([.][0-9]*([eE][-+][0-9]+)?)?
TURTLE          PI|I|CIRCLE|POLY5
CID             [a-zA-Z_][a-zA-Z0-9_]*

%%


{INTEGER}               { printf("Integer: %s\n", yytext); }
{TRUE}                  { printf("Boolean: %s\n", yytext); }
{FALSE}                 { printf("Boolean: %s\n", yytext); }
{HEXA}                  { printf("Hexa value: %s\n", yytext); }
{FLOAT}                 { printf("Float value: %s\n", yytext); }
{TURTLE}                { printf("TURTLE Procedure identifier: %s\n", yytext); }
{CID}                   { printf("C identifier: %s\n", yytext); }


[\n\t ]*  /* nothing */
.         { fprintf(stderr, "Unknown token: '%s'\n", yytext); ; exit(EXIT_FAILURE); }

%%
