namespace DY {
class Hacked {
    public:
        void show();
        void show3();
};

class WrapperHacked : public Hacked {
    public:
        void show();
        void show2();
};
}
