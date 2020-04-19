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
    Node(): next(this), prev(this) {}
    Node(Data *data) {
        this->next = this;
        this->prev = this;
        this->data = data;
    }
};

void precede (Node *q, Node *r) {
    Node *p = r->prev;
    q->prev = p;
    q->next = r;
    p->next = q;
    r->prev = q;
}

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
        precede(newNode, p);
        if(this->head->prev->data->code < this->head->data->code) {
            this->head = this->head->prev;
        }

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

class C2LH {
public:
    Node *head;
    C2LH(): head(new Node()) {}
    void pushBeforeLarger(Data *data) {
        Node *newNode = new Node(data);
        Node *r = this->head->next;
        while( r != this->head && newNode->data->code >= r->data->code ) { r = r->next; }
        precede(newNode, r);
    }

    void print() {
        Node *p = this->head->next;
        while (p != this->head) {
            std::cout << "Code: " << p->data->code << " Amount: " << p->data->amount << std::endl;
            p = p->next;
        }
    }
};

int main() {
    C2LH *list = new C2LH();
    list->pushBeforeLarger(new Data(10, 1));
    list->pushBeforeLarger(new Data(2, 1));
    list->pushBeforeLarger(new Data(3, 1));
    list->pushBeforeLarger(new Data(20, 1));
    list->pushBeforeLarger(new Data(5, 1));
    list->pushBeforeLarger(new Data(1, 1));
    list->pushBeforeLarger(new Data(7, 1));
    list->print();


    return 0;
}
