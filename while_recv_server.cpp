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

    int s = listen (sfd, SOMAXCONN);
    if (s == -1)
    {
        perror ("listen");
        abort ();
    }

    return sfd;
}

int server_loop(int efd, int sfd) {
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



    ssize_t count;
    while (1) {
        //cout << "read from client" << endl;
        count = ::recv(infd, inbuf, BUFFER_SIZE, 0);
        if (count == -1) {
            /* If errno == EAGAIN, that means we have read all
               data. So go back to the main loop. */
            if (errno != EAGAIN)
            {
                perror ("recv");
            }
            break;
        } else if (count == 0) {
            /* End of file. The remote has closed the
               connection. */
            break;
        }

    }
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

  int efd = epoll_create(3233);
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
