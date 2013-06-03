#include <iostream>

using namespace std;

namespace inherit {
class Parent {
public:
    Parent() {cout << "parent constructor" << endl;}
    Parent(int i) {_i = i; cout << "parent constructor with i:" << i << endl;}
    ~Parent() {cout << "parent destructor" << endl;}
    void show_i() {cout << "i:" << _i << endl;}

private:
    int _i;
};

class Child : public Parent {
public:
    Child() {cout << "child constructor" << endl;}
    Child(int i):Parent(i) {cout << "child constructor, i:" << i << endl;}
    ~Child() {cout << "child destructor" << endl;}
    //void show_i() {cout << "i:" << _i << endl;}
private:
    int _i;
};
}

using namespace inherit;
int main() {
    string s = "abc";

    Child c(3);
    c.show_i();
}
