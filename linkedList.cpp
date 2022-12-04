/*
LL better for large ammount of data
FLL, DLL, CLL, DCLL
LL vs arrays:                           array   |   LL
    insertion/deletion at beginning     O(n)        O(1)
    insertion/deletion at middle        O(n)        O(n)
    insertion/deletion at end           O(1)        O(n)

    search methods                      linear, binary | linear

    
    Linear ds, non-contiguous in memory
    Advantages:
        - LL are dynamic in size
        - ease of insertion/deletion
    Disadvantages:
        - Don't have random access (indexing)
        - extra memory due to ptrs
        - not cache friendly

    Traversing is faster in contiguous ds


 * /
*/

#include <iostream>

struct Node{
    int data;
    Node* pnext = nullptr;
    Node(int d): data(d) {};
};

struct LinkedList{
    Node* phead = nullptr;
};

void printLL(LinkedList ll){
    Node* pitr = ll.phead;
    std::cout << "Printing list: \n";
    int counter=0;
    while (pitr != nullptr){
        std::cout << "idx: "<< counter << " value: " << pitr->data << std::endl;
        pitr = pitr -> pnext;
        counter++;
    }
}

void prependNode(LinkedList& ll, Node* pn) {
    if (ll.phead == nullptr){
        ll.phead = pn;
        return;
    }
    // go take current head and store it in a temp ptr
    Node* ptmp = ll.phead;
    // update head
    ll.phead = pn;
    // link new head node to old head saved in temp
    ll.phead -> pnext = ptmp;
    return;
}

void appendNode(LinkedList& ll, Node* pn) {
    // find node with nullptr as next
    Node* pitr = ll.phead;
    while(pitr->pnext != nullptr) { //!
        pitr = pitr->pnext;
    }
    pitr->pnext = pn;
    pn ->pnext = nullptr;
}

int coutElsInLL(LinkedList &ll) {
    Node* pitr = ll.phead;
    int count = 1;
    while(pitr->pnext != nullptr) { //!
        pitr = pitr->pnext;
        count++;
    }
    return count;
}

Node* getPtrAtPos(const LinkedList &ll, int pos) {
    // TODO check validity of pos
    if (pos == 0) {
        return ll.phead;
    }

    Node* pitr = ll.phead;
    int count = 0;
    while(count != pos) {
        pitr = pitr->pnext;
        count++;
    }
    return pitr;
}

void insertAtPos(LinkedList &ll, Node* pn, int pos) {
    // always update first the inserted node
    if (pos == 0) {
        prependNode(ll, pn);
        return;
    } else if (pos == coutElsInLL(ll)) {
        appendNode(ll, pn);
        return;
    }

    Node* tmp = getPtrAtPos(ll, pos);
    pn->pnext = tmp;
    Node* prev_n = getPtrAtPos(ll, pos-1);
    prev_n ->pnext = pn;
}

void deleteFromBeginning(LinkedList &ll) {
    Node* tmp = ll.phead;
    ll.phead = tmp->pnext;
}

void deleteFromEnd(LinkedList &ll) {
    Node* tmp;
    Node* prev_tmp;
    tmp = ll.phead;

    while(tmp->pnext != nullptr) {
        prev_tmp = tmp;
        tmp = tmp->pnext;
    }
    prev_tmp->pnext = nullptr;
}

void deleteFromPos(LinkedList &ll, int pos) {
    if (pos==0) {
        deleteFromBeginning(ll);
        return;
    } else if (pos == coutElsInLL(ll)-1) {
        deleteFromEnd(ll);
        return;
    }

    Node* tmp;
    Node* prev_tmp;
    tmp = ll.phead;
    int counter = 0;
    while(counter != pos) {
        counter++;
        prev_tmp = tmp;
        tmp = tmp ->pnext;
    }
    prev_tmp->pnext = tmp->pnext;
}

// reversing a linked list - iterative approach that reverses the links direction
void reverse(LinkedList &ll) {
    Node *prev_node, *curr_node, *next_node;
    prev_node = nullptr;
    curr_node = ll.phead;
    next_node = ll.phead;

    // keep going untill next node does not exists
    while(next_node != nullptr) {
        // move next
        next_node = next_node->pnext;
        // update current
        curr_node->pnext = prev_node;
        // move prev, move currN
        prev_node = curr_node;
        curr_node = next_node;
    }
    ll.phead = prev_node;
}



// now comprehend, refactor and switch/tests/prints


int main(){
    LinkedList ll = LinkedList();
    Node n1 = Node(1);
    prependNode(ll, &n1);
    Node n2 = Node(2);
    prependNode(ll, &n2);
    Node n3 = Node(3);
    prependNode(ll, &n3);

    Node n4 = Node(4);
    appendNode(ll, &n4);
    Node n5 = Node(5);
    appendNode(ll, &n5);
    Node n6 = Node(6);
    appendNode(ll, &n6);

    Node n0 = Node(0);
    insertAtPos(ll, &n0,  2);
    std::cout << "N of els: " << coutElsInLL(ll);

    Node n_0 = n0;
    Node n_1 = n1;
    Node n_2 = n2;
    Node n_3 = n3;
    Node n_4 = n4;
    Node n_5 = n5;
    Node n_6 = n6;

    insertAtPos(ll, &n_0,  0);
    insertAtPos(ll, &n_1,  1);
    insertAtPos(ll, &n_2,  2);
    insertAtPos(ll, &n_3,  3);
    insertAtPos(ll, &n_4,  4);
    insertAtPos(ll, &n_5,  5);
    insertAtPos(ll, &n_6,  6);

    printLL(ll);
    std::cout << "N of els: " << coutElsInLL(ll) << std::endl;
    deleteFromBeginning(ll);
    deleteFromBeginning(ll);
    deleteFromBeginning(ll);
    std::cout << "N of els: " << coutElsInLL(ll) << std::endl;
    printLL(ll);
    deleteFromEnd(ll);
    deleteFromEnd(ll);
    deleteFromEnd(ll);
    printLL(ll);

    deleteFromPos(ll, 4);
    deleteFromPos(ll, 0);
    printLL(ll);

    reverse(ll);
    std::cout << "Reversed: \n";
    printLL(ll);




}


/*
        if (next_node -> pnext == nullptr) {
            end = true;
        }

        if (prev_node == ll.phead) {
            prev_node = tmp;
            tmp = tmp -> pnext;
            prev_node -> pnext = nullptr;
        } else if (end) {
            ll.phead = tmp;
        }


        tmp_copy = tmp;
        tmp = tmp -> pnext;
        tmp_copy -> pnext = prev_node;
        prev_node = tmp_copy;

    }*/