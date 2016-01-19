/*
 * readHID.c
 *
 *  Created on: Jan 8, 2016
 *      Author: donald
 */
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define A 0
#define B 1

int get_lead(int fd) {
        int value;
        lseek(fd, 0, 0);

        char buffer[1024];
        int size = read(fd, buffer, sizeof(buffer));
        if (size != -1) {
                buffer[size] = NULL;
                value = atoi(buffer);
        }
        else {
                value = -1;
        }

        return value;
}

int main() {
        int count=0;
		int fd[2];
        unsigned long tagID =0;
        fd[A] = open("/sys/class/gpio/gpio67/value", O_RDONLY);
        fd[B] = open("/sys/class/gpio/gpio68/value", O_RDONLY);

        struct pollfd pfd[2];

        pfd[A].fd = fd[A];
        pfd[A].events = POLLPRI;
        pfd[A].revents = 0;

        pfd[B].fd = fd[B];
        pfd[B].events = POLLPRI;
        pfd[B].revents = 0;

        int lead[2];
        while (1) {

                printf("ready:\n");
                while(1){
                	 int ready = poll(pfd, 2, -1);

                	 lead[A] = get_lead(fd[A]);
                	 lead[B] = get_lead(fd[B]);

                	 if (pfd[A].revents == 0)
                	 {
                		 count++;
                		 tagID <<= 1;
                	 }
                	 if (pfd[B].revents == 0)
                	 {
                		 count++;
                		 tagID |= 1;
                		 tagID <<= 1;
                	 }
                	 if (count >=35) break;
                }
                count = 0;
                printf("ID: %lu\n",tagID);
                printf("count %d\n", count);
                tagID = 0;
        }
	return 0;
}


