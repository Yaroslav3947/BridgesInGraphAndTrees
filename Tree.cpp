#include <vector>
#include <iostream>
#include <unordered_map>

struct Tree {
    int value;
    Tree* left;
    Tree* right;
    Tree(int val) : value(val), left(nullptr), right(nullptr) {}
};

void printTreeInReverseTraversal(Tree *node) {
    if (node != nullptr) {
        printTreeInReverseTraversal(node->left);
        printTreeInReverseTraversal(node->right);
        std::cout << node->value << " ";
    }
}

Tree *buildTree(std::vector<std::pair<int, int>> &edges) {
    std::unordered_map<int, Tree*> nodes;
    Tree *root = nullptr;
    for (auto &edge : edges) {
        int parentValue = edge.first;
        int childValue = edge.second;
        Tree *parent = nodes[parentValue];
        if (parent == nullptr) { // create root
            parent = new Tree(parentValue);
            nodes[parentValue] = parent;
            if (root == nullptr) {
                root = parent;
            }
        }
        Tree *child = nodes[childValue];
        if (child == nullptr) {
            child = new Tree(childValue);
            nodes[childValue] = child;
        }
        if (parent->left == nullptr) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
    return root;
}

int main() {

    std::vector<std::pair<int, int>> edges =   {{1, 2}, 
                                                {1, 3}, 
                                                {2, 4}, 
                                                {2, 5}, 
                                                {3, 6}, 
                                                {3, 8},
                                                {5, 7}};


    Tree *tree = buildTree(edges);

    printTreeInReverseTraversal(tree);

    return 0;
}
