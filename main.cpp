#include <iostream>

struct Data {
    int code, amount;
    Data(int code, int amount) {
        this->code = code;
        this->amount = amount;
    }
};

class Node {
public:
    Node *next;
    Node *prev;
    Data *data;

    Node(Data *data) {
        this->next = this;
        this->prev = this;
        this->data = data;
    }
};

class C2l {
public:
    Node *head;
    C2l(Data *headData) {
        this->head = new Node(headData);
    }
    void push(Data *data) {
        Node *newNode = new Node(data);
        Node *p = this->head;
        while( (p->next != this->head)  && p->data->code <= newNode->data->code ) {
            p = p->next;
        };
        if(p->next == this->head && p->data->code < newNode->data->code ) {
            p = p->next;
        }
        Node *temp = p->prev;
        newNode->prev = temp;
        newNode->next = p;
        temp->next = newNode;
        p->prev = newNode;
        std::cout << this->head->data->code << std::endl;
        if(this->head->prev->data->code < this->head->data->code) {
            this->head = this->head->prev;
        }

    }
    void deleteFirst() {

    }


    void printList() {
        Node *p = this->head;
        while(p->next != this->head) {
            std::cout << "Code: " << p->data->code << " Amount: " << p->data->amount << std::endl;
            p = p->next;
        }
        std::cout << "Code: " << p->data->code << " Amount: " << p->data->amount << std::endl;
    }

};

int main() {
    C2l *L = new C2l(new Data(10, 20));
    C2l *LM = new C2l(new Data(10, 30));



    return 0;
}
