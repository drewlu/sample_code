#include <string>
#include <iostream>
#include <sys/time.h>

using namespace std;

static int64_t time_diff(struct timeval &tr, struct timeval &tl) {
    cout << "tr sec:" << tr.tv_sec << ", usec:" << tr.tv_usec << endl;
    cout << "tr sec:" << tr.tv_sec << ", usec:" << tr.tv_usec << endl;
    cout << "sec " << tr.tv_sec - tl.tv_sec << endl;
    cout << "usec " << tr.tv_usec - tl.tv_usec << endl;
    return (tr.tv_sec-tl.tv_sec)*1000000+(tr.tv_usec-tl.tv_usec);
}

int test_time() {
    struct timeval t0, t1, t2;
    gettimeofday(&t0, NULL);
    usleep(30000);
    gettimeofday(&t1, NULL);
    sleep(1);
    gettimeofday(&t2, NULL);

    cout << "timecost of 30000us " << time_diff(t1, t0) << endl;
    cout << "timecost of 1s + 30000us " << time_diff(t2, t0) << endl;
}

int main() {
    uint64_t ulong = 18445419837344484021ul;
    int64_t ilong = (int64_t)ulong;

    string s = string("abc", 2);
    cout << s << "len:" << s.length() << endl;
    string b = string("abcddd", 3);
    cout << b << "len:" << b.length() << endl;

    int i = min(3, 4);

    string c(b, 2, 2);
    string d(b, 0, 2);
    cout << c << "new len:" << c.length() << i << endl;
    cout << d << "new len:" << d.length() << i << endl;


    cout << "ulong:" << ulong << ", ilong:" << ilong << endl;

    char *cc = static_cast<char *>(malloc(16));
    memset(cc, 1, 3);

    //memcpy(cc, "hello", 5);
    string newcc = string(cc, 7);

    //cout << "new cc :" << newcc << endl;

    test_time();
    return 0;
}
