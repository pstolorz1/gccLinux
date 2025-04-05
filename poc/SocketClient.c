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
	   perror("socket");
	   exit(EXIT_FAILURE);
	}

	/*
	* For portability clear the whole structure, since some
	* implementations have additional (nonstandard) fields in
	* the structure.
	*/

	memset(&addr, 0, sizeof(addr));

	/* Connect socket to socket address. */

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

	ret = connect(data_socket, (const struct sockaddr *) &addr,
				  sizeof(addr));
	if (ret == -1) {
	   fprintf(stderr, "The server is down.\n");
	   exit(EXIT_FAILURE);
	}

	/* Request result. */
	while(1)
	{
		/* Receive result. */
		if( read(data_socket, array, sizeof(array)) > 0 );
		{
			printf("RECEIVED NUMBERS: %d, %d, %d, %d\n", array[0], array[1], array[2], array[3]);
		}
	}
	/* Close socket. */

	close(data_socket);

	exit(EXIT_SUCCESS);
}

