#include <iostream>


struct Node {
    int data;
    Node* prev_node;
    Node* next_node;

    Node(int data): data(data), prev_node(nullptr), next_node(nullptr){}
};


struct DoubleLL {
    Node* head;
    Node* tail;
    DoubleLL(): head(nullptr), tail(nullptr) {}

};


void prependNode(DoubleLL &dll, Node* n) {
    if (!dll.tail && !dll.head ) {
        dll.head = n;
        dll.tail = n;
    } else {
        Node* tmp;
        tmp = dll.head;
        dll.head = n;
        dll.head ->next_node = tmp;
        tmp->prev_node = dll.head;
    }
}

void printDLL(const DoubleLL dll) {
    Node* tmp;
    tmp = dll.head;
    int counter = 0;
    while(tmp != nullptr) {
        std::cout << "idx: " << counter << ", el: " << tmp -> data << std::endl;
        tmp = tmp->next_node;
        counter++;
    }
}

void appendNode(DoubleLL &dll, Node* n) {
    Node* tmp;
    tmp = dll.tail;
    dll.tail = n;
    dll.tail -> prev_node = tmp;
    tmp ->next_node = dll.tail;
}

int countElsInDLL(const DoubleLL &dll) {
    Node* tmp = dll.head;
    int counter = 0;
    while(tmp) {
        tmp = tmp ->next_node;
        counter++;
    }
    return counter;
}

void insertAtPos(DoubleLL &dll, Node* n, int pos) {
    // assuming pos in correct range and not last el
    if (countElsInDLL(dll) == pos) {
        appendNode(dll, n);
        return;
    } else if (pos == 0) {
        prependNode(dll, n);
        return;
    }

    Node *tmp;
    tmp = dll.head;
    int counter = 0;
    while(counter != pos) {
        tmp = tmp ->next_node;
        counter++;
    }

    tmp ->prev_node -> next_node = n;
    n -> prev_node = tmp ->prev_node;
    tmp ->prev_node = n;
    n ->next_node = tmp;
}

void deleteFromBeginning(DoubleLL &dll) {
    dll.head->next_node ->prev_node = nullptr;
    dll.head = dll.head->next_node;
}

void deleteFromEnd(DoubleLL &dll) {
    dll.tail ->prev_node ->next_node = nullptr;
    dll.tail = dll.tail ->prev_node;
}

void deleteFromPos(DoubleLL &dll, int pos) {
    Node* tmp;
    tmp = dll.head;

    int counter= 0;
    while(counter!= pos){
        tmp= tmp->next_node;
        counter++;
    }
    tmp->prev_node ->next_node = tmp->next_node;
    tmp->next_node->prev_node = tmp->prev_node;
}


void reverseDLL(DoubleLL &dll){
    Node* itr = dll.head;
    Node* tmp;
    while(itr != nullptr) {
        tmp = itr -> next_node;
        itr -> next_node = itr -> prev_node;
        itr -> prev_node = tmp;
        itr = itr -> prev_node;
    }
    tmp = dll.head;
    dll.head = dll.tail;
    dll.tail = tmp;
}




int main() {
    DoubleLL dll;
    Node n0 = Node(0);
    prependNode(dll,&n0);
    Node n1 = Node(1);
    prependNode(dll,&n1);
    Node n2 = Node(2);
    prependNode(dll,&n2);
    printDLL(dll);

    std::cout << "test appendings" << std::endl;
    Node n_1 = Node(-1);
    appendNode(dll, &n_1);
    Node n_2 = Node(-2);
    appendNode(dll, &n_2);
    Node n_3 = Node(-3);
    appendNode(dll, &n_3);
    printDLL(dll);

    std::cout << "test insertion at pos" << std::endl;
    Node n_99 = Node(-99);
    insertAtPos(dll, &n_99, 1);
    Node n_98 = Node(-98);
    insertAtPos(dll, &n_98, 2);
    Node n_97 = Node(-97);
    insertAtPos(dll, &n_97, 3);
    printDLL(dll);

    std::cout << "test deletion at beginning" << std::endl;
    deleteFromBeginning(dll);
    deleteFromBeginning(dll);
    deleteFromBeginning(dll);
    printDLL(dll);

    std::cout << "test deletion from end" << std::endl;
    deleteFromEnd(dll);
    deleteFromEnd(dll);
    deleteFromEnd(dll);
    printDLL(dll);

    std::cout << "test deletion from pos" << std::endl;
    Node a = Node(-99);
    Node b = Node(-98);
    Node c = Node(-10);
    Node c1 = Node(-101);
    Node c2 = Node(-102);
    Node c3 = Node(-103);

    prependNode(dll, &c1);
    prependNode(dll, &c2);
    prependNode(dll, &c3);
    appendNode(dll, &a);
    appendNode(dll, &b);
    appendNode(dll, &c);
    deleteFromPos(dll, 1);
    deleteFromPos(dll, 3);
    printDLL(dll);

    std::cout << "test reverse" << std::endl;
    reverseDLL(dll);
    printDLL(dll);


}