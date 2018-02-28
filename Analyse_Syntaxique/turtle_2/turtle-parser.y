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
  const char *colour_name_value;
  struct ast_node *node;
}

%token <value>                  VALUE       "value"
%token <colour_name_value>      COLOUR_NAME_VALUE      "colour_name_value"
%token <name>                   NAME        "name"

%token            KW_FORWARD    "forward"
%token            KW_LEFT       "left"
%token            KW_UP         "up"
%token            KW_DOWN       "down"
%token            KW_RIGHT      "right"
%token            KW_BACKWARD   "backward"
%token            KW_HEADING    "heading"
%token            KW_COLOUR     "colour"



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
    KW_FORWARD expr               { $$ = make_cmd($2, "forward"); }
    | KW_RIGHT expr               { $$ = make_cmd($2, "right"); }
    | KW_LEFT expr                { $$ = make_cmd($2, "left"); }
    | KW_HEADING expr             { $$ = make_cmd($2, "heading"); }
    | KW_BACKWARD expr            { $$ = make_cmd($2, "backward"); }
    | KW_UP                       { $$ = make_pen_cmd("up"); }
    | KW_DOWN                     { $$ = make_pen_cmd("down"); }
    | KW_COLOUR expr              { $$ = make_colour_cmd_one($2); }

;

expr_literal:
    VALUE                 { $$ = make_expr_value($1); }
    | COLOUR_NAME_VALUE   { $$ = make_expr_colour($1); }
    /* TODO: add identifier */
;

expr_primary:
    expr_literal        { $$ = $1; }
    | expr '+' expr     { $$ = make_operande_exp($1, $3, '+'); }
    | expr '-' expr     { $$ = make_operande_exp($1, $3, '-'); }
    | expr '/' expr     { $$ = make_operande_exp($1, $3, '/'); }
    | expr '*' expr     { $$ = make_operande_exp($1, $3, '*'); }

    /* TODO: add internal functions */
;

expr:
    expr_primary      { $$ = $1; }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
