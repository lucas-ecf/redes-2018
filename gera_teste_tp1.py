from random import choice
import string


def gera_arquivo_teste(size):
    # quais os tipos de caracteres aceitos
    caracteres = string.ascii_letters + string.whitespace

    # conteudo do arquivo de teste
    key_string = ''

    for k in range(size):
        key_string += choice(caracteres)

    return key_string


def main():
    # cria nome do arquivo
    nome_p1 = 'test'
    nome_p2 = 0
    nome_p3 = '.txt'
    nome = nome_p1 + str(nome_p2) + nome_p3

    # numero de caracteres do arquivo: 300 kB
    size = 300000

    # numero maximo de caracteres do arquivo: 30 MB
    size_max = 30000000

    while size < size_max:
        arq = open(nome, 'w')
        arq.write(gera_arquivo_teste(size))
        arq.close()

        # criar novo arquivo
        nome_p2 = nome_p2 + 1
        nome = nome_p1 + str(nome_p2) + nome_p3

        # atualiza o tamanho do arquivo
        size = size*2


if __name__ == '__main__':
    main()
