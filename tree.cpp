#include "random"
#include "tree.h"

namespace tree {
    void update_size(node_t *node) {
        node->size = node->mark == 0 ? 1 : 0;

        node->size += node->left_child->size;
        node_t *right_son = node->left_child->right_sibling;
        if (right_son) node->size += right_son->size;
    }

    node_t *actual_left(node_t *root) {
        if (!root) return nullptr;
        if (root->left_child->mark != 0) return nullptr;
        return root->left_child;
    }

    node_t *make_virtual_node() {
        auto left_child = new node_t(0);
        left_child->mark = 2;
        left_child->size = 0;
        return left_child;
    }

    node_t *make_node(int root_value) {
        auto node = new node_t(root_value);
        node->left_child = make_virtual_node();
        return node;
    }

    void reuse_virtual_child(node_t *node, int value) {
        node->value = value;
        node->mark = 0;
        node->left_child = make_virtual_node();
    }

    node_t *rotate_left(node_t *q) {
        node_t *p = q->left_child->right_sibling;

        // Если правого поддерева нет, то ничего не делаем и возвращаем корень поддерева.
        if (!p) return q;

        p->right_sibling = q->right_sibling;
        q->right_sibling = p->left_child->right_sibling;

        q->left_child->right_sibling = actual_left(p);
        p->left_child = q;

        p->size = q->size;

        // Пересчитываем размер поддерева с новым корнем и возвращаем его.
        update_size(p);
        return p;
    }

    node_t *rotate_right(node_t *p) {
        node_t *q = p->left_child;

        // Если левого поддерева нет, то ничего не делаем и возвращаем корень поддерева.
        if (!q) return p;

        p->left_child = q->left_child->right_sibling;

        if (!p->left_child) p->left_child = make_virtual_node();
        p->left_child->right_sibling = q->right_sibling;

        if (q->left_child->right_sibling) {
            p->left_child->right_sibling = q->right_sibling;
        }

        q->right_sibling = p->right_sibling;
        p->right_sibling = nullptr;

        q->left_child->right_sibling = p;
        q->size = p->size;

        if (!p->left_child) p->left_child = make_virtual_node();

        // Пересчитываем размер поддерева с новым корнем и возвращаем его.
        update_size(q);
        return q;
    }

    node_t *insert_root(node_t *root, int value) {
        if (!root) return make_node(value);

        if (root->mark != 0) {
            reuse_virtual_child(root, value);
            update_size(root);
            return root;
        }

        if (value < root->value) {
            root->left_child = insert_root(root->left_child, value);
            return rotate_right(root);
        }

        if (value > root->value) {
            root->left_child->right_sibling = insert_root(root->left_child->right_sibling, value);
            return rotate_left(root);
        }

        return root;
    }

    node_t *insert(node_t *root, int value) {
        // Если в качестве родителя передан null, то считаем, что мы дошли до "конца" дерева,
        // нужно создать новый узел (поддерево).
        if (!root) return make_node(value);

        if (root->mark != 0) {
            reuse_virtual_child(root, value);
            update_size(root);
            return root;
        }

        // Не добавляем повторяющиеся значения
        if (root->value == value) return root;

        // С вероятностью 1 / (n + 1) вставляем новый элемент в корень.
        if (rand() % (root->size + 1) == 0) return insert_root(root, value);

        // В зависимости от того, больше или меньше полученное значение, чем родитель,
        // добавляем его либо в левое, либо в правое поддерево.
        // Если поддерево отсутствует, то insert создаст новое.
        if (value < root->value) {
            root->left_child = insert(root->left_child, value);
        }

        if (value > root->value) {
            root->left_child->right_sibling = insert(root->left_child->right_sibling, value);
        }

        // Пересчитываем размер поддерева и возвращаем его.
        update_size(root);
        return root;
    }

    node_t *merge(node_t *left, node_t *right) {
        if (!left || left->mark != 0) return right;
        if (!right || right->mark != 0) return left;

        left->left_child->right_sibling = merge(left->left_child->right_sibling, right);
        update_size(left);
        return left;
    }

    node_t *remove(node_t *root, int value) {
        if (!root || root->mark != 0) return nullptr;

        if (value < root->value) {
            root->left_child = remove(root->left_child, value);
            if (!root->left_child) root->left_child = make_virtual_node();
            return root;
        }

        if (root->value == value) {
            node_t *merged_root = merge(root->left_child, root->left_child->right_sibling);

            if (root->right_sibling) {
                if (!merged_root) merged_root = make_virtual_node();
                merged_root->right_sibling = root->right_sibling;
            } else if (merged_root) {
                merged_root->right_sibling = nullptr;
            }

            root->mark = 1;
            return merged_root;
        }

        if (value > root->value) {
            root->left_child->right_sibling = remove(root->left_child->right_sibling, value);
            return root;
        }

        // unreachable
        return root;
    }

    bool find_symmetric(node_t *tree, int value) {
        if (!tree || tree->mark != 0) return false;

        if (value < tree->value) return find_symmetric(tree->left_child, value);
        if (value == tree->value) return true;

        if (value > tree->value) {
            if (!tree->left_child) return false;
            return find_symmetric(tree->left_child->right_sibling, value);
        }

        // unreachable
        return false;
    }
}
