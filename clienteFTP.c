#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

// Cliente:
int main(int argc, char** argv) {
	int client_socket, bytes, rv,conta_bytes_recebidos=0,cliente_buffer;
  float kbps;
  unsigned time_delay_s=0,time_delay_us;
  struct addrinfo hints, *list, *item;
  struct timeval start, end;

  /* verifica numero de argumentos */
  if(argc != 5)
   {
    printf("\n[TCP Client] Erro no número de argumentos.\n\n");
    exit(1);
  }
  cliente_buffer = atoi(argv[4]);
  char buffer[cliente_buffer];
  memset(&hints, 0, sizeof hints); // Enche de zeros na nova estrutura
  hints.ai_family = AF_UNSPEC;     // aceitar IPv4 ou IPv6
  hints.ai_socktype = SOCK_STREAM; // Apenas TCP

  if((rv = getaddrinfo(argv[1], argv[2], &hints, &list)) != 0) { // Chama a função passando os dois argumentos
    printf("[TCP Multi Client] getaddrinfo error: %s\n", gai_strerror(rv));
    exit(1);
  }
   // Para cada item obtido da função....
  for(item = list; item != NULL; item = item->ai_next) {
    // Tenta criar o socket
    if((client_socket = socket(item->ai_family, item->ai_socktype, item->ai_protocol)) == -1) {
      printf("[TCP Multi Client]: Erro no socket\n"); // Não deu certo, tenta criar outro socket com novos valores.
      continue;
    }

    // Se criar o socket, tenta realizar a conexão:
    if(connect(client_socket, item->ai_addr, item->ai_addrlen) == -1) {
      close(client_socket); // Não deu certo a conexão! Fecha o socket criado e tenta de novo.
      printf("[TCP Client]: Erro de conexao\n");
      continue;
    }
    break;
  }
  if(item == NULL) exit(1); // Caso todos os itens falhem, será o fim da lista.
//Conectados!
  gettimeofday(&start, NULL); 
  printf("[TCP Client] CONECTADO!.Enviando nome do Arquivo\n");
//envia nome do arquivo
  bytes = strlen(argv[3])+1;
  send(client_socket, argv[3], bytes,0); 

//cria arquivo de saida
  FILE* arq_saida = fopen(argv[3],"wb");

  while(bytes >0) {
    memset(&buffer, 0, sizeof(buffer));
    bytes = recv(client_socket, buffer, sizeof(buffer), 0);  // Esperando por uma resposta do servidor
    conta_bytes_recebidos +=bytes;

    fwrite(buffer,sizeof(char),bytes,arq_saida);
  }
  printf("\n[TCP Client] Fechando conexão...\n");
//Fecha Tempo
    
  close(client_socket); // Releasing the socket.
    gettimeofday(&end, NULL);
    time_delay_s = (end.tv_sec- start.tv_sec);
    time_delay_us =(end.tv_usec- start.tv_usec);
    kbps = (float) (conta_bytes_recebidos*1000)/time_delay_us;
  printf("\nBuffer = %5u byte(s), %10.2f kbps (%u bytes em %3u.%06u s)\n",cliente_buffer,kbps,conta_bytes_recebidos,time_delay_s,time_delay_us);
  freeaddrinfo(list); // liberando a memória!!

	exit(EXIT_SUCCESS);
}
