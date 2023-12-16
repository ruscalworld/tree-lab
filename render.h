#ifndef TREE_CPP_RENDER_H
#define TREE_CPP_RENDER_H

#include <iostream>
#include <gvc.h>

#include "tree.h"
#include "string"
#include "map"

void bulk_render(tree::node_t** forest, int size, char* name);
void print_tree_pre(tree::node_t *tree);
void print_tree_sym(tree::node_t *tree);

#endif
