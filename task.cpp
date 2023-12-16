#include "task.h"

namespace task {
    tree::node_t* intersect(tree::node_t* a, tree::node_t* b) {
        if (!a || a->mark == 1) return a;

        if (a->mark == 0 && !tree::find_symmetric(b, a->value)) {
            a = tree::remove(a, a->value);
            return intersect(a, b);
        }

        a->left_child = intersect(a->left_child, b);
        if (a->right_sibling) a->right_sibling = intersect(a->right_sibling, b);

        return a;
    }

    tree::node_t* generate_tree(int size) {
        tree::node_t* tree = nullptr;

        for (int i = 0; i < size; i++) {
            int value = (int) random() % (size * 2);
            tree = tree::insert(tree, value);
        }

        return tree;
    }
}
