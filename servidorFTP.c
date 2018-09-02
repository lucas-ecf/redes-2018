#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

// Servidor:
int main(int argc, char** argv) {
	// processa argumentos da linha de comando:
	// porto_servidor tam_buffer
	// faz abertura passiva e aguarda conexão
	// recebe a string com nome do arquivo
	// abre arquivo que vai ser lido – pode ser fopen(nome,"r")
	// se deu erro, fecha conexão e termina

	// loop lê o arquivo, um buffer por vez até fread retornar zero
	//	envia o buffer lido
	//	se quiser, contabiliza bytes enviados
	// fim_loop

	// fecha conexão e arquivo
	// chama gettimeofday para tempo final e calcula tempo gasto
	// se quiser, imprime nome arquivo e número de bytes enviados

	exit(EXIT_SUCCESS);
}
