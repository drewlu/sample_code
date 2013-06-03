#include <iostream>

using namespace std;


class Yeye {
public:
    virtual void WhoAmI() {
        cout << "wo shi yeye" << endl;
    }
};

class Baba : public Yeye {
public:
    void WhoAmI() {
        cout << "wo shi laoba" << endl;
    }
};

class Erzi : public Baba {
public:
    void WhoAmI() {
        cout << "wo shi Erzi" << endl;
    }
};

class Nobody : public Baba {
public:
    void nobody() {
        cout << "wo shi nobody" << endl;
    }

    void WhoAmI();
};

void Nobody::WhoAmI() {cout << "nobody whoAmI" << endl;}

int main() {
    Erzi erzi;
    erzi.WhoAmI();

    Yeye *who = new Erzi();
    who->WhoAmI();

    Nobody nb;
    nb.nobody();

    nb.WhoAmI();


    return 0;
}
