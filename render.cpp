#include "render.h"

std::string label(tree::node_t* node) {
    if (!node || node->value == 0) return "0";
    std::string label = std::to_string(node->value);
    return label;
}

void draw_tree(tree::node_t* parent, node_t* gv_parent, graph_t* gv_graph) {
    if (!gv_parent) gv_parent = agnode(gv_graph, (char*) label(parent).c_str(), true);

    auto gv_left_child = agnode(gv_graph, (char*) std::to_string(random()).c_str(), true);
    auto gv_left_edge = agedge(gv_graph, gv_parent, gv_left_child, nullptr, true);

    if (parent->left_child && parent->left_child->mark == 0) {
        draw_tree(parent->left_child, gv_left_child, gv_graph);
        agsafeset(gv_left_child, (char*) "label", (char*) label(parent->left_child).c_str(), (char*) "");
    } else {
        agsafeset(gv_left_child, (char*) "label", (char*) "0", (char*) "");
        agsafeset(gv_left_child, (char*) "color", (char*) "gray", (char*) "black");
        agsafeset(gv_left_edge, (char*) "color", (char*) "gray", (char*) "black");
    }

    auto gv_right_child = agnode(gv_graph, (char*) std::to_string(random()).c_str(), true);
    auto gv_right_edge = agedge(gv_graph, gv_parent, gv_right_child, nullptr, true);

    if (parent->left_child && parent->left_child->right_sibling && parent->left_child->right_sibling->mark == 0) {
        draw_tree(parent->left_child->right_sibling, gv_right_child, gv_graph);
        agsafeset(gv_right_child, (char*) "label", (char*) label(parent->left_child->right_sibling).c_str(), (char*) "");
    } else {
        agsafeset(gv_right_child, (char*) "label", (char*) " ", (char*) "");
        agsafeset(gv_right_child, (char*) "color", (char*) "white", (char*) "black");
        agsafeset(gv_right_edge, (char*) "color", (char*) "white", (char*) "black");
    }
}

void bulk_render(tree::node_t** forest, int size, char* name) {
    graph_t* gv_graph = agopen(name, Agdirected, nullptr);

    for (int i = 0; i < size; i++) {
        graph_t* gv_subgraph = agsubg(gv_graph, (char*) std::to_string(i).c_str(), true);
        draw_tree(forest[i], nullptr, gv_subgraph);
    }

    agwrite(gv_graph, stdout);
    agclose(gv_graph);
}
