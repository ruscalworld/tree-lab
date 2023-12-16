#ifndef TREE_CPP_TASK_H
#define TREE_CPP_TASK_H

#include "tree.h"
#include "random"

namespace task {
    tree::node_t* intersect(tree::node_t *a, tree::node_t *b);
    tree::node_t* generate_tree(int size);
}

#endif
