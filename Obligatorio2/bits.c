
/**
 * @file bits.c
 * @author Carlos Gruss
 * @date 09 may 2022
 * @brief Codigo fuente biblioteca de manejo de bits y encriptación 
 * para Obligatorio 1 PIE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bits.h"

// Las posiciones se numeran como: MSB: ... b_7 b_6 ... b_0 :LSB

// Devuelve el valor del bit de buffer en la posicion pos_bit
int bit(unsigned int buffer, int pos_bit){
	for(int i = 0 ; i < pos_bit ; i++){
		buffer = buffer >> 1;
	}
	
	return (buffer & 1);
}

// Imprime el los bits de buffer entre pos_ls y pos_ms (inclusive ambos)
// Se supone 31 >= pos_ms >= pos_ls >= 0
void ver_binario(unsigned int buffer, int pos_ls, int pos_ms){
	for(int i = pos_ms ; i >= pos_ls ; i--){
		printf("%d", bit(buffer, i));
	}
	printf("\n");
	
	return;
}

// Setea el bit de buffer en posicion pos a valor 
// Se supone que valor siempre vale 0 o 1
unsigned int set_bit(unsigned int buffer, int pos, int valor){
	if(valor){
		buffer = buffer | power(2, pos); 
	}
	else{
		buffer = buffer & (UINT_MAX - power(2, pos));
	}
	
	return buffer;
}

// Devuelve una mascara que vale 1 en el rango pos_ms >= x >= pos_ls
// y cero en los demas bits
// Se supone 31 >= pos_ms >= pos_ls >= 0
unsigned int crear_mascara(int pos_ls, int pos_ms){
	unsigned int mascara = 0;
	for(int i = pos_ls ; i <= pos_ms ; i++){
		mascara = set_bit(mascara, i, 1);
	}
	
	return mascara;
}

// Devuelve la concatenacion de los num_bits_ls bits menos significativos de 
// buffer_ls con buffer_ms. Este ultimo se truca en su parte mas significativa
unsigned int concatena(unsigned int buffer_ms, unsigned int buffer_ls, int num_bits_ls){
	unsigned int mask_ls = crear_mascara(0, num_bits_ls - 1);
	 
	buffer_ms = buffer_ms << num_bits_ls;
	buffer_ls = buffer_ls & mask_ls;
	
	return (buffer_ms | buffer_ls);
}

// Devuelve el resultado de espejar los num_bits menos significativos de buffer
// y poner todos los bits en posiciones >= num_bits en cero
// Se supone 31 >= num_bits
unsigned int espejar(unsigned int buffer, int num_bits){
	for(int i = 0 ; i < num_bits / 2 ; i++){
		buffer = permutar_bits(buffer, i, num_bits - 1 - i);
	}
	
	return (buffer & crear_mascara(0, num_bits - 1));
}

// Devuelve uno si la cantidad de bits es par y cero si impar
int paridad(unsigned int buffer){
	int suma_unos = 0;
	for(int i = 0 ; i < sizeof(unsigned int)*CHAR_BIT ; i++){
		suma_unos = ((buffer >> i) & 1) ? suma_unos + 1 : suma_unos;
	}
	
	return !(suma_unos % 2);
}

// Imprime los bits del valor de clave en binario con salto de linea al final
void ver_clave(Clave_t clave){
	ver_binario(clave.valor, 0, clave.largo ? (clave.largo - 1) : 0);
	return;
}

// Devuelve la clave rotada nrot veces a la izquierda sin perdida (circular)
// No se modifica el largo de la clave
Clave_t rotar_clave(Clave_t clave, unsigned int nrot){
	unsigned int valor_aux = 0;
	for(int i = 0 ; i < nrot ; i++){
		for(int j = 0 ; j < clave.largo ; j++){
			valor_aux = set_bit(valor_aux, (j + 1) % clave.largo ,
			bit(clave.valor, j));
		}
		clave.valor = valor_aux;
	}
	
	
	return clave;
}

// Devuelve buffer pasado por un encriptado vigenere usando clave
unsigned int encriptar(unsigned int buffer, Clave_t clave){
	int claves_enteras = clave.valor ? 
	(sizeof(buffer)*CHAR_BIT / clave.largo) : 0;
	
	int num_bits_restantes = clave.valor ? 
	(sizeof(buffer)*CHAR_BIT % clave.largo) : 0;
	
	unsigned int clave_repetida = 0;
	unsigned int bits_restantes = 
	(crear_mascara(clave.largo - 1 - num_bits_restantes, clave.largo - 1) & clave.valor) 
	>> (clave.largo - num_bits_restantes);
		
	for(int i = 0 ; i < claves_enteras ; i++){
		clave_repetida = concatena(clave_repetida, clave.valor, clave.largo);
	}
	clave_repetida = concatena(clave_repetida, bits_restantes, num_bits_restantes);
		
	return (buffer ^ clave_repetida);
}

// Devuelve el resultado de intercambiar el bit de la posicion pos_a 
// con el de la posicion pos_b en buffer
unsigned int permutar_bits(unsigned int buffer, int pos_a, int pos_b){
	int aux_bit;
	
	aux_bit = bit(buffer, pos_b);
	buffer = set_bit(buffer, pos_b, bit(buffer, pos_a));
	buffer = set_bit(buffer, pos_a, aux_bit);
	
	return buffer;
}

// Devuelve base ^ exponent
int power(int base, unsigned int exponent){
	int result = 1;
	for (int i = 0 ; i < exponent ; i++){
		result *= base;
	}
	
	return result;
}
