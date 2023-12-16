#include "render.h"
#include "tree.h"
#include "task.h"

int main() {
    tree::node_t* a = task::generate_tree(50);
    tree::node_t* b = task::generate_tree(50);
//    a = tree::remove(a, 40);
//    bulk_render(new tree::node_t*[]{a}, 1, (char*) "Original");
    bulk_render(new tree::node_t*[]{a, b}, 2, (char*) "Original");

    tree::node_t* result = task::intersect(a, b);
    bulk_render(new tree::node_t*[]{result}, 1, (char*) "Result");

    return 0;
}
