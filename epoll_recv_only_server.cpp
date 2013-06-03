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
int recv_loop = 0;
int send_loop = 0;


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

typedef unsigned long long ticks;
#define CPU_THOUSAND_HZ 240 /* 100ns */
ticks getticks(void) {
    unsigned long long a;
    asm volatile("rdtsc" : "=a" (a) :: "memory");
    return a;
}

double subticks(ticks t1, ticks t2) {
    return (t1-t2)/CPU_THOUSAND_HZ;
}



int accept_handler(int efd, int sfd, struct epoll_event *events) {
    /* We have a notification on the listening socket, which
       means one or more incoming connections. */

    /* FIXME: is it neccessary to register the accept_handler again? */
    struct epoll_event inevent;
#if 0
    while (1)
    {
#endif
        struct sockaddr in_addr;
        socklen_t in_len;
        int infd;
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

        in_len = sizeof in_addr;
        infd = accept(sfd, &in_addr, &in_len);
        if (infd == -1)
        {
            if ((errno == EAGAIN) ||
                    (errno == EWOULDBLOCK))
            {
                /* We have processed all incoming
                   connections. */
#if 0
                break;
#else
                return -1;
#endif
            }
            else
            {
                perror ("accept");
#if 0
                break;
#else
                return -1;
#endif
            }
        }

        int s = getnameinfo (&in_addr, in_len, hbuf, sizeof hbuf,
                sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);

        if (s == 0)
        {
            printf("Accepted connection on descriptor %d "
                    "(host=%s, port=%s)\n", infd, hbuf, sbuf);
        }

        /* Make the incoming socket non-blocking and add it to the
           list of fds to monitor. */
        s = make_socket_non_blocking (infd);
        if (s == -1)
            abort ();

        inevent.data.fd = infd;
        inevent.events = EPOLLIN | EPOLLET;
        s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &inevent);
        if (s == -1)
        {
            perror ("epoll_ctl");
            abort ();
        }
#if 0
    }
#endif

    return 0;
}
//}

int server_loop(int efd, int sfd) {
    struct epoll_event inevent;
    struct epoll_event outevent;
    struct epoll_event *events;


    ticks t1, t2, avg = 0;
    size_t wait_count = 0;

    /* accept handler */
    inevent.data.fd = sfd;
    inevent.events = EPOLLIN | EPOLLET;
    int s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &inevent);
    if (s == -1) {
        perror ("epoll_ctl");
        abort ();
    }

    /* Buffer where events are returned */
    events = (struct epoll_event *)calloc (MAXEVENTS, sizeof inevent);

    /* The event loop */
    ssize_t count = 0;
    while (1) {
        int n, i, done;


        t1 = getticks();
        n = epoll_wait (efd, events, MAXEVENTS, -1);
        t2 = getticks();
        avg = (ticks)(((avg * wait_count) + subticks(t2,t1))/(++wait_count));

        if (wait_count % 102400 == 0) {
            cout << "avg ticks:" << avg << ",ticks" << subticks(t2,t1)
                << ", epoll_wait count:" << wait_count << endl;
        }

        for (i = 0; i < n; i++) {
            /* acceptor */
            if (sfd == events[i].data.fd) {
                accept_handler(efd, sfd, events);
                continue;
            }


            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)) {
                /* An error has occured on this fd, or the socket is not
                   ready for reading (why were we notified then?) */
                cout << "server epoll error" << endl;
                close (events[i].data.fd);
                continue;
            } 


            if (events[i].events & EPOLLIN) {
                ++recv_loop;
                //cout << "read from client" << endl;
                count = ::recv(events[i].data.fd, inbuf, BUFFER_SIZE, 0);
                if (count == -1) {
                    /* If errno == EAGAIN, that means we have read all
                       data. So go back to the main loop. */
                    if (errno != EAGAIN)
                    {
                        perror ("recv");
                        done = 1;
                    }
                    break;
                } else if (count == 0) {
                    /* End of file. The remote has closed the
                       connection. */
                    done = 1;
                    break;
                } else {
                    //cout << "want:" << BUFFER_SIZE << ",got:" << count << endl;
                }

                outevent.data.fd = events[i].data.fd;
                outevent.events = EPOLLIN | EPOLLET;
                /* FIXME: with CTL_MOD or CTL_ADD, or MOD as all? */
                if (epoll_ctl(efd, EPOLL_CTL_MOD, events[i].data.fd, &outevent) < 0) {
                    cout << "failed to epoll_ctl, CTL_MOD, done" << endl;
                }
            } else if (events[i].events & EPOLLOUT) {
                ++send_loop;
                cout << "send to client " << endl;
                size_t real = ::send(events[i].data.fd, outbuf, BUFFER_SIZE, 0);

                if (real <= 0) {
                    cout << "errno:" << errno << ", real:" << real << endl;
                } else if (real < count) {
                    cout << "errno:" << errno << ", real:" << real << endl;
                } else {
                    cout << "errno:" << errno << "omg" << endl;
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


//}

int
main (int argc, char *argv[])
{
  int sfd, s;
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

  cout << "args:" << endl;
  cout << "host:" << host << endl;
  cout << "port:" << PORT << endl;
  cout << "buffsize:" << BUFFER_SIZE << endl;
  cout << "isServer:" << isServer << endl;

  init_buf(BUFFER_SIZE);

  int efd = epoll_create(1);
  if (efd == -1) {
      perror ("epoll_create");
      abort ();
  }

  if (isServer) {
      sfd = init_server(PORT);
      server_loop(efd, sfd);
  }

  close (sfd);

  return EXIT_SUCCESS;
}
