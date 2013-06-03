#include <stdlib.h>
using namespace std;

class CC {
public:
    CC(int i) {_i = i;}
    int _i;
};

class CX {
    public:
        void setCC(CC *cc) {
            _cc = cc;
        }
    private:
        CC *_cc;
};

int main() {
    CC cc(3);
    return 0;
}
