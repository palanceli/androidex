#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define HA_DEVICE_NAME "/dev/ha"

int main(int argc, char** argv){
	int fd = -1;
	int value = 0;

	fd = open(HA_DEVICE_NAME, O_RDWR);
	if(fd == -1){
		printf("Failed to open device %s.", HA_DEVICE_NAME);
		return -1;
	}

	printf("Read original value: \n");
	read(fd, &value, sizeof(value));
	printf("%d.\n\n", value);

	value = 100;
	printf("Write value %d to %s.\n\n", value, HA_DEVICE_NAME);
	write(fd, &value, sizeof(value));

	printf("Read the value again:\n");
	read(fd, &value, sizeof(value));
	printf("%d.\n\n", value);

	close(fd);
	
	return 0;
}