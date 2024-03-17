
#include <bits/stdc++.h>
//#include "ui_designer.h"

using namespace std;

struct node {
    shared_ptr<node> prev, next;
    virtual string get_data() = 0;
};

struct numNode : public node {
    int data;
    numNode(int data) : data(data) {};
    string get_data() override {return to_string(data);}
};

struct strNode : public node {
    string data;
    strNode(string data) : data(data) {};
    string get_data() override {return data;}
};

struct List {
    shared_ptr<node> first, cur, last;
    void add_node(shared_ptr<node> newNode) {
        if (!first)
            first = last = cur = newNode;
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
    }
    void del_cur_node() {
        if (!cur)
            return;
        if (cur->prev)
            cur->prev->next = cur->next;
        else first = cur->next;
        
        if (cur->next)
            cur->next->prev = cur->prev;
        else last = cur->prev;
        
        cur = cur->next;
    }

    void print() {
        shared_ptr<node> temp = first;
        while (temp) {
            cout << temp->get_data() << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    void print_reverse() {
        shared_ptr<node> temp = last;
        while (temp) {
            cout << temp->get_data() << " ";
            temp = temp->prev;
        }
        cout << "\n";
    }
    void sum() {
        int numSum = 0;
        string strSum;
        shared_ptr<node> temp = first;
        while (temp != nullptr) {
            if (dynamic_cast<numNode*>(temp.get()) != nullptr)
                numSum += dynamic_cast<numNode*>(temp.get())->data;
            else if (dynamic_cast<strNode*>(temp.get()) != nullptr)
                strSum += dynamic_cast<strNode*>(temp.get())->data + " ";
            
            temp = temp->next;
        }
        cout << "Sum of numbers: " << numSum << endl;
        cout << "Concatenation of strings: " << strSum << endl;
    }
    ~List() {}
};



int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//    app.beep();
    //MyInterface ui; // Создание экземпляра интерфейса
    //QObject::connect(&ui.myButton, &QPushButton::clicked, MyFunction); // Соединение сигнала clicked() кнопки с функцией MyFunction
    //ui.show();
    //return app.exec();
//    return app.exec();
//}
    List lst;
    for (int i = 5; i < 10; ++i)
        lst.add_node(make_shared<numNode>(i));
    
    vector<string> v = {"hello", "how", "are", "you?"};
    for (string& str : v)
        lst.add_node(make_shared<strNode>(str));

    lst.print();
    lst.print_reverse();
    lst.sum();
    lst.del_cur_node();
    lst.print();
    return 0;
}