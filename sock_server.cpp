#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

using namespace std;

#define MAX 200
#define BSI 400000

#define NC_PORT 32456
//#define WITH_NC 1

int main() {
    int got;
    char readb[BSI];
    struct sockaddr_in dest;
   const char buf[] = "GET / HTTP/1.1\r\nHost: www.baidu.com\r\nConnection: keep-alive\r\n\r\n";
    //const char buf[] = "GET / HTTP/1.1\r\nUser-Agent: curl/7.15.5 (x86_64-redhat-linux-gnu) libcurl/7.15.5 OpenSSL/0.9.8b\r\nzlib/1.2.3 libidn/0.6.5\r\nHost: 220.181.111.85\r\nAccept: */*\r\n\r\n";

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        cout << "socket return error, errno:" << errno << endl;
    } else {
        cout << "settle socket fd " << fd << endl;
    }

    int one = 1;
    if (0 != setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one))) {
        cout << "failed to set opt , errno " << errno << endl;
    }

    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number */ 
    dest.sin_port = htons(NC_PORT);

    if (bind(fd,  (struct sockaddr *)&dest, sizeof(struct sockaddr)) < 0) {
        cout << "failed to bind, errno:" << errno << endl;
    }

    if (listen(fd, 5) < 0) {
        cout << "failed to listen, errno:" << errno << endl;
    }

    struct sockaddr_in caddr;

    int cfd  = accept(fd, NULL, NULL);

    if (cfd < 0) {
        cout << "failed to accept, errno:" << errno << endl;
    }

    size_t total = 0;
    while (total < BSI) {
        if ((got = read(cfd, readb, BSI)) < BSI) {
            cout << "read not enough bytes, required:" << BSI << ", got " << got << ", result:" << string(readb) << endl;
        } else {
            cout << "got string " << readb << endl;
        }

        if (got == -1) {
            cout << "errno " << errno << endl;
        }
        cout << "return got:" << got << endl;

        total += got;
    }

    return 0;
}
