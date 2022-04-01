#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

// Para los testeos no se planea agregar chequeo de la entrada
// el correcto funcionamiento de los tests queda a merced del tester
int main(int argc, char** argv){
	/* test: bit
	unsigned int buffer = atoi(argv[1]);
	int pos_bit = atoi(argv[2]);
	printf("%d\n", bit(buffer, pos_bit));
	return 0;
	*/
	
	/* test: ver_binario 
	unsigned int buffer = atoi(argv[1]);
	int pos_ls = atoi(argv[2]);
	int pos_ms = atoi(argv[3]);
	ver_binario(buffer, pos_ls, pos_ms);
	return 0;
	*/
	
	/* test: set_bit 
	unsigned int buffer = atoi(argv[1]);
	int pos = atoi(argv[2]);
	int valor = atoi(argv[3]);
	ver_binario(buffer, 0, 31);
	ver_binario(set_bit(buffer, pos, valor), 0 , 31);
	return 0;
	*/
	
	/* test: crear_mascara 
	int pos_ls = atoi(argv[1]);
	int pos_ms = atoi(argv[2]);
	ver_binario(crear_mascara(pos_ls, pos_ms), 0, 31);
	return 0;
	*/
	
	/* test: concatena */
	unsigned int buffer_ms = 629145;
	unsigned int buffer_ls = 26214;
	ver_binario(concatena(buffer_ms, buffer_ls, 10), 0, 31);
	return 0;
}
