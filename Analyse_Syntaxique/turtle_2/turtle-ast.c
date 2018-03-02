#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define SQRT2 1.4142135623730951
#define SQRT3 1.732050807568877



int rand_a_b(int a, int b){
    return rand()%(b-a) + a ;
}


//VALUE 1, 3 etc....
struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}


//TURTLE VAR PI, SQRT2, SQRT3, etc...
struct ast_node *make_turtle_var(const char *turtle_var) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  if(strcmp("PI", turtle_var)== 0){
    node->u.value = PI;
  }else if(strcmp("SQRT2", turtle_var)==0){
    printf("NANI THE FUCK\n");
    node->u.value = 1.4142135623730951;
  }else if(strcmp("SQRT3", turtle_var) == 0){
    node->u.value = 1.732050807568877;
  }
  printf("%f\n", node->u.value);
  return node;
}


//COLOUR
struct ast_node *make_expr_colour(const char* colour_name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_COLOUR_VALUE;
  printf("%d\n", strcmp("red", colour_name));
  if(strcmp("red", colour_name) == 0 | strcmp("Red", colour_name) == 0 | strcmp("RED", colour_name) == 0){
    node->u.value = 0;
  }else if(strcmp("green", colour_name) == 0| strcmp("Green", colour_name) == 0| strcmp("GREEN", colour_name) == 0){
    node->u.value = 1;
  }else if(strcmp("blue", colour_name) == 0 | strcmp("Blue", colour_name) == 0 | strcmp("BLUE", colour_name) == 0){
    node->u.value = 2;
  }else if(strcmp("black", colour_name) == 0 | strcmp("Black", colour_name) == 0 | strcmp("BLACK", colour_name) == 0){
    node->u.value = 3;
  }else if(strcmp("gray", colour_name) == 0 | strcmp("Gray", colour_name) == 0 | strcmp("GRAY", colour_name) == 0){
    node->u.value = 4;
  }else if(strcmp("cyan", colour_name) == 0 | strcmp("Cyan", colour_name) == 0 | strcmp("CYAN", colour_name) == 0){
    node->u.value = 5;
  }else if(strcmp("yellow", colour_name) == 0 | strcmp("Yellow", colour_name) == 0 | strcmp("YELLOW", colour_name) == 0){
    node->u.value = 6;
  }else if(strcmp("magenta", colour_name) == 0 | strcmp("Magenta", colour_name) == 0 | strcmp("MAGENTA", colour_name) == 0){
    node->u.value = 7;
  }else if(strcmp("white", colour_name) == 0 | strcmp("White", colour_name) == 0 | strcmp("WHITE", colour_name) == 0){
    node->u.value = 8;
  }

  return node;
}


struct ast_node *make_move_cmd_one(struct ast_node *node_fils, int mode) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  if(mode == 0){
    node->u.cmd = CMD_FORWARD;
  }else if(mode == 1){
    node->u.cmd = CMD_BACKWARD;
  }

  node->children[node->children_count] = node_fils;
  node->children_count ++;
  return node;
}

struct ast_node *make_move_cmd_two(struct ast_node *node_fils1, struct ast_node *node_fils2, int mode) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  if(mode == 0){
    node->u.cmd = CMD_POSITION;
  }

  node->children[node->children_count] = node_fils1;
  node->children_count ++;
  node->children[node->children_count] = node_fils2;
  node->children_count ++;
  return node;
}

struct ast_node *make_orientation_cmd(struct ast_node *node_fils, int mode) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  if(mode == 0){
    node->u.cmd = CMD_LEFT;
  }else if(mode == 1){
    node->u.cmd = CMD_RIGHT;
  }else if(mode == 2){
    node->u.cmd = CMD_HEADING;
  }

  node->children[node->children_count] = node_fils;
  node->children_count ++;
  return node;
}

struct ast_node *make_colour_cmd(struct ast_node *node_fils) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOUR;

  node->children[node->children_count] = node_fils;
  node->children_count ++;
  return node;
}


struct ast_node *make_operande_exp(struct ast_node *node_fils1, struct ast_node *node_fils2, char operande) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BINOP;
  if(operande == '+'){
    node->u.value = node_fils1->u.value + node_fils2->u.value;
    node->u.op = operande;
  }else if(operande == '/'){
    node->u.value = node_fils1->u.value / node_fils2->u.value;
    node->u.op = operande;
  }else if(operande == '-'){
    node->u.value = node_fils1->u.value - node_fils2->u.value;
    node->u.op = operande;
  }else if(operande == '*'){
    node->u.value = node_fils1->u.value * node_fils2->u.value;
    node->u.op = operande;
  }else{
    printf("ERROR\n");
  }
  node->children_count = 2;
  node->children[0] = node_fils1;
  node->children[1] = node_fils2;
  return node;
}

