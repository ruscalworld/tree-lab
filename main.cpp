#include <iostream>

#include "render.h"
#include "tree.h"
#include "task.h"

int main() {
    tree::node_t* a = task::generate_tree(50);
    print_tree_pre(a);
    std::cout << std::endl;

    tree::node_t* b = task::generate_tree(50);
    print_tree_sym(b);
    std::cout << std::endl;

    bulk_render(new tree::node_t*[]{a, b}, 2, (char*) "Original");

    tree::node_t* result = task::intersect(a, b);
    bulk_render(new tree::node_t*[]{result}, 1, (char*) "Result");

    return 0;
}
