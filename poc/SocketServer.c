#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdint.h>

#define SOCKET_NAME "/tmp/testsocket123.socket"
#define BUFFER_SIZE 12

int main()
{
    struct sockaddr_un addr;
    int ret;
    int data_socket;
    unsigned char array[4];

    /* Create local socket. */
    data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (data_socket == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));

    /* Bind socket to socket name. */
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

    ret = bind(data_socket, (const struct sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    ret = listen(data_socket, 20);
    if (ret == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

        //int data_socket;
        /* Wait for incoming connection. */
	data_socket = accept(data_socket, NULL, NULL);
	if (data_socket == -1) {
	   perror("accept");
	   exit(EXIT_FAILURE);
	}

	/* Request result. */
	int num;
	
	scanf("%d", &num);
	while(1)
	{
	  if(num == 1)
	  {
	    array[0] = 5;
	    array[1] = 10;
	    array[2] = 15;
	    array[3] = 20;
	    printf("NUMBER TO BE SENT: %d, %d, %d, %d\n", array[0], array[1], array[2], array[3]);

	    ret = write(data_socket, array, sizeof(array));
	    if (ret == -1) 
	    {
	      perror("write");  
	      exit(EXIT_FAILURE);
	    }
	  }
	  if(num == 2)
	    break;
	  scanf("%d", &num);
        }

	/* Close socket. */
	unlink(SOCKET_NAME);
	close(data_socket);
	exit(EXIT_SUCCESS);
}

