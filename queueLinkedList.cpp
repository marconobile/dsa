#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

struct Node {
    int data;
    Node* next;
    Node(int data): data(data), next(nullptr) {};
};

struct LinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;
    int n_of_elements = 0;
};

class Queue {

    public:
        int size;
        LinkedList ll;
        LinkedList* getLL() { return &ll; }
        std::vector<std::shared_ptr<Node>> nodePtrsStorage;

        bool isFull() const {
            return ll.n_of_elements == size ? true : false;
        }

        bool isEmpty() const {
            return ll.n_of_elements == 0 ? true : false;
        }

        Queue(int size): size(size) {}
        void enqueue(int data) {
            if (isFull()) {
                throw std::overflow_error("Queue overflow!");
            }
            // add check for overflow condition in the queue has a max-size
            nodePtrsStorage.push_back(std::make_shared<Node>(data));
            Node* new_node = nodePtrsStorage.back().get();
            if (!ll.head) {
                ll.head = new_node;
                ll.tail = ll.head;
                ll.n_of_elements++;
                return;
            }
            ll.tail -> next = new_node;
            ll.tail = new_node;
            ll.n_of_elements++;
            return;
        }

        void displayQueue() const {
            if (isEmpty()) {
                std::cout << "can't display empty list\n";
                return;
            }
            Node* tmp = ll.head;
            while(tmp != nullptr) {
                std::cout << tmp -> data << std::endl;
                tmp = tmp->next;
            }
        }

        int dequeue() {
            if (isEmpty()) {
                throw std::underflow_error("Queue underflow!");
            }
            int res = ll.head ->data;
            ll.head = ll.head -> next;
            nodePtrsStorage.erase(nodePtrsStorage.begin());
            ll.n_of_elements--;
            return res;
        }

        void peek() const {
            if (ll.head) {
                std::cout << ll.head -> data << std::endl;
            }
        }


};

int main() {
    Queue q = Queue(5);
    q.enqueue(0);
    q.enqueue(1);
    q.enqueue(2);
    q.displayQueue();
    q.enqueue(3);
    q.enqueue(4);

    std::cout << "Testing display\n";
    q.displayQueue();

    try {
        q.enqueue(99);
    } catch (...) {
        std::cout << "could not push value into queue\n";
        std::cout << "Indeed is list full?" << q.isFull() << std::endl;
    }

    std::cout << "Testing peek\n";
    q.peek();

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();

    try {
        q.dequeue();
    } catch (...) {
        std::cout << "Queue empty test:\n";
        q.displayQueue();
        std::cout << "could not pop value into queue\n";
        std::cout << "Indeed is queue empty" << q.isEmpty() << std::endl;
    }



}