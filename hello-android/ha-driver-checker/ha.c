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

	read(fd, &value, sizeof(value));
	printf("Read original value: %d.\n", value);

	value += 10;
	printf("Write value %d to %s.\n", value, HA_DEVICE_NAME);
	write(fd, &value, sizeof(value));

	read(fd, &value, sizeof(value));
	printf("Read the value again:%d.\n", value);

	close(fd);

	return 0;
}