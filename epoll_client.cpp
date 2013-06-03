#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#include <sstream>
#include <iostream>
#include <string>
using namespace std;

#define MAXEVENTS 128
int PORT = 43242;
int BUFFER_SIZE = 4096;
int read_loop = 0;
int write_loop = 0;


char *outbuf;
char *inbuf;

static int init_buf(size_t max) {
    outbuf = (char *)malloc(BUFFER_SIZE);
    inbuf = (char *)malloc(BUFFER_SIZE);

    size_t i = max;
    while (i-->0) {
        outbuf[i] = 'A';
    }

    outbuf[max-1] = 'E';
}

static int
make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}

static int
create_and_bind (int port)
{
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("0.0.0.0"); /* set destination IP number */ 
    dest.sin_port = htons(port);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        cout << "socket return error, errno:" << errno << endl;
    } else {
        cout << "settle socket fd " << fd << endl;
    }

    if (bind(fd,  (struct sockaddr *)&dest, sizeof(struct sockaddr)) < 0) {
        cout << "failed to bind, errno:" << errno << endl;
    }

    return fd;
}

int init_server(int port) {
    int sfd = create_and_bind(port);
    if (sfd == -1)
        abort ();

    int s = make_socket_non_blocking (sfd);
    if (s == -1)
        abort ();

    s = listen (sfd, SOMAXCONN);
    if (s == -1)
    {
        perror ("listen");
        abort ();
    }

    return sfd;
}

int init_client(const char *host, int port) {
    struct sockaddr_in dest;
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
        cout << "failed to connect, errno:" << errno << ", fd:" << fd << endl;
        cout << "failed to connect, host:" << host << ", port:" << port << endl;
    }

    if (0 != make_socket_non_blocking(fd)) {
        cout << "failed to make client nonblocking, errno:" << errno << endl;
        abort();
    }
    return fd;
}

void prepare_client(int efd, int cfd) {
    struct epoll_event event;
    event.events = EPOLLOUT | EPOLLET;
    event.data.fd = cfd;
    cout << "EPOLL_CTL_ADD " << cfd << endl;
    int s = epoll_ctl (efd, EPOLL_CTL_ADD, cfd, &event);
    if (s == -1) {
        perror ("epoll_ctl");
        abort ();
    }
}

void client_loop(int efd, int cfd) {
    int timeout = -1;
    struct epoll_event inevent;
    struct epoll_event outevent;
    struct epoll_event *events;


    /* The event loop */
    ssize_t count = 0;

    /* Buffer where events are returned */
    events = (struct epoll_event *)calloc (MAXEVENTS, sizeof inevent);

    while (1) {
        int n, i, done, s;

        n = epoll_wait (efd, events, MAXEVENTS, timeout);

        for (i = 0; i < n; i++) {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)) {
                /* An error has occured on this fd, or the socket is not
                   ready for reading (why were we notified then?) */
                cout << "client epoll error" << endl;
                close (events[i].data.fd);
                continue;
            } 


            if (events[i].events & EPOLLIN) {
                ++read_loop;
                //cout << "read from server" << endl;
                count = ::read(events[i].data.fd, inbuf, BUFFER_SIZE);
                if (count == -1) {
                    /* If errno == EAGAIN, that means we have read all
                       data. So go back to the main loop. */
                    if (errno != EAGAIN)
                    {
                        perror ("read");
                        done = 1;
                    }
                    break;
                } else if (count == 0) {
                    /* End of file. The remote has closed the
                       connection. */
                    done = 1;
                    break;
                }

                outevent.data.fd = events[i].data.fd;
                outevent.events = EPOLLOUT | EPOLLET;
                /* FIXME: with CTL_MOD or CTL_ADD, or MOD as all? */
                s = epoll_ctl(efd, EPOLL_CTL_MOD, events[i].data.fd, &outevent);
                if (s == -1) {
                    perror ("write");
                    abort ();
                }
            } else if (events[i].events & EPOLLOUT) {
                ++write_loop;

                int newfd = events[i].data.fd;

                //cout << "write to server, fd:" << newfd << endl;
                //cout << "cfd:" << cfd << ", buffsize:" << BUFFER_SIZE << endl;
                size_t real = ::write(newfd, outbuf, BUFFER_SIZE);

                if (real <= 0) {
                    cout << "errno:" << errno << ", real:" << real << endl;
                } else if (real < count) {
                    cout << "errno:" << errno << ", real:" << real << endl;
                } else {
                    //cout << "errno:" << errno << "omg client:" << real << endl;
                }

                outevent.data.fd = events[i].data.fd;
                outevent.events = EPOLLIN | EPOLLET;
                /* FIXME: with CTL_MOD or CTL_ADD, or MOD as all? */
                if (epoll_ctl(efd, EPOLL_CTL_MOD, events[i].data.fd, &outevent) < 0) {
                    cout << "failed to epoll_ctl, CTL_MOD, done" << endl;
                }
            }

#if 0
            if (done)
            {
                printf ("Closed connection on descriptor %d\n",
                        events[i].data.fd);

                /* Closing the descriptor will make epoll remove it
                   from the set of descriptors which are monitored. */
                close (events[i].data.fd);
            }
#endif
        }
    }

    free (events);
}

int
main (int argc, char *argv[])
{
    size_t i;
    int sfd, s, nclient = 1;
    char *host = "127.0.0.1";
    bool isServer = true;

    if (argc > 1) {
        PORT = atoi(argv[1]);
    }

    if (argc > 2) {
        BUFFER_SIZE = atoi(argv[2]);
    }

    if (argc > 3) {
        isServer = false;
    }

    if (argc > 4) {
        host = argv[4];
    }

    if (argc > 5) {
        nclient = atoi(argv[5]);
    }

    cout << "args:" << endl;
    cout << "host:" << host << endl;
    cout << "port:" << PORT << endl;
    cout << "buffsize:" << BUFFER_SIZE << endl;
    cout << "isServer:" << isServer << endl;
    cout << "nclient:" << nclient << endl;

    init_buf(BUFFER_SIZE);

    int efd = epoll_create(3233);
    if (efd == -1) {
        perror ("epoll_create");
        abort ();
    }

    int cfd;
    for (i=0; i<nclient; i++) {
        cfd = init_client(host, PORT);
        prepare_client(efd, cfd);
    }
    client_loop(efd, sfd);

    close (cfd);

    return EXIT_SUCCESS;
}
