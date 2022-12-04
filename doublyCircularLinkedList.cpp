#include <iostream>

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int data): data(data), prev(nullptr), next(nullptr) {};
};

struct doublyCLL
{
    Node* head;
    Node* tail;
    doublyCLL(): head(nullptr), tail(nullptr){};
};

void appendNode(doublyCLL &dcll, Node* new_node) {
    if (dcll.head == nullptr) {
        dcll.head = new_node;
        dcll.tail = new_node;
        new_node -> next = new_node;
        new_node -> prev = new_node;
        return;
    }
    dcll.tail -> next = new_node;
    new_node -> prev = dcll.tail;
    new_node -> next = dcll.head;
    dcll.tail = new_node;
    dcll.head -> prev = new_node;
    return;
}



void printDCLL(const doublyCLL &dcll) {
    std::cout << "Idx: -1 el: " << dcll.head-> prev -> data << std::endl;
    Node* tmp = dcll.head;
    int counter = 0;
    while(tmp -> next != dcll.head) {

        std::cout << "Idx: " << counter << " el: " << tmp->data << std::endl;
        counter++;
        tmp = tmp -> next;
    }
    std::cout << "Idx: " << counter << " el: " << tmp->data << std::endl;
    std::cout << "Idx: -1 el: " << dcll.tail-> next -> data << std::endl;
}


void prependNode(doublyCLL &dcll, Node* new_node) {
    if (dcll.head == nullptr){
        appendNode(dcll, new_node);
        return;
    }

    dcll.head -> prev = new_node;
    new_node -> next = dcll.head;
    new_node -> prev = dcll.tail;
    dcll.head = new_node;
    dcll.tail -> next = new_node;
}


int counElsInList(const doublyCLL &dcll) {
    if (dcll.head == nullptr) {
        return 0;
    } else  if (dcll.head == dcll.tail) {
        return 1;
    }

    Node* itr = dcll.head;
    int counter = 0;
    while(itr -> next != dcll.head) {
        counter++;
        itr = itr -> next;
    }
    counter++;
    return counter;

}

void insertAtPos(doublyCLL &dcll, Node* new_node, int pos) {
    if( pos == 0) {
        prependNode(dcll, new_node);
        return;
    } else if (pos == counElsInList(dcll)-1 ){
        appendNode(dcll, new_node);
        return;
    }

    Node* itr = dcll.head;
    int counter = 0;
    while (counter != pos) {
        itr = itr -> next;
        counter ++;
    }

    new_node -> next = itr;
    new_node -> prev = itr -> prev;
    itr -> prev -> next = new_node;
    itr -> prev = new_node;
}


void deleteAtBeginning(doublyCLL &dcll) {
    dcll.head -> next -> prev = dcll.tail;
    dcll.tail -> next = dcll.head -> next;
    dcll.head = dcll.head -> next;
}


void deleteAtEnd(doublyCLL &dcll) {
    dcll.tail -> prev -> next = dcll.head;
    dcll.head -> prev = dcll.tail -> prev;
    dcll.tail = dcll.tail -> prev;
}



void deleteAtPos(doublyCLL &dcll, int pos) {
    if (pos == 0) {
        deleteAtBeginning(dcll);
        return;
    } else if (pos == counElsInList(dcll)-1){
        deleteAtEnd(dcll);
        return;
    }

    Node* tmp = dcll.head;
    int counter = 0;
    while(counter != pos) {
        tmp = tmp -> next;
        counter ++;
    }

    tmp -> prev -> next = tmp -> next;
    tmp -> next -> prev = tmp -> prev;
    return;
}

void reverseDCLL(doublyCLL &dcll) {

    Node* next_node, *prev_node;
    Node* curr_node = dcll.head;

    while(curr_node != dcll.tail) {
        // get ptr
        prev_node = curr_node -> prev;
        next_node = curr_node -> next;
        // swap links
        curr_node -> next = prev_node;
        curr_node -> prev = next_node;
        curr_node = next_node;
    }

    // get ptr
    prev_node = curr_node -> prev;
    next_node = curr_node -> next;
    // swap links
    curr_node -> next = prev_node;
    curr_node -> prev = next_node;
    curr_node = next_node;



    next_node = dcll.head;
    dcll.head = dcll.tail;
    dcll.tail = next_node;




}


int main(){
    doublyCLL dcll = doublyCLL();
    Node n0 = Node(0);
    Node n1 = Node(1);
    Node n2 = Node(2);
    std::cout << "test append\n";
    appendNode(dcll, &n0);
    appendNode(dcll, &n1);
    appendNode(dcll, &n2);
    // std::cout << "head "<< dcll.head -> data  << " tail " << dcll.tail -> data << std::endl;
    printDCLL(dcll);

    std::cout << "test prepend\n";
    Node n_1 = Node(-1);
    Node n_2 = Node(-2);
    Node n_3 = Node(-3);
    prependNode(dcll, &n_1);
    prependNode(dcll, &n_2);
    prependNode(dcll, &n_3);
    printDCLL(dcll);

    std::cout << "test insert at pos\n";
    Node n99 = Node(99);
    Node n98 = Node(98);
    Node n97 = Node(97);
    insertAtPos(dcll, &n99, 1);
    insertAtPos(dcll, &n98, 3);
    insertAtPos(dcll, &n97, 4);
    printDCLL(dcll);


    std::cout << "test insert at pos end-beginning\n";
    Node n100 = Node(100);
    Node n101 = Node(101);
    insertAtPos(dcll, &n100, 0);
    insertAtPos(dcll, &n101, counElsInList(dcll)-1 );
    printDCLL(dcll);

    std::cout << "delete at beginning\n";
    deleteAtBeginning(dcll);
    deleteAtBeginning(dcll);
    printDCLL(dcll);

    std::cout << "delete at beginning\n";
    deleteAtEnd(dcll);
    // deleteAtEnd(dcll);
    printDCLL(dcll);

    std::cout << "delete at pos 1\n";
    deleteAtPos(dcll, 1);
    printDCLL(dcll);
    std::cout << "delete at pos 4\n";
    deleteAtPos(dcll, 4);
    printDCLL(dcll);

    std::cout << "delete at pos\n";
    deleteAtPos(dcll, 0);
    deleteAtPos(dcll, counElsInList(dcll)-1);
    printDCLL(dcll);

    Node n1000 = Node(1000);
    Node n1010 = Node(1001);
    prependNode(dcll, &n1000);
    prependNode(dcll, &n1010);

    std::cout << "Pre reverse\n";
    printDCLL(dcll);
    reverseDCLL(dcll);
    std::cout << "post reverse\n";
    printDCLL(dcll);




}