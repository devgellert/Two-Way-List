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
void out(Node *q) {
    Node *p = q->prev;
    Node *r = q->next;
    p->next = r;
    r->prev = p;
    delete(q);
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
    enum Errors { DOESNOTCONTAIN };
    C2LH(): head(new Node()) {}
    void pushBeforeLarger(Data *data) {
        Node *newNode = new Node(data);
        Node *r = this->head->next;
        while( r != this->head && newNode->data->code >= r->data->code ) { r = r->next; }
        precede(newNode, r);
    }
    int deleteAndGetAmount(Node *q) {
        int val = q->data->amount;
        out(q);
        return val;
    }


    void print() {
        Node *p = this->head->next;
        while (p != this->head) {
            std::cout << "Code: " << p->data->code << " Amount: " << p->data->amount << std::endl;
            p = p->next;
        }
    }
};

void task(C2LH *L, C2LH *LM) {
    Node* l = L->head->next;
    Node* lm = LM->head->next;
    std::cout << "Event logs:" << std::endl ;
    while ( l != L->head && lm != LM->head ) {
        if( l->data->code == lm->data->code ) {
            lm = lm->next;
            l = l->next;
            std::cout << "  " << lm->prev->data->code << " was deleted from LM and " << lm->prev->data->amount << " has added to " << l->prev->data->code << " in L"  << std::endl;
            l->prev->data->amount += LM->deleteAndGetAmount(lm->prev);
        }else if(l->data->code > lm->data->code) {
            try {
                throw C2LH::DOESNOTCONTAIN;
            }catch (C2LH::Errors e) {
                std::cout << "  ERROR: The storage does not contain an item with code " << lm->data->code << std::endl;
            }
            lm = lm->next;
        }else if (l->data->code < lm->data->code) {
            l = l->next;
        }
    }
    std::cout << std::endl ;
}

int main() {
    C2LH *L = new C2LH();
    L->pushBeforeLarger(new Data(5, 1));
    L->pushBeforeLarger(new Data(7, 2));
    L->pushBeforeLarger(new Data(9, 3));
    L->pushBeforeLarger(new Data(25, 4));

    C2LH *LM = new C2LH();
    LM->pushBeforeLarger(new Data(4, 1));
    LM->pushBeforeLarger(new Data(5, 2));
    LM->pushBeforeLarger(new Data(6, 3));
    LM->pushBeforeLarger(new Data(9, 18));
    LM->pushBeforeLarger(new Data(25, 3));

    task(L, LM);

    std::cout << "L: " << std::endl;
    L->print();
    std::cout << "LM: " << std::endl;

    LM->print();


    return 0;
}
