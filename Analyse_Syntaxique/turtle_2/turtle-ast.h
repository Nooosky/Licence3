#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>


int rand_a_b(int a, int b);


// simple commands
enum ast_cmd {
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_LEFT,
  CMD_RIGHT,
  CMD_UP,
  CMD_DOWN,
  CMD_HEADING,
  CMD_COLOUR,
  CMD_POSITION,
  CMD_PRINT,
  // TODO: add simple commands
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_SIN,
  FUNC_TAN,
  FUNC_SQRT,
  FUNC_POW,
  FUNC_RANDOM,
  // TODO: add other functions
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,


  KIND_EXPR_VALUE,
  KIND_EXPR_FUNC,
  KIND_EXPR_BINOP,
  KIND_EXPR_COLOUR_VALUE,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
  KIND_EXPR_UNA,

};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // the command if it is simple (KIND_CMD_SIMPLE)
    double value;       // the value for literals
    char op;            // the operator for expressions
    const char *name;   // the name for procedures and variables
    enum ast_func func; // the command if
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};


// TODO: make some constructors to use in parser.y
// for example:

struct ast_node *make_expr_value(double value);

struct ast_node *make_expr_colour(const char* colour_name);


struct ast_node *make_move_cmd_one(struct ast_node *node_fils, int mode);
struct ast_node *make_move_cmd_two(struct ast_node *node_fils1, struct ast_node *node_fils2, int mode);

struct ast_node *make_orientation_cmd(struct ast_node *node_fils, int mode);

struct ast_node *make_colour_cmd(struct ast_node *node_fils);
struct ast_node *make_operande_exp(struct ast_node *node_fils1, struct ast_node *node_fils2, char operande);
struct ast_node *make_turtle_var(const char *turtle_var);

struct ast_node *make_parenthesis_exp(struct ast_node *node_fils);

struct ast_node *make_func_one_arg(struct ast_node *node_fils, int mode);
struct ast_node *make_func_two_args(struct ast_node *node_fils1, struct ast_node *node_fils2, int mode);

struct ast_node *make_expr_name(const char *expr_name);
struct ast_node *make_unary_exp(double value);



// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);

// the execution context
struct context {
  double x;
  double y;
  double angle;
  bool up;

  // TODO: add procedure handling
  // TODO: add variable handling
};

// create an initial context
void context_create(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);

#endif /* TURTLE_AST_H */
