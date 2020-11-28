/*
 0초에 50 byte를 /dev/mydrv에 write한다.
• 3초에 50 byte를 /dev/mydrv에 write한다.
• 각 application은 read나 write가 성공적으로 수행되었으면 ‘mtest#: (read/write) success’를 출력하고, 그렇지 못하면 ‘mtest#: (read/write) failed’를 출력한다.

*/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_BUFFER 50
char buf_in[MAX_BUFFER];
char buf_out[MAX_BUFFER];
int main(void)
{
        int fd, i;
        if ((fd = open("/dev/mydrv", O_RDWR)) < 0){
                perror("open error");
                return -1;
        }


        for (i = 0; i < MAX_BUFFER; i++){//0부터 50까지 50bytes
                buf_out[i] = 65;
        }
       // for (i = 0; i < MAX_BUFFER; i++) 
        //        fprintf(stderr, "%c", buf_in[i]);
		if(write(fd, buf_out, MAX_BUFFER)>0){
			fprintf(stderr,"mtest1: write success");
		}else{
			fprintf(stderr,"mtest1: write failed");
		}
		sleep(3);
        if(write(fd, buf_out, MAX_BUFFER)>0){
			fprintf(stderr,"mtest1: write success");
		}else{
			fprintf(stderr,"mtest1: write failed");
		}
        fprintf(stderr, "\n");
        close(fd);
        return 0;
}
