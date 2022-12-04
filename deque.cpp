// implement circular deque
#include <iostream>
#include <stdexcept>

class CircularDeque {
    private:
        const int size;
        int front, rear;
        int* q = new int[size];

    public:
        CircularDeque(int size): size(size), front(-1), rear(-1) {};
        ~CircularDeque() { delete[] q; }
        void display() {
            std::cout << "-------------------------------------------------------\n";
            int i;
            for (i = front; i != rear; i = ((i+1) % size)) {
                // if (q[i]) {
                std::cout << "El at idx "<< i << ": " << q[i] << std::endl;
                // }
            }
            // if (q[i]) {
            std::cout << "El at idx "<< i << ": " << q[i] << std::endl;
            // }
        }
        void peekFront() {
            std::cout << "Front: " << q[front] << std::endl;
            }
        void peekRear() {
            std::cout << "Rear " << q[front] << std::endl;
            }
        bool isFull() {
            return (front == (rear + 1 ) % size) ? true: false;
            }
        bool isEmpty() {
            return ((front == -1) && (rear == -1)) ? true : false;
            }


        void insertFront(int val) {
            if (isFull()) {
                std::cout << "Queue overflow!\n";
                return;
            } // throw std::overflow_error("Queue overflow!")
            if (isEmpty()) {
                front++;
                rear++;
                q[front] = val;
                return;
            }
            if (front == 0) {
                front = size - 1;
                q[front] = val;
                return;
            }
            front--;
            q[front] = val;
            return;
        }

        void insertRear(int val) {
            if (isFull()) {
                std::cout << "Queue overflow!\n";
                return;
            } // throw std::overflow_error("Queue overflow!")

            if (isEmpty()) {
                insertFront(val);
                return;
            }
            rear = (rear+1) % size;
            q[rear] = val;
            return;
        }

        int deleteFront() {
            int res = q[front];
            if (front == 0 && rear == 0) {
                front = -1;
                rear = -1;
                return res;
            }
            if (front == size - 1) {
                front = 0;
                return res;
            }
            front++;
            return res;
        }

        int deleteRear() {
            int res = q[rear];
            if (front == 0 && rear == 0) {
                front = -1;
                rear = -1;
                return res;
            }
            if (rear==0) {
                rear = size-1;
                return res;
            }
            rear--;
            return res;
        }

};

int main() {
    CircularDeque cdq = CircularDeque(5);

    cdq.insertRear(-5);

    cdq.insertFront(2);
    cdq.insertFront(44);
    cdq.display();

    // cdq.insertFront(5);
    // cdq.insertFront(55);
    // cdq.insertFront(66);
    // cdq.insertFront(77);

    cdq.insertRear(0);
    cdq.insertRear(-1);
    cdq.insertRear(99);

    cdq.display();

    cdq.deleteFront();
    cdq.deleteRear();
    cdq.deleteFront();
    cdq.deleteRear();

    cdq.display();

    // cdq.deleteFront();
    cdq.deleteRear();
    cdq.insertRear(0);

}