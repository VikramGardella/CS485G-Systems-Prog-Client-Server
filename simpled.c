//this is simpled.c, based off of echoserveri.c
#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>


void echo(int connfd){

}

int simpleSet(char *MachineName, int TCPport, int secKey, char *varN, char *value, int dataLength){return 0;}


int simpleGet(char *MachineName, int TCPport, int secKey, char *varN, char *value, int *resultLength){return 0;}


int simpleDigest(char *MachineName, int TCPport, int secKey, char *data, int dataLength, char *result, int *resultLength){return 0;}


int simpleRun(char *MachineName, int TCPport, int secKey, char *request, int *resultLength){return 0;}


int main(int argc, char **argv){

	int listenfd, connfd, port, secretKey, theirKey;
	socklen_t clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp, detail, machineName, varName, varValue;
	char keyString[MAXLINE], theirString[MAXLINE], buffer[MAXLINE], type[MAXLINE];
	int inadd = INADDR_ANY;
	int forbuf, completion = 0;
	char **splitB;
	char *vars[64], *vals[64];
	int varInd = 0;

	
//	rio_t rio;
	fprintf(stdout, "INADDR_ANY is %d\n", inadd);

	if(argc != 3){
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]);
	secretKey = atoi(argv[2]);
	sscanf(argv[2], "%d", &secretKey);
	//sprintf(keyString, "%d", secretKey);
	fprintf(stdout,"The secret key for the server is %d\n", secretKey);
	listenfd = Open_listenfd(port);
	while(1){//continuously looking for connections until termination
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		/* Determine the domain name and IP address of the client */
		hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		if(connfd<0)
			fprintf(stderr,"Error accepting client to connecting socket.\n");
		haddrp = inet_ntoa(clientaddr.sin_addr);
		printf("server connected to %s (%s)\n", hp->h_name, haddrp);

		forbuf = read(connfd, buffer, 255);
		printf("The client said: %s\n", buffer);
		int i, j=0, in = 0, foundAlready = 0, typeInd = 2;
		type[0] = 's';
		type[1] = 's';
		for(i=1; i<strlen(buffer); i++){
			if(buffer[i]=='s'&&buffer[i-1]=='s'&&foundAlready==0){
				in = 1;
			}
			else if(in==1){
				if(buffer[i]==' '){
					in = 0;
					foundAlready = 1;
				}
				else
					type[typeInd++] = buffer[i];
			}
		}

		printf("type is %s\n", type);
		printf("about to split by spaces\n");
		char *piece = strtok(buffer, " ");
		int bufInd = 0;
		while(piece!=NULL){
			printf("%s\n",piece);
			piece = strtok(NULL, " ");
			if(bufInd == 1)
				machineName = piece;
		//		printf("piece at 1 is: %s\n", piece);
			if(bufInd == 3){
		//		printf("piece at 3 is: %s\n", piece);
				sscanf(piece, "%d", &theirKey);
				//theirKey = piece;
			}
			if(bufInd == 4)
				varName = piece;
			if(bufInd == 5)
				varValue = piece;
			bufInd++;
		}

//		sprintf(theirString, "%d", theirKey);
		printf("theirs: %d, mine: %d\n", theirKey, secretKey);
		if(theirKey == secretKey){
			printf("Access granted.\n\n");
			vars[varInd] = varName;
			vals[varInd] = varValue;
			printf("Setting %s to %s.\n\n", varName, varValue);
		}
		else
			printf("Access denied, invalid key.\n\n");

		printf("Secret key attempt = %d\n", theirKey);
		printf("Request type = %s\n", type);
	//	printf("Detail = %s\n", varName);
		if(completion==0)
			printf("Completion = failure\n\n");
		else
			printf("Completion = success\n\n");

		forbuf = write(connfd, "received the message\n", MAXLINE);

		echo(connfd);
		Close(connfd);
	}
	exit(0);
}