struct ast_node *make_parenthesis_exp(struct ast_node *node_fils) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));

  node->kind = KIND_EXPR_VALUE;
  node->u.value = node_fils->u.value;
  node->children[node->children_count] = node_fils;
  node->children_count ++;

  printf("%f\n", node->u.value);

  return node;
}

struct ast_node *make_func_one_arg(struct ast_node *node_fils, int mode) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_FUNC;

  if(mode == 0){
    node->u.func = FUNC_COS;
    float x = PI / 180.0;
    node->u.value = cos(x*node_fils->u.value);
  }
  if(mode == 1){
    node->u.func = FUNC_SIN;
    float x = PI / 180.0;
    node->u.value = sin(x*node_fils->u.value);
  }
  if(mode == 2){
    node->u.func = FUNC_TAN;
    float x = PI / 180.0;
    node->u.value = tan(x*node_fils->u.value);
  }
  if(mode == 3){
    node->u.func = FUNC_SQRT;
    node->u.value = sqrt(node_fils->u.value);
  }
  node->children[node->children_count] = node_fils;
  node->children_count ++;

  printf("%f\n", node->u.value);

  return node;
}


struct ast_node *make_func_two_args(struct ast_node *node_fils1, struct ast_node *node_fils2, int mode) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_FUNC;

  if(mode == 0){
    node->u.func = FUNC_POW;
    node->u.value = pow(node_fils1->u.value, node_fils2->u.value);
  }
  if(mode == 1){
    node->u.func = FUNC_RANDOM;
    node->u.value = rand_a_b(node_fils1->u.value, node_fils2->u.value);
  }

  node->children[node->children_count] = node_fils1;
  node->children_count ++;

  node->children[node->children_count] = node_fils2;
  node->children_count ++;

  printf("%f\n", node->u.value);

  return node;
}

struct ast_node *make_expr_name(const char *expr_name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->u.name = expr_name;

  return node;
}

struct ast_node *make_unary_exp(struct ast_node* expr) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_UNA;
  node->u.op = '-'

  node->children_count++;
  node->children[node->children_count] = expr;
  
  return node;
}




void ast_destroy(struct ast *self) {
  printf("TATATATAT\n");
  printf("%d\n", self->unit->children[0]->kind);
}

/*
 * context
 */

void context_create(struct context *self) {
  self->x = 0.;
  self->y = 0.;
  self->angle = 0;
  self->up = true;
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */

void print_second(const struct ast_node *self){
  if(self->children_count == 0){
    //value or color
    int kind = self->kind;
    if(kind == 2){
      //expr value
      printf("%f\n", self->u.value);
    }else if(kind == 4){
      //colour value
      if(self->u.value == 0){
        printf("1.0 0.0 0.0\n");
      }else if(self->u.value == 1){
        printf("0.0 1.0 0.0\n");
      }else if(self->u.value == 2){
        printf("0.0 0.0 1.0\n");
      }else if(self->u.value == 3){
        printf("0.0 0.0 0.0\n");
      }else if(self->u.value == 4){
        printf("0.5 0.5 0.5\n");
      }else if(self->u.value == 5){
        printf("0.0 1.0 1.0\n");
      }else if(self->u.value == 6){
        printf("1.0 0.0 1.0\n");
      }else if(self->u.value == 7){
        printf("1.0 1.0 0.0\n");
      }else if(self->u.value == 8){
        printf("1.0 1.0 1.0\n");
      }
    }else{
      printf("Error ?\n");
    }
  }else{
    for (size_t i = 0; i < self->children_count; i++) {
      print_second(self->children[i]);
      int kind = self->kind;
      if(kind == 3){
        if(i != (self->children_count - 1)){
          printf("%c\n", self->u.op);
        }
      }
    }
  }

}


void print_first(const struct ast_node *self){
  int kind = self->kind;
  if(kind == 0){
    int cmd_kind = self->u.cmd;
    if(cmd_kind == 0){
      printf("forward ");
    }else if(cmd_kind == 1){
      printf("left ");
    }else if(cmd_kind == 2){
      printf("right ");
    }else if(cmd_kind == 3){
      printf("up\n");
    }else if(cmd_kind == 4){
      printf("heading");
    }else if(cmd_kind == 5){
      printf("down\n");
    }else if(cmd_kind == 6){
      printf("backward ");
    }else if(cmd_kind == 7){
      printf("colour ");
    }else if(cmd_kind == 8){
      printf("position ");
    }
  }else if(kind == 1){
    printf("FUNC\n");
  }else if(kind == 2){
    printf("VALUE EXPR\n");
  }else if(kind == 3){
    printf("BINOP EXPR\n");
  }

  print_second(self);

  if(self->next){
    print_first(self->next);
  }
}




void ast_print(const struct ast *self) {
  print_first(self->unit);
}
