#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <iostream>

       #include <sys/time.h>
       #include <sys/types.h>
       #include <fcntl.h>

using namespace std;

#define ALIGN_SIZE 512
#define BUFFER_SIZE (2*1024*1024)
#define INTERVAL 64

#if 0
char buffer[BUFFER_SIZE];
#else
void *buffer;
#endif

int start_test(int iosize, int count, const char *file, int flags) {

    int fd = open(file, flags, 00777);
    if (fd < 0) {
        cout << "failed to open file:" << file << ", flags:" << flags << ",errno:" << errno << endl;
        exit(errno);
    } else
        cout << "opened fd:" << fd << endl;

    if (0 != posix_memalign(&buffer, ALIGN_SIZE, BUFFER_SIZE)) {
        cout << "failed to malloc aligned memory, errno:" << errno << endl;
        exit(errno);
    }

    int ret, i=0;
    size_t offset = 0;

    char *p;
    while (i<count) {
        offset = (i*iosize) % BUFFER_SIZE;
        p = ((char *)buffer)+offset;
        if ((ret = pwrite(fd, (void *)p, iosize, iosize*i)) != iosize) {
            cout << "offset:" << offset << ",iosize:" << iosize << endl;
            cout << "failed to write:, errno:" << errno << endl;
            exit(errno);
        }
        i++;
    }

    close(fd);

    free(buffer);
    
    return 0;
}

int start_fsync_test(int iosize, int count, const char *file, int flags) {

    int fd = open(file, flags, 00777);
    if (fd < 0) {
        cout << "failed to open file:" << file << ", flags:" << flags << ",errno:" << errno << endl;
        exit(errno);
    } else
        cout << "opened fd:" << fd << endl;

    if (0 != posix_memalign(&buffer, ALIGN_SIZE, BUFFER_SIZE)) {
        cout << "failed to malloc aligned memory, errno:" << errno << endl;
        exit(errno);
    }

    int ret, i=0;
    size_t offset = 0;

    char *p;
    while (i<count) {
        offset = (i*iosize) % BUFFER_SIZE;
        p = ((char *)buffer)+offset;
        if ((ret = pwrite(fd, (void *)p, iosize, iosize*i)) != iosize) {
            cout << "offset:" << offset << ",iosize:" << iosize << endl;
            cout << "failed to write:, errno:" << errno << endl;
            exit(errno);
        }
        i++;

        if (i % INTERVAL == 0)
            fsync(fd);
    }

    close(fd);

    free(buffer);
    
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "Usage:" << argv[0] << " iosize count filename mode[direct|sync|dsync|both]" << endl;
        exit(1);
    }

    int flags;
    int iosize = atoi(argv[1]);
    int count = atoi(argv[2]);
    char *file = argv[3];

    if (strcmp(argv[4], "direct") == 0)
        flags = O_CREAT | O_TRUNC | O_RDWR | O_DIRECT;
    if (strcmp(argv[4], "sync") == 0)
        flags = O_CREAT | O_TRUNC | O_RDWR | O_SYNC;
    if (strcmp(argv[4], "dsync") == 0)
        flags = O_CREAT | O_TRUNC | O_RDWR | O_DSYNC;
    if (strcmp(argv[4], "both") == 0)
        flags = O_CREAT | O_TRUNC | O_RDWR | O_SYNC | O_DIRECT;
    if (strcmp(argv[4], "buffer") == 0)
        flags = O_CREAT | O_TRUNC | O_RDWR;
    if (strcmp(argv[4], "fsync") == 0)
        flags = O_CREAT | O_TRUNC | O_RDWR;
#if 0
    int flags = O_CREAT | O_TRUNC | O_RDWR | O_SYNC;
    int flags = O_CREAT | O_TRUNC | O_RDWR | O_SYNC;
#endif

    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    if (strcmp(argv[4], "fsync") != 0)
        start_test(iosize, count, file, flags);
    else
        start_fsync_test(iosize, count, file, flags);
    gettimeofday(&end, NULL);

    int64_t usecs = (end.tv_sec-begin.tv_sec) * 1000000 + (end.tv_usec-begin.tv_usec);
    cout << "total count:" << count << ", time spend usecs:" << usecs << ", avg:" << usecs/iosize << endl;
    cout << "iops:" << 1000000/(usecs/iosize) << endl;

    return 0;    
}
