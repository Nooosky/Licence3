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

%token <value>                VALUE                 "value"
%token <name>                 NAME                  "name"
%token <turtle_var>           TURTLE_VAR            "turtle_var"

%token        COS       "cos"
%token        SIN       "sin"
%token        TAN       "tan"
%token        SQRT      "sqrt"
%token        POW       "pow"
%token        RANDOM    "random"

%token      KW_FORWARD      "forward"
%token      KW_BACKWARD     "backward"
%token      KW_POSITION     "position"
%token      KW_LEFT         "left"
%token      KW_RIGHT        "right"
%token      KW_HEADING      "heading"
%token      KW_UP           "up"
%token      KW_DOWN         "down"
%token      KW_PRINT        "print"
%token      KW_COLOUR       "colour"

%token      KW_REPEAT       "repeat"
%token      KW_PROC         "proc"
%token      KW_SET          "set"
%token      KW_CALL         "call"

/* TODO: add other keywords */

%left '+' '-'
%left '*' '/'


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
    KW_FORWARD expr   { $$ = make_cmd_one("forward", $2); }
    | KW_BACKWARD expr   { $$ = make_cmd_one("backward", $2); }
    | KW_POSITION expr ',' expr   { $$ = make_cmd_two("position", $2, $4); }
    | KW_LEFT expr   { $$ = make_cmd_one("left", $2); }
    | KW_RIGHT expr   { $$ = make_cmd_one("right", $2); }
    | KW_HEADING expr   { $$ = make_cmd_one("heading", $2); }
    | KW_UP              {$$ = make_cmd_zero("up");}
    | KW_DOWN              {$$ = make_cmd_zero("down");}
    | KW_PRINT              {$$ = make_cmd_zero("print");}
    | KW_COLOUR RED     { $$ = make_cmd_three(make_expr_value(1.0), make_expr_value(0.0), make_expr_value(0.0)); }
    | KW_COLOUR GREEN     { $$ = make_cmd_three(make_expr_value(0.0), make_expr_value(1.0), make_expr_value(0.0)); }
    | KW_COLOUR BLUE     { $$ = make_cmd_three(make_expr_value(0.0), make_expr_value(0.0), make_expr_value(1.0)); }
    | KW_COLOUR BLACK     { $$ = make_cmd_three(make_expr_value(0.0), make_expr_value(0.0), make_expr_value(0.0)); }
    | KW_COLOUR GRAY     { $$ = make_cmd_three(make_expr_value(0.5), make_expr_value(0.5), make_expr_value(0.5)); }
    | KW_COLOUR CYAN     { $$ = make_cmd_three(make_expr_value(0.0), make_expr_value(1.0), make_expr_value(1.0)); }
    | KW_COLOUR YELLOW     { $$ = make_cmd_three(make_expr_value(1.0), make_expr_value(0.0), make_expr_value(1.0)); }
    | KW_COLOUR MAGENTA     { $$ = make_cmd_three(make_expr_value(1.0), make_expr_value(1.0), make_expr_value(0.0)); }
    | KW_COLOUR WHITE     { $$ = make_cmd_three(make_expr_value(1.0), make_expr_value(1.0), make_expr_value(1.0)); }

;

expr_literal:
    VALUE             { $$ = make_expr_value($1); }
    | NAME            { $$ = make_expr_name($1); }

    /* TODO: add identifier */
;

expr_primary:
    expr_literal        { $$ = $1; }
    | COS '(' expr ')'  { $$ = make_cmd_one("cos", $3); }
    | SIN '(' expr ')'  { $$ = make_cmd_one("sin", $3); }
    | TAN '(' expr ')'  { $$ = make_cmd_one("tan", $3); }
    | SQRT '(' expr ')'  { $$ = make_cmd_one("sqrt", $3); }
    | POW '(' expr ')'  { $$ = make_cmd_one("pow", $3); }
    | RANDOM '(' expr ')'  { $$ = make_cmd_one("random", $3); }

    /* TODO: add internal functions */
;

expr:
    expr_primary      { $$ = $1; }
    | expr '+' expr   { $$ = make_operande_exp($1, $3, '+'); }
    | expr '-' expr   { $$ = make_operande_exp($1, $3, '-'); }
    | expr '/' expr   { $$ = make_operande_exp($1, $3, '/'); }
    | expr '*' expr   { $$ = make_operande_exp($1, $3, '*'); }
    | '(' expr ')'    { $$ = $2; }
    | '-' expr %prec '-' {$$ = make_unary_exp($2); }

;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
