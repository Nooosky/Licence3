#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// simple commands
enum ast_cmd {
  CMD_FORWARD,
  CMD_LEFT,
  CMD_RIGHT,
  CMD_UP,
  CMD_HEADING,
  CMD_DOWN,
  CMD_BACKWARD,
  CMD_COLOUR,
  // TODO: add simple commands
};

// internal functions
enum ast_func {
  FUNC_COS,
  // TODO: add other functions
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  // TODO: add non-simple commands: repeat, block, proc, call, set

  KIND_EXPR_VALUE,
  KIND_EXPR_BINOP,
  // TODO: add expressions kind: func, binop, block, name
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


struct ast_node *make_cmd(struct ast_node *node_fils, char * name);

struct ast_node *make_pen_cmd(char * name);

struct ast_node *make_colour_cmd_one(struct ast_node *node_fils);
struct ast_node *make_colour_cmd_three(struct ast_node *node_r, struct ast_node *node_g, struct ast_node *node_b);

struct ast_node *make_operande_exp(struct ast_node *node_fils1, struct ast_node *node_fils2, char operande);

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
