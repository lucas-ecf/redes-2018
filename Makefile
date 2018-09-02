all:
	gcc -Wall clienteFTP.c -o clienteFTP
	gcc -Wall servidorFTP.c -o servidorFTP

clean:
	rm -f clienteFTP servidorFTP
