#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

// Cliente:
int main(int argc, char** argv) {
	// processa argumentos da linha de comando:
	// host_do_servidor porto_servidor nome_arquivo tam_buffer
	// chama gettimeofday para tempo inicial
	// faz abertura ativa a host_do_servidor : porto_servidor
	// envia string com nome do arquivo (terminada em zero)
	// abre arquivo que vai ser gravado - pode ser fopen(nome,"w+")

	// loop recv buffer até que perceba que o arquivo acabou
	// 	escreve bytes do buffer no arquivo (fwrite)
	//	atualiza contagem de bytes recebidos
	// fim_loop

	// fecha conexão e arquivo
	// chama gettimeofday para tempo final e calcula tempo gasto
	// imprime resultado: "Buffer = %5u byte(s), %10.2f kbps (%u bytes em %3u.%06u s)"

	exit(EXIT_SUCCESS);
}
