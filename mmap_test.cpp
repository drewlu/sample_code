/*
 * =====================================================================================
 *
 *       Filename:  mmap_test.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  06/20/2013 08:42:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jason.gs (), 
 *        Company:  Aliyun
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <iostream>

using namespace std;

size_t mmap_size = 512*1024;
size_t sleep_sec = 10;

int main(int argc, char *argv[]) {
    const char *file = "/tmp/mmap.dat";
    int fd = open(file, O_CREAT|O_RDWR|O_TRUNC);
    if (fd < 0) {
        cout << "failed to open"<< endl;
        exit(1);
    }

    if (argc > 1) {
        mmap_size = atoi(argv[1]);
    }
    if (argc > 2) {
        sleep_sec = atoi(argv[2]);
    }

    if(ftruncate(fd, mmap_size) < 0) {
        cout << "failed to truncate to:" << mmap_size << ", erno:" << errno << endl;
        exit(2);
    }


    struct stat statbuf;
    if (fstat(fd, &statbuf) < 0) {
        cout << "fstat error";
        exit(errno);
    }

    cout << "size:" << statbuf.st_size << endl;
    void *p;
    if ((p = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        cout << "mmap failed";
        exit(errno);
    }

    const char *rd = "this is a mmap test\n";
    memcpy(p, rd, strlen(rd));

#if 0
    void *pdst = memcpy((char*)p+mmap_size, rd, strlen(rd));
    if ((char*)pdst - (char*)p != mmap_size) {
        cout << "memcpy beyond boundary failed" << errno << endl;
    }
#endif

    //sleep(sleep_sec);
    cout << mmap_size/10 << endl;
    for (int i=0; i<10; i++) {
        memset((char*)p+i*mmap_size/10, 'a'+i, i*mmap_size/10);
        sleep(10);
    }

    return 0;
}
