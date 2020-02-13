#include "csapp.h"

int main(int argc, char **argv){
	int clientfd, port, secretKey;
	char *host, buf[MAXLINE], *varName, *value;
	rio_t rio;

	if(argc != 6){
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = atoi(argv[2]);
	secretKey = atoi(argv[3]);
	varName = argv[4];
	value = argv[5];

	fprintf(stdout, "host: %s\n", host);
	fprintf(stdout, "port: %d\n", port);
	fprintf(stdout, "secretKey: %d\n", secretKey);
	fprintf(stdout, "varName: %s\n", varName);
	fprintf(stdout, "value: %s\n", value);

	int ind = 0, i, j;
	for(i=0; i<argc; i++){
		for(j=0; j<strlen(argv[i]); j++){
			buf[ind++] = argv[i][j];
		//	printf("%d ", ind);
		}
		buf[ind++] = ' ';
	}

	for(i=0; i<strlen(buf);i++)
		printf("%c", buf[i]);
	printf("\n");


	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);

//	while(Fgets(buf, MAXLINE, stdin) != NULL){
		Rio_writen(clientfd, buf, strlen(buf));
		Rio_readlineb(&rio, buf, MAXLINE);
		Fputs(buf, stdout);
		
/*		string parttwo = "Second message from client";
		Rio_writen(clientfd, parttwo, strlen(parttwo));
		Rio_readlineb(&rio, buf, MAXLINE);
		Fputs(buf, stdout);
*/
		Fputs("I am in a non-while loop\n", stdout);
//	}
	//need to send secret key at some point
	//Fputs(secretKey, stdout);
	Close(clientfd);
	exit(0);
}
