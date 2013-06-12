/**
 * Este aplicacion representa a una entidad crediticia la cual
 * concentra todos los creditos otorgados a los clientes de
 * diferentes entidades.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <unistd.h>

#define PORT 3550 /* El puerto que será abierto */
#define BACKLOG 2 /* El número de conexiones permitidas */

int  search(int msgsock, char* Buffer,int size){
	int a=0;
	char rfc[500];	
	char line[1024];	
	char rfc2[1024];
	int retval=0;
	FILE *file;
	file = fopen("loans.txt", "r");
	
	for(a=0;a<(strlen(Buffer)-1);a++)
		rfc[a]=Buffer[a];
		
	//size = strlen(rfc);
	//printf("\n%d : %s\n",size,rfc);
	int b=0;
	if (file) {	
		printf("\n\n\n");
		while(fgets(line, sizeof(line), file)) 
		{
			
			if (strstr(line,rfc)) 
			{
				printf("%s", line);	
				for(a=0;a<=strlen(line);a++){
					rfc2[b]=line[a];				
					b++;				
				}				
			}								
		}
	
		rfc2[b] = '?';
		//int ss = sizeof(rfc2);
		//printf("%d",ss);

		int sizze=0;
		for(a=0;a<sizeof(rfc2);a++){
			if(rfc2[a]=='?')
				sizze=a-1;
		}
		
		//retval = send(msgsock,rfc2,sizeof(rfc2),0);
		retval = send(msgsock,rfc2,sizze,0);
		printf("\n\n\n");
		fclose(file);
	}
	return retval;
 }
 

void doprocessing (int sock)
{
    int n;
	int x=0, pipe = 0;
    char buffer[256],buffer2[] = "ROMS260389JSAULO1", line[100];
	char c;
	FILE *file;
	file = fopen("loans.txt", "r");
	//File *file;
	//file = fopen("loans.txt","r");

    memset(&(buffer), '0', 256);
    int recvMsgSize;
    
    /* Receive message from client */
    if ((recvMsgSize = recv(sock, buffer, 256, 0)) < 0)
        perror("ERROR reading to socket-");

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
		if (socket_type != SOCK_DGRAM){
			retval = search(msgsock,Buffer, sizeof(Buffer));
		}
        else{			
            retval = sendto(msgsock, Buffer, sizeof(Buffer), 0, (struct sockaddr *)&from, fromlen);			
		}
        /* Echo message back to client */
		/*if (strstr(line,buffer2)) 
		{
			
			if (send(sock, line, strlen(line), 0) != recvMsgSize){
				printf("\nEntro aqui\n");
				
					printf("\nBuffer: %s\n",buffer);
					printf("\nLine: %s\n",line);
					printf("Buffer2: %s\n",buffer2);
						if (strstr(line,buffer2)) 
						{
							printf("\n%s", line);
							if (send(sock, line, 100, 0) != 0 || send(sock, line, strlen(line), 0) == 0)
								printf("\nHere\n\n");
						}			
					//}
				//}
			}
		}*/
		//if (send(sock, line, strlen(line), 0) != recvMsgSize)
		
			//perror("ERROR writing to socket");

        /* See if there is more data to receive */
        if ((recvMsgSize = recv(sock, buffer, 256, 0)) > 0)
            perror("ERROR reading to socket+");
    }

    closesocket(sock);    /* Close client socket */
}

BOOL initW32() 
{
		WSADATA wsaData;
		WORD version;
		int error;
		
		version = MAKEWORD( 2, 0 );
		
		error = WSAStartup( version, &wsaData );
		
		/* check for error */
		if ( error != 0 )
		{
		    /* error occured */
		    return FALSE;
		}
		
		/* check for correct version */
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
		     HIBYTE( wsaData.wVersion ) != 0 )
		{
		    /* incorrect WinSock version */
		    WSACleanup();
		    return FALSE;
		}	
}

int main()
{

	 initW32(); /* Necesaria para compilar en Windows */ 
	 	
   int fd, fd2; /* los descriptores de archivos */

   /* para la información de la dirección del servidor */
   struct sockaddr_in server;

   /* para la información de la dirección del cliente */
   struct sockaddr_in client;

   unsigned int sin_size;

   pid_t pid;

   /* A continuación la llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
      printf("error en socket()\n");
      exit(-1);
   }

   server.sin_family = AF_INET;

   server.sin_port = htons(PORT);

   server.sin_addr.s_addr = INADDR_ANY;
   /* INADDR_ANY coloca nuestra dirección IP automáticamente */

   //bzero(&(server.sin_zero),8);
   memset(&(server.sin_zero), '0', 8);
   /* escribimos ceros en el reto de la estructura */


   /* A continuación la llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
      printf("error en bind() \n");
      exit(-1);
   }

   if(listen(fd,BACKLOG) == -1) {  /* llamada a listen() */
      printf("error en listen()\n");
      exit(-1);
   }

   while(1) {
      sin_size=sizeof(struct sockaddr_in);
      /* A continuación la llamada a accept() */
      if ((fd2 = accept(fd,(struct sockaddr *)&client, &sin_size))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }

      printf("Se obtuvo una conexion desde %s\n", inet_ntoa(client.sin_addr) );
      /* que mostrará la IP del cliente */

      send(fd2,"Bienvenido a mi servidor.\n",26,0);
      /* que enviará el mensaje de bienvenida al cliente */
	  
      
      doprocessing(fd2);

   } /* end while */
}

