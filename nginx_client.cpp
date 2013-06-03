#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

using namespace std;

#define MAX 1000
#define BSI 240


int main(int argc, char *argv[]) {
    int port, got;
    char *host;

    cout << "argc " << argc << endl;
    cout << "args " << argv[0] << endl;

    if (argc > 1) {
        cout << "args " << argv[0] << endl;
        cout << "args " << argv[1] << endl;
        host = argv[1];
    }

    if (argc > 2) {
        cout << "args " << argv[2] << endl;
        port = atoi(argv[2]);
    }

    cout << "host:" << host << ",port:" << port << endl;

    char readb[BSI];
    struct sockaddr_in dest;
    const char buf[] = "GET /index.html HTTP/1.1\r\nHost: localhost:8088\r\nAccept-Encoding: identity\r\n\r\n";

    //const char buf[] = "POST /?address=nuwa://10.250.6.27:10240/sys/houyi/netc&method=NetcNoop&timeout=20000000&client=Houyi+Web+Console&token=& HTTP/1.1\r\nHost: 10.250.8.212:31267\r\nConnection: keep-alive\r\nTransfer-Encoding: chunked\r\n\r\n17\r\n{\n\"vmName\":\n\"macnat1\"\n}\r\n0\r\n\r\n";

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        cout << "socket return error, errno:" << errno << endl;
    } else {
        cout << "settle socket fd " << fd << endl;
    }

    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(host); /* set destination IP number */ 
    dest.sin_port = htons(port);

    int ret = connect(fd, (struct sockaddr *)&dest, sizeof(struct sockaddr));
    if (ret < 0) {
        cout << "failed to connect, errno:" << errno << endl;
    }

    cout << "sizeof " << buf << " is " << sizeof(buf) << endl;

    try {
        size_t iter = 0;
again:
        cout << " =========== iter " << iter << " ============== " << endl;
        if ((got = write(fd, buf, sizeof(buf))) < 0) {
            cout << "failed to write, errno" << errno << endl;
        }

        cout << "enter read " << endl;

        size_t total = 0;
        readb[0] = '\0';
        if ((got = read(fd, readb, BSI)) != BSI) {
            cout << "read not enough bytes, required:" << BSI << ", got " << got << ", result:" << string(readb) << endl;
        } else {
            cout << "got string " << readb << endl;
        }

        cout << "quit read " << endl;

        sleep(2);
        iter++;
        if (iter < 2)
            goto again;
    }
    catch (int e) {
        cout << e << endl;
    }

#if 0
    total += got;
    cout << "result:" << endl << readb << endl;
#endif

    return 0;
}
