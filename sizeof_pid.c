#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

struct negotiate_message1
{
   pid_t tapdisk_pid;
   uint16_t mode;
   uint16_t type;
   char confFile[1024];
};

struct negotiate_message
{
   uint16_t mode;
   pid_t tapdisk_pid;
   uint16_t type;
   char confFile[1024];
};

int main() {
    printf("sizeof pid_t:%d\n", sizeof(pid_t));
    printf("sizeof negotiate_message1:%d\n", sizeof(struct negotiate_message1));
    printf("sizeof negotiate_message:%d\n", sizeof(struct negotiate_message));
    sleep(1000);
}
