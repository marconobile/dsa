#include <iostream>
#include <string>
#include <memory>
#include <cstddef>
#include <vector>
#include <algorithm>

// g++ -std=c++17 -o  avl.out avlTree.cpp
// leaks --atExit -- ./avl.out

class avlNode {
    public:
        int data;
        int height;
        // int depth;
        avlNode *right, *left;

    avlNode(int value): data(value), height(0), right(nullptr), left(nullptr) {}
};

void printInorder(avlNode *node);
void printInorderWithHeights(avlNode *node);
avlNode* rebalance(avlNode* node);
void printInorderWithBF(avlNode *node);


// THIS INSERTION SETS DEPTH VALUE
// avlNode* insert(int value, avlNode* node, int depth = 0) {
//     if (node == nullptr) {
//         node = new avlNode(value, depth);
//     } else if (value < node->data) {
//         node -> left = insert(value, node -> left, ++depth);
//     } else if (value > node->data) {
//         node -> right = insert(value, node -> right, ++depth);
//     }
//     return node;
// }

int getHeight(avlNode* node) {
    return node == nullptr ? -1 : node -> height;
}

int updateHeight(avlNode* node) {
    return std::max(getHeight(node -> left), getHeight(node -> right)) + 1;
}

int getBalanceFactor(avlNode* node){
    return  getHeight(node->left) - getHeight(node->right); // TBU why getHeight may return -1 if no L/R child?
}

avlNode* insert(int value, avlNode* node) {
    if (node == nullptr) {
        node = new avlNode(value);
    } else if (value < node->data) {
        node -> left = insert(value, node -> left);
        node -> height = updateHeight(node);
    } else if (value > node->data) {
        node -> right = insert(value, node -> right);
        node -> height = updateHeight(node);
    } else {
        throw; // key already present
    }
    return rebalance(node);
}

avlNode* rotateLeft(avlNode* p) {
    avlNode* q = p->right;
    p->right = q->left;
    q->left = p;
    p->height = updateHeight(p);
    q->height = updateHeight(q);
    return q;
}

// need to rotate right when the tree is left heavy (BF < -1)
avlNode* rotateRight(avlNode* p) {
    avlNode* q = p->left; // get the root of the left subtree
    p->left = q -> right; // move the right subtree of q to the left side of p
    q->right = p; // move p
    // : lifting q by moving its right subtree to the left side of p
    p->height = updateHeight(p);
    q->height = updateHeight(q);
    return q;
}

avlNode* rotateRightLeft(avlNode* p) {
    p -> right = rotateRight(p->right);
    return rotateLeft(p);
}

avlNode* rotateLeftRight(avlNode* p) {
    p -> left = rotateLeft(p->left);
    return rotateRight(p);
}

avlNode* rebalance(avlNode* p) {
    if (p == nullptr) {
        return p;
    }
    if (getBalanceFactor(p) < -1){ // right heavy
        if (getHeight(p->right->right) >=  getHeight(p->right->left)) { // right-right (or simply right) heavy
            p = rotateLeft(p);
        } else { // if right - left heavy
            p = rotateRightLeft(p);
        }
    } else if (getBalanceFactor(p) > 1) { // left heavy
        if (getHeight(p->left->left) >= getHeight(p->left->right)) { // left left heavy
            p = rotateRight(p);
        } else { // left right heavy
            p = rotateLeftRight(p);
        }
    }
    p -> height = updateHeight(p);
    return p;
}

// let's use the largest node in the left subtre (i.e. the rightmost node)
avlNode* findReplacement(avlNode* node) {
    avlNode* r = node -> left;
    while (r -> right != nullptr) {
        r = r->right;
    }
    return r;
}

avlNode* deleteNode(int value, avlNode* node) {
    if (node == nullptr) {
        throw; // fell off the tree = key not found!
    }
    if (value < node -> data) {
        node -> left = deleteNode(value, node -> left);
    } else if (value > node -> data) {
        node -> right = deleteNode(value, node -> right);
    } else if (node -> right == nullptr || node -> left == nullptr) {
        if (node ->right != nullptr) {
            return rebalance(node ->right);
        } else {
            return rebalance(node -> left);
        }
    } else {
        avlNode* r = findReplacement(node);
        node -> data = r ->data;
        node -> left = deleteNode(r -> data, node -> left); // once replaced we call delete in that subtree
    }
    return rebalance(node);
}

void deleteTree(avlNode *node) {
    // follow post-order traversal criteria L-Ri-Ro to delete
    if (node -> left == nullptr && node -> right == nullptr) {
        delete node;
        return;
    }

    if (node -> left != nullptr) {
        deleteTree(node ->left);
    }

    if (node -> right != nullptr) {
        deleteTree(node ->right);
    }

    delete node;
    return;
}

int main() {

    std::vector<int> values_to_insert = {11, 6, 8, 19, 4, 10, 5, 17, 43, 49, 31};
    avlNode* root = nullptr;

    for (int i = 0; i <= values_to_insert.size()-1; i++)
        root = insert(values_to_insert[i], root);

    // printInorderWithHeights(root);
    printInorderWithBF(root);
    std::cout << std::endl;

    root = deleteNode(5, root);
    printInorderWithBF(root);
    std::cout << std::endl;

    root = deleteNode(8, root);
    printInorderWithBF(root);
    std::cout << std::endl;

    deleteTree(root);
}

// inorder: left root right
void printInorder(avlNode *node)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << " " << node->data << " ";
        return;
    }

    if (node->left) {
        printInorder((node->left));
    }

    std::cout << " " << node->data << " ";

    if (node->right) {
        printInorder((node->right));
    }
}

// inorder: left root right
void printInorderWithHeights(avlNode *node)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << " " << node->data << " ";
        std::cout << "(height: " << node->height << ") ";
        return;
    }

    if (node->left) {
        printInorderWithHeights((node->left));
    }

    std::cout << " " << node->data << " ";
    std::cout << "(height: " << node->height << ") ";

    if (node->right) {
        printInorderWithHeights((node->right));
    }
}

void printInorderWithBF(avlNode *node)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << " " << node->data << " ";
        std::cout << "(bf: " << getBalanceFactor(node) << ") ";
        return;
    }

    if (node->left) {
        printInorderWithBF((node->left));
    }

    std::cout << " " << node->data << " ";
    std::cout << "(bf: " << getBalanceFactor(node) << ") ";

    if (node->right) {
        printInorderWithBF((node->right));
    }
}