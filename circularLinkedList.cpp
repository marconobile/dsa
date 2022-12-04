#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int data): data(data), next(nullptr) {};
};

struct circularLL
{
    Node* tail;
    circularLL(): tail(nullptr){};
};

void appendNode(circularLL &cll, Node* new_node) {

    if (cll.tail == nullptr) {
        cll.tail = new_node;
        cll.tail -> next = new_node;
    } else {
        // last node .next field always contains ptr to first element of list
        new_node -> next = cll.tail -> next;
        cll.tail -> next = new_node;
        cll.tail = new_node;
    }
}

void prependNode(circularLL &cll, Node* new_node) {
    if (cll.tail == nullptr) {
        appendNode(cll, new_node);
        return;
    }
    new_node ->next = cll.tail -> next;
    cll.tail -> next = new_node;
}



void printCLL(const circularLL &cll) {
    std::cout << "Printing list: \n";
    Node* itr = cll.tail ->next;
    int counter = 0;
    do {

        std::cout << "Idx: " << counter  << " el: " << itr -> data << std::endl;
        counter++;
        itr = itr->next;

    } while(itr != cll.tail ->next );
}

int countElsInList(const circularLL &cll) {
    int counter = 0;
    if (cll.tail == nullptr){
        return 0;
    }

    Node* itr = cll.tail -> next;
    do{
        counter++;
        itr = itr -> next;
    } while(itr != cll.tail -> next);
    return counter;
}

void insertAtPos(circularLL &cll, Node* new_node, int pos) {
    // first element in the list has index = 0
    if (pos == 0) {
        prependNode(cll, new_node);
        return;
    } else if (pos == countElsInList(cll) -1 ){
        appendNode(cll, new_node);
        return;
    }
    Node* itr = cll.tail -> next;
    int counter = 0;
    Node* prev_node;
    while(counter != pos) {
        prev_node = itr;
        itr = itr -> next;
        counter++;
    }
    prev_node -> next = new_node;
    new_node -> next = itr;
}

void deleteFromBeginning(circularLL &cll) {
    if (cll.tail == nullptr) {
        return;
    } else if(cll.tail -> next == cll.tail) {
        cll.tail = nullptr;
        return;
    }
    cll.tail ->next = cll.tail ->next -> next;
}

void deleteFromEnd(circularLL &cll) {
    if (cll.tail == nullptr) {
        return;
    } else if(cll.tail -> next == cll.tail) {
        cll.tail = nullptr;
        return;
    }
    Node* itr = cll.tail ->next;
    while(itr -> next != cll.tail) {
        itr = itr -> next;
    }
    itr -> next = cll.tail ->next;
    cll.tail = itr;
}

void deleteFromPos(circularLL &cll, int pos) {
    if (pos == 0) {
        deleteFromBeginning(cll);
        return;
    } else if (pos == countElsInList(cll) -1 ){
        deleteFromEnd(cll);
        return;
    }
    Node* itr = cll.tail -> next;
    int counter = 0;
    Node* prev_node;
    while(counter != pos) {
        prev_node = itr;
        itr = itr -> next;
        counter++;
    }
    prev_node -> next = itr -> next;
}

void revertList(circularLL &cll) {
    Node* prev_node = cll.tail -> next;
    Node* curr_node = prev_node -> next;
    Node* next_node = nullptr;
    while(curr_node != cll.tail) {
        next_node = curr_node -> next;
        curr_node -> next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }
    // fix tail
    next_node = cll.tail -> next; // new head
    cll.tail -> next -> next = cll.tail;
    cll.tail -> next = prev_node;
    cll.tail = next_node;

}


int main(){
    circularLL cll = circularLL();
    Node n0 = Node(0);
    Node n1 = Node(1);

    appendNode(cll, &n0);
    appendNode(cll, &n1);
    std::cout << "Last element: " << cll.tail ->next -> data << std::endl;
    printCLL(cll);

    Node n2 = Node(2);
    Node n3 = Node(3);
    Node n4 = Node(4);
    prependNode(cll, &n2);
    prependNode(cll, &n3);
    prependNode(cll, &n4);
    printCLL(cll);

    std::cout << "N of els in list: " << countElsInList(cll) << std::endl;

    Node n99 = Node(99);
    Node n98 = Node(98);
    Node n97 = Node(97);
    insertAtPos(cll, &n97, 4);
    insertAtPos(cll, &n99, 1);
    insertAtPos(cll, &n98, 3);
    printCLL(cll);

    Node n101 = Node(101);
    insertAtPos(cll, &n101, 0);
    printCLL(cll);

    std::cout << "Reverting list\n";
    revertList(cll);
    printCLL(cll);

    std::cout << "Deleting from beginning\n";
    deleteFromBeginning(cll);
    deleteFromBeginning(cll);
    printCLL(cll);

    // deleteFromEnd(cll);
    // deleteFromEnd(cll);
    std::cout << "Deleting end\n";
    deleteFromEnd(cll);
    printCLL(cll);

    deleteFromPos(cll, 1);
    deleteFromPos(cll, 3);
    printCLL(cll);

    deleteFromPos(cll, 0);
    deleteFromPos(cll, countElsInList(cll) -1);
    printCLL(cll);



}