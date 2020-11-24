include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_BUFFER 5
char buf[MAX_BUFFER];
int main(void)
{
        int fd, i, c = 65;
        if ((fd = open("/dev/mydrv", O_RDWR)) < 0){
                perror("open error");
                return -1;
        }
        for (i = 0; i < MAX_BUFFER; i++){
                buf[i] = c++;
        }
        for (i = 0; i < MAX_BUFFER; i++){
                        write(fd, buf, MAX_BUFFER);
                fprintf(stderr, "write into fd %c\n", buf[i]);
                }
        fprintf(stderr, "writing complete(size: %ld)\n",sizeof(buf));

}
