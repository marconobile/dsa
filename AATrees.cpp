#include <iostream>
#include <string>
#include <algorithm> // for std::min
// #include <memory>
// #include <cstddef>
// #include <vector>

// g++ -std=c++17 -o  aat.out AATrees.cpp
// leaks --atExit -- ./avl.out

class Nil;

class AANode {
    public:
        int data;
        int level;
        AANode *right, *left;

        AANode(int value, AANode *right, AANode *left): data(value), level(1), right(right), left(left) {}
        AANode(): data(0), level(0), left(this), right(this) {}
};
AANode nil = AANode();

AANode* skew(AANode* p) {
    if (p == &nil) {
        return p;
    }
    if (p -> left ->level == p -> level) { // if p has a left red node
        // right rotation
        AANode* q = p -> left;
        p -> left = q -> right;
        q -> right = p;
        return q;
    }
    return p;
}

AANode* split(AANode *p) {
    if (p == &nil) {
        return p;
    }

    if (p->right->right->level == p->level) { // check if (p ->level == p->right->level) is useless since if p->right was red, then we need to split iff p->right->right->level is red
        AANode* q = p->right;
        p -> right = q -> left;
        q -> left = p;
        q->level++; // IMPORTANT: promote q to lvl above!
        return q;
    }
    return p;
}

AANode* insert(int value, AANode* p) {
    if (p == &nil) {
        p = new AANode(value, &nil, &nil);
    } else if (value < p -> data) {
        p -> left = insert(value, p -> left);
    } else if (value > p -> data) {
        p -> right = insert(value, p -> right);
    } else {
        throw; // duplicate key found
    }
    return split(skew(p));
}

void updateLevel(AANode* p) {
    int idealLevel = 1 + std::min(p ->left -> level, p ->right -> level);
    if (p ->level > idealLevel) {
        p ->level = idealLevel;
        if (p ->right->level > idealLevel) { // if red node present
            p ->right->level = idealLevel; // bring it down aswell
        }
    }
}

AANode* findInorderSuccessor(AANode* p) {
    AANode *r = p->right;
    while (r != &nil) {
        r = r -> right;
    }
    return r;
}

AANode* findInorderPredecessor(AANode* p) {
    AANode *r = p->left;
    while (r != &nil) {
        r = r -> left;
    }
    return r;
}

AANode* fixAfterDelete(AANode* p) {
    updateLevel(p);
    p = skew(p);
    p ->right = skew(p ->right);
    p ->right->right = skew(p ->right->right);
    p = split(p);
    p ->right = split(p ->right);
    return p;

}

AANode* deleteNode(int value, AANode* p) {
    if (p == &nil) {
        throw; // key not found!
    }

    if (value < p ->data){
        p -> left = deleteNode(value, p ->left);
    } else if (value > p ->data) {
        p -> right = deleteNode(value, p ->right);
    } else { // node found!
        if (p ->left == &nil && p -> right == &nil) {
            return &nil;
        } else if(p ->left == &nil) {
            AANode* r = findInorderSuccessor(p);
            p -> data = r ->data;
            p ->right = deleteNode(r ->data, p ->right);
        } else if(p ->right == &nil) { // avoidable check but clearer
            AANode* r = findInorderPredecessor(p);
            p -> data = r ->data;
            p ->left = deleteNode(r ->data, p ->left);
        }
    }
    return fixAfterDelete(p);
}

// TODO:
// insertion list in main
// why three skews
// comment & debug step by step code
// test case
// delete - free mem func
// print inorder func

int main() {


    AANode* root = new AANode(0, &nil, &nil);

    if (root == &nil) {
        std::cout << "in\n";
    }

    if (root -> right == &nil) {
        std::cout << "right is nil\n";
    }

    if (root -> left == &nil) {
        std::cout << "left is nil\n";
    }

    delete root;

}

