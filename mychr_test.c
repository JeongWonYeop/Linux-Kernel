#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_BUFFER 5
char buf_in[MAX_BUFFER];
char buf_out[MAX_BUFFER];
int main(void)
{
        int fd, i, c = 65;
        if ((fd = open("/dev/mydrv", O_RDWR)) < 0){
                perror("open error");
                return -1;
        }


        for (i = 0; i < MAX_BUFFER; i++){
                buf_in[i] = 65;
				buf_out[i] = c++; // ABCDE
        }
        for (i = 0; i < MAX_BUFFER; i++)
                fprintf(stderr, "%c", buf_in[i]);
        fprintf(stderr, "\n");
        write(fd, buf_out+2, 3); 
        read(fd, buf_in, 3);
        for (i = 0; i < 3; i++)
                fprintf(stderr, "%c", buf_in[i]);
        fprintf(stderr, "\n");
        close(fd);
        return 0;
}
