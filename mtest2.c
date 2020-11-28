/*
 1초에 50 byte를 /dev/mydrv로부터 읽는다.
• 3초에 50 byte를 /dev/mydrv로부터 읽는다.
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

		sleep(1);
		if(read(fd,buf_in,MAX_BUFFER)){
			fprintf(stderr,"mtest2: read success");
		}else{
			fprintf(stderr,"mtest2: read failed");
		}
		fprintf(stderr, "\n");
		sleep(2);
		if(read(fd,buf_in,MAX_BUFFER)){
			fprintf(stderr,"mtest2: read success");
		}else{
			fprintf(stderr,"mtest2: read failed");
		}
        fprintf(stderr, "\n");
        close(fd);
        return 0;
}
