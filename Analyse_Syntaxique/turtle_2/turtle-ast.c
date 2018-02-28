#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_expr_colour(const char* colour_name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = 0;
  return node;
}


struct ast_node *make_cmd(struct ast_node *node_fils, char * name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  if(strcmp("forward", name)){
    node->u.cmd = CMD_FORWARD;
  }else if(strcmp("backward", name)){
    node->u.cmd = CMD_BACKWARD;
  }else if(strcmp("up", name)){
    node->u.cmd = CMD_UP;
  }else if(strcmp("down", name)){
    node->u.cmd = CMD_DOWN;
  }else if(strcmp("heading", name)){
    node->u.cmd = CMD_HEADING;
  }else if(strcmp("left", name)){
    node->u.cmd = CMD_LEFT;
  }else if(strcmp("right", name)){
    node->u.cmd = CMD_RIGHT;
  }else if(strcmp("colour", name)){
    node->u.cmd = CMD_COLOUR;
  }else{
    printf("ERROR\n");
  }

  node->children[node->children_count] = node_fils;
  node->children_count ++;
  return node;
}

struct ast_node *make_pen_cmd(char * name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  if(strcmp("up", name)){
    node->u.cmd = CMD_UP;
  }else if(strcmp("down", name)){
    node->u.cmd = CMD_DOWN;
  }else{
    printf("ERROR\n");
  }
  return node;
}

struct ast_node *make_colour_cmd_one(struct ast_node *node_fils) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOUR;

  node->children[node->children_count] = node_fils;
  node->children_count ++;
  return node;
}

struct ast_node *make_colour_cmd_three(struct ast_node *node_r, struct ast_node *node_g, struct ast_node *node_b) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOUR;

  node->children_count = 3;
  node->children[0] = node_r;
  node->children[1] = node_g;
  node->children[2] = node_b;
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

  node->children[node->children_count] = node_fils1;
  node->children_count ++;
  node->children[node->children_count] = node_fils2;
  node->children_count ++;
  return node;
}


void ast_destroy(struct ast *self) {

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

void ast_print(const struct ast *self) {

}
