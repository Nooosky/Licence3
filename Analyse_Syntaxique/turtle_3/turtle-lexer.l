%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT               [0-9]
NUMBER              (0+|[1-9][0-9]*)([.][0-9]*([eE][-+][0-9]+)?)?
ID                  [A-Z][A-Z0-9]*

%%

"("       { return "("; }
")"       { return ")"; }
"+"       { return "+"; }
"-"       { return "-"; }
"*"       { return "*"; }
"/"       { return "/"; }
","       { return ","; }
"{"       { return "{"; }
"}"       { return "}"; }

"sin"     { return "SIN"; }
"cos"     { return "COS"; }
"tan"     { return "TAN"; }
"sqrt"    { return "SQRT"; }
"pow"     { return "POW"; }
"random"  { return "RANDOM"; }

"forward"|"fw"            { return KW_FORWARD; }
"backward"|"bw"           { return KW_BACKWARD; }
"position"|"pos"          { return KW_POSITION; }
"left"|"lt"               { return KW_LEFT; }
"right"|"rt"              { return KW_RIGHT; }
"heading"|"hd"            { return KW_HEADING; }
"up"                      { return KW_UP; }
"down"|"dw"               { return KW_DOWN; }
"print"                   { return KW_PRINT; }
"color"|"colour"          { return KW_COLOUR; }

"repeat"|"rp"             { return KW_REPEAT; }
"proc"                    { return KW_PROC; }
"set"                     { return KW_SET; }
"call"                    { return KW_CALL; }

"red"|"Red"|"RED"             { return RED; }
"green"|"Green"|"GREEN"       { return GREEN; }
"blue"|"Blue"|"BLUE"          { return BLUE; }
"black"|"Black"|"BLACK"       { return BLACK; }
"gray"|"Gray"|"GRAY"          { return GRAY; }
"cyan"|"Cyan"|"CYAN"          { return CYAN; }
"yellow"|"Yellow"|"YELLOW"    { return YELLOW; }
"magenta"|"Magenta"|"MAGENTA" { return MAGENTA; }
"white"|"White"|"WHITE"       { return WHITE; }

"PI"|"SQRT2"|"SQRT3"        { return TURTLE_VAR; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
{NUMBER}              { yylval.value = strtod(yytext, NULL); return VALUE; }
{ID}+                 { yylval.name = strdup(yytext); return NAME; }

{COLOUR_NAME}         { yyval.colour_name_value = strdup(yytext); return COLOUR_NAME_VALUE; }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
