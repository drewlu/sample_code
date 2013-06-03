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

int main(int argc, char *argv[]) {
    int got;
    char readb[BSI];
    struct sockaddr_in dest;
   const char buf[] = "GET / HTTP/1.1\r\nHost: www.baidu.com\r\nConnection: keep-alive\r\n\r\n";
    //const char buf[] = "GET / HTTP/1.1\r\nUser-Agent: curl/7.15.5 (x86_64-redhat-linux-gnu) libcurl/7.15.5 OpenSSL/0.9.8b\r\nzlib/1.2.3 libidn/0.6.5\r\nHost: 220.181.111.85\r\nAccept: */*\r\n\r\n";

   int port = NC_PORT;
   if (argc > 1)
       port = atoi(argv[1]);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        cout << "socket return error, errno:" << errno << endl;
    } else {
        cout << "settle socket fd " << fd << endl;
    }

#if 0
    int one = 1;
    if (0 != setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one))) {
        cout << "failed to set opt , errno " << errno << endl;
    }
#endif

    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("0.0.0.0"); /* set destination IP number */ 
    dest.sin_port = htons(port);

    if (bind(fd,  (struct sockaddr *)&dest, sizeof(struct sockaddr)) < 0) {
        cout << "failed to bind, errno:" << errno << endl;
    }

    if (listen(fd, 5) < 0) {
        cout << "failed to listen, errno:" << errno << endl;
    }

#if 0
    struct sockaddr_in caddr;

    const char *response = "haha, responsed\n";
    while (1) {
        sleep(20);
        cout << "accept begin" << endl;
        int cfd  = accept(fd, NULL, NULL);
        cout << "accept returned" << endl;

        if (cfd < 0) {
            cout << "failed to accept, errno:" << errno << endl;
        }

        write(cfd, response, strlen(response));
        close(cfd);

        cout << "sleep 10s to make connect delay 10s" << endl;
    }
#else
    while (1) sleep(1);

#endif


    return 0;
}
