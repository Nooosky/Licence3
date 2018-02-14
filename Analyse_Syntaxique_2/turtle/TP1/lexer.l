%{
#include <stdio.h>
#include <stdlib.h>
%}

%option warn 8bit nodefault noyywrap


INTEGER           (0+|[1-9][0-9]*)
COLOR             red|green|blue|black|gray|cyan|yellow|magenta|Red|Green|Blue|Black|Gray|Cyan|Yellow|Magenta|RED|GREEN|BLUE|BLACK|GRAY|CYAN|YELLOW|MAGENTA
FORWARD_KW        fw|forward
BACKWARD_KW       bw|backward
RIGHT_KW          rt|right
LEFT_KW           lt|left
UP_KW             up
DOWN_KW           dw|down
HEADING_KW        hd|heading
TURTLE_VAR        PI|SQRT2|SQRT3
NUMBER            (0+|[1-9][0-9]*)([.][0-9]*([eE][-+][0-9]+)?)?
COMMENT           #.*\n

%%


{INTEGER}               { printf("Integer: %s\n", yytext); return yytext;}
{COLOR}                 { printf("Color value: %s\n", yytext); return yytext;}
{BACKWARD_KW}           { printf("Backward keyword: %s\n", yytext); return yytext;}
{RIGHT_KW}              { printf("Direction keyword: %s\n", yytext); return yytext;}
{LEFT_KW}               { printf("Direction keyword: %s\n", yytext); return yytext;}
{UP_KW}                 { printf("Direction keyword: %s\n", yytext); return yytext;}
{DOWN_KW}               { printf("Direction keyword: %s\n", yytext); return yytext;}
{HEADING_KW}            { printf("Heading keyword: %s\n", yytext); return yytext;}
{TURTLE_VAR}            { printf("Turtle keyword: %s\n", yytext); return yytext;}
{COMMENT}               { printf("Comment: %s\n", yytext); return yytext;}
{NUMBER}                { printf("Float value: %s\n", yytext); return yytext;}
'fw'|'forward'          { return "forward_kw"; }
"("                     { return '('; }
")"                     { return ')'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"color"                 { return 'color'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
"repeat"                { return 'repeat'; }
"set"                   { return 'set'; }
"call"                  { return 'call'; }
"proc"                  { return 'proc'; }
"print"                 { return 'print'; }



[\n\t ]*  /* nothing */
.         { fprintf(stderr, "Unknown token: '%s'\n", yytext); ; exit(EXIT_FAILURE); }

%%
