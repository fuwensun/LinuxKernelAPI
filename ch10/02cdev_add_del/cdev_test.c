
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/fcntl.h>

int main(int argc, char **argv){

	int fd, cnt;
	char buf[256];

	printf("char device testing\n");
	fd = open("/dev/my_char_dev",O_RDWR);
	if(!fd){
		printf("the char dev file cannot be opened!\n");
		return 1;
	}
	printf("input the data for kernel: ");
	
	scanf("%s",buf);
	cnt = write(fd,buf,256);
	if(!cnt){
		printf("Write Error!\n");
	}

	cnt = read(fd,buf,256);
	if(!cnt){
		printf("read data error\n");
	}

	printf("read data form kernel is: %s\n",buf);
	close(fd);
	printf("close the char dev file and test over\n");
	return 0;
}
