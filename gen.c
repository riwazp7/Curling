/*
 * gen.c 
 *-(c) Riwaz Poudyal 2015
 *-Generates all possible sequences of 2s and 3s gor given length 
 */
#include <stdio.h>

int main() {

	//length of string to generate
	int n;
	scanf("%d", &n);
	
	//Bitwise counter
	long l = 0;

	//if counter<= (2^n)-1
	while (l <= ((1L << n) - 1)) {

		//String to create
		char str[BUFSIZ];
		
		int j;
		
		//jth character of str is either 2 or 3
		for(j = 0; j < n; j++){

			if((l & (1L<<j)) != 0 ){
				str[j] = '2';

			} else {
				str[j] = '3';
			}

		}

		str[n] = '\0';

		fputs(str, stdout);
		putchar('\n');

		l++;

	}
}
