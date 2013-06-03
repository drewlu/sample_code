#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

using namespace std;

int readNc(int sock) {
}

int readHttp(int sock) {
}

#define MAX 200
#define BSI 400000

#define NC_PORT 32456
//#define WITH_NC 1

int main() {
    size_t got;
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

    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;

#ifndef WITH_NC
    dest.sin_addr.s_addr = inet_addr("220.181.111.85"); /* set destination IP number */ 
    dest.sin_port = htons(80);
#else
    dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number */ 
    dest.sin_port = htons(NC_PORT);
#endif

    int ret = connect(fd, (struct sockaddr *)&dest, sizeof(struct sockaddr));
    if (ret < 0) {
        cout << "failed to connect, errno:" << errno << endl;
    }

    cout << "sizeof " << buf << " is " << sizeof(buf) << endl;

#if 1
    if ((got = write(fd, buf, sizeof(buf))) < 0) {
#else
    if ((got = send(fd, buf, sizeof(buf), 0)) < 0) {
#endif
        cout << "failed to write, errno" << errno << endl;
    } else {
        cout << "write to baidu ok, written" << got << endl;
    }

    size_t total = 0;
    while (total < MAX) {
        if ((got = read(fd, readb, BSI)) != BSI) {
            cout << "read not enough bytes, required:" << BSI << ", got " << got << ", result:" << string(readb) << endl;
        } else {
            cout << "got string " << readb << endl;
        }

        total += got;
    }

    return 0;
}
