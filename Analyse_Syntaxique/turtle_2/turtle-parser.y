    %{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  const char *name;
  const char *turtle_var;
  const char *colour_name_value;

  struct ast_node *node;
}

%token <value>                              VALUE                   "value"
%token <colour_name_value>                  COLOUR_NAME_VALUE       "colour_name_value"
%token <name>                               NAME                    "name"
%token <turtle_var>                         TURTLE_VAR              "turtle_var"

%token            COS      "cos"
%token            SIN      "sin"
%token            TAN      "tan"
%token            SQRT     "sqrt"
%token            POW      "pow"
%token            RANDOM   "random"


%token            KW_RIGHT  "right"
%token            KW_LEFT   "left"
%token            KW_HEADING "heading"

%token            KW_UP     "up"
%token            KW_DOWN   "down"
%token            KW_PRINT  "print"


%token            KW_FORWARD    "forward"
%token            KW_BACKWARD   "backward"
%token            KW_POSITION   "position"
%token            KW_COLOUR     "colour"

%token            KW_REPEAT     "repeat"
%token            KW_SET        "set"
%token            KW_PROC       "proc"
%token            KW_CALL       "call"



%left '+' '-'
%left '*' '/'


/* TODO: add other keywords */

%type <node> unit cmds cmd expr_literal expr_primary expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_COLOUR expr              { $$ = make_colour_cmd($2); }
    | KW_FORWARD expr               { $$ = make_move_cmd_one($2, 0); }
    | KW_BACKWARD expr               { $$ = make_move_cmd_one($2, 1); }
    | KW_POSITION expr ',' expr       { $$ = make_move_cmd_two($2, $4, 0); }
    | KW_LEFT expr                    { $$ = make_orientation_cmd($2, 0); }
    | KW_RIGHT expr                    { $$ = make_orientation_cmd($2, 1); }
    | KW_HEADING expr                    { $$ = make_orientation_cmd($2, 2); }
    | '{' cmds '}'                        { $$ = make_cmd_bloc($2); }


;

expr_literal:
    VALUE                 { $$ = make_expr_value($1); }
    | NAME                { $$ = make_expr_name($1); }
    | COLOUR_NAME_VALUE   { $$ = make_expr_colour($1);}
    | TURTLE_VAR            { $$ = make_turtle_var($1); }

;

expr_primary:
    expr_literal        { $$ = $1; }
    | COS '(' expr ')' { $$ = make_func_one_arg($3, 0); }
    | SIN '(' expr ')' { $$ = make_func_one_arg($3, 1); }
    | TAN '(' expr ')' { $$ = make_func_one_arg($3, 2); }
    | SQRT '(' expr ')' { $$ = make_func_one_arg($3, 3); }
    | POW '(' expr ',' expr ')' {$$ = make_func_two_args($3, $5, 0); }
    | RANDOM '(' expr ',' expr ')' {$$ = make_func_two_args($3, $5, 1); }


    /* TODO: add internal functions */
;

expr:
    expr_primary      { $$ = $1; }
    | expr '+' expr     { $$ = make_operande_exp($1, $3, '+'); }
    | expr '-' expr     { $$ = make_operande_exp($1, $3, '-'); }
    | expr '*' expr     { $$ = make_operande_exp($1, $3, '*'); }
    | expr '/' expr     { $$ = make_operande_exp($1, $3, '/'); }
    | '(' expr ')'       { $$ = make_parenthesis_exp($2); }
    | '-' expr %prec '-'  { $$= make_unary_exp($2); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
