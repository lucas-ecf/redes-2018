#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

/*Server*/
int main(int argc, char **argv)
{
    int server_socket, client_socket, v6only, buffer_server = 0, tam_nome_arquivo = 0, cont = 0;
    char client_ip[150], byte, nome_temp[1000];
    unsigned int size, time_delay_s, time_delay_us;
    FILE *arq;
    struct sockaddr_in6 server_addr, client_addr;
    struct timeval start, end;

    if (argc != 3)
    {
        printf("\n[TCP Server] Erro nos argumentos.\n\n");
        exit(1);
    }
    buffer_server = atoi(argv[2]);
    server_socket = socket(AF_INET6, SOCK_STREAM, 0); // AF_INET6 --> IPv6, SOCK_STREAM --> TCP
    if (server_socket == -1)
    {
        printf("\n[TCP Server] Socket error.\n\n");
        exit(1);
    }
    /* IPv4 and IPv6 */
    v6only = 0;
    if (setsockopt(server_socket, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only)) != 0)
    {
        printf("\n[TCP Server] Socket IPv6/IPv4 error.\n\n");
        exit(1);
    }
    /* Configure settings in address struct */
    memset(&server_addr, 0, sizeof(server_addr)); // Cleaning the entire struct
    server_addr.sin6_family = AF_INET6;           // IPv6
    server_addr.sin6_addr = in6addr_any;          // Any IP address for the server
    server_addr.sin6_port = htons(atoi(argv[1])); // Gets the port number by the first argument

    /* Bind  */
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("\n[TCP Server] Bind Error\n\n");
        exit(1);
    }
    size = sizeof(struct sockaddr_in6);

    listen(server_socket, 5);
    //  while(1) {
    printf("[TCP Server] Esperando Cliente...\n\n");

    client_socket = accept(server_socket, NULL, NULL); // Blocks the execution waiting por clients
    if (client_socket < 0)
    { // Test the new socket.
        perror("[TCP Server] Erro de conexao.\n");
        exit(1);
    }

    // Informa;'ao do cliente
    getpeername(client_socket, (struct sockaddr *)&client_addr, &size);
    if (inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip, sizeof(client_ip)))
    {
        printf("[TCP Server] Cliente [%s:%d] Conectado!\n\n", client_ip, ntohs(client_addr.sin6_port));
    }
    //-----------------------------Conexao estabelecida / Iniciar transferência --------------------------------------//
    gettimeofday(&start, NULL);

    do
    {
        recv(client_socket, &byte, sizeof(byte), 0);
        nome_temp[cont] = byte;
        cont++;
    } while (byte != '\0');

    tam_nome_arquivo = strlen(nome_temp) + 1;
    char nome_arquivo[tam_nome_arquivo];
    strcpy(nome_arquivo, nome_temp);

    arq = fopen(nome_arquivo, "rb");
    if (arq == NULL)
    {
        printf("erro ao abrir arquivo de saida");
        exit(1);
    }

    char buffer[buffer_server];

    while (fread(buffer, sizeof(byte), buffer_server, arq))
    {
        send(client_socket, buffer, sizeof(buffer), 0);
        memset(&buffer, 0, sizeof(buffer));
    }
    fclose(arq);

    printf("[TCP Server] Cliente [%s:%d] Conexao Encerrada.\n\n", client_ip, ntohs(client_addr.sin6_port));
    close(client_socket); // Libera Socket
                          // }
    //close(server_socket);
    gettimeofday(&end, NULL);
    time_delay_s = (end.tv_sec - start.tv_sec);
    time_delay_us = (end.tv_usec - start.tv_usec);
    printf("\n[TCP Server] Tempo de conexao: %3u.%06u s", time_delay_s, time_delay_us);
    printf("\n[TCP Server] Nome do Arquivo: %s\n", nome_arquivo);
    return 0;
}
