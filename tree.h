#ifndef TREE_CPP_TREE_H
#define TREE_CPP_TREE_H

namespace tree {
    struct node_t {
        node_t *left_child;
        node_t *right_sibling;

        int value;
        int size;
        int mark;

        explicit node_t(int v) {
            value = v;
            size = 1;
            mark = 0;

            left_child = nullptr;
            right_sibling = nullptr;
        }
    };

    node_t* insert(node_t *root, int value);
    node_t* remove(node_t* root, int value);
    bool find_symmetric(node_t* tree, int value);
}

#endif
