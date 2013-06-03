#include <iostream>

using namespace std;

class Inner {
public:
    Inner() {
        cout << "this is inner" << endl;
    }
};

class Outter {
    public:
        Outter() {
            k = 0;
        }
    private:
        Inner i;
        int k;
};

int main() {
    Outter o;
}
