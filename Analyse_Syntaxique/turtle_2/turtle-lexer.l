%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT             [0-9]
NUMBER            (0+|[1-9][0-9]*)([.][0-9]*([eE][-+][0-9]+)?)?
COLOUR_NAME       red|green|blue|black|gray|cyan|yellow|magenta|Red|Green|Blue|Black|Gray|Cyan|Yellow|Magenta|RED|GREEN|BLUE|BLACK|GRAY|CYAN|YELLOW|MAGENTA

%%

"forward"|"fw"        { return KW_FORWARD; }
"bw"|"backward"       { return KW_BACKWARD; }
"rt"|"right"	        { return KW_RIGHT; }
"lt"|"left"	          { return KW_LEFT; }
"up"		              { return KW_UP; }
"dw"|"down"	          { return KW_DOWN; }
"hd"|"heading" 	      { return KW_HEADING; }
"+"           	      { return '+'; }
"-"           	      { return '-'; }
"*"           	      { return '*'; }
"/"           	      { return '/'; }
"color"|"colour"      { return KW_COLOUR; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
{NUMBER}              { yylval.value = strtod(yytext, NULL); return VALUE; }

{COLOUR_NAME}         { yylval.colour_name_value = strdup(yytext); return COLOUR_NAME_VALUE;}

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
