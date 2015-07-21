/* forced.c
 * --Check which characters are forced for a given pattern in a sequence
 * --(c) Riwaz Poudyal
 * Finds occurance of the pattern from start.
 * The length of output array is 2*start.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 249866440  //level 11

int main (int argc, char **argv){

  if (!(argc > 2))  {

    fputs("Usage: forced [sequence(Pattern)] [start position]", stdout);

  } else {
    
    //Starting point( and half the length of output)
    int start;
    start = atoi(argv[2]);
    
    //Pattern to look for
    char *str = argv[1];
    
    //Input sequence
    char *gen = (char*) calloc(MAX, sizeof(char));;
    fgets(gen, MAX , stdin );

    int genLen = strlen(gen);
    int strLen = strlen(str);

    //Outout array--Start with X
    char *output = (char*) calloc(2*start+strLen+1 , sizeof(char));
    memset(output, 'X', 2*start+strLen);
    
    //1st occurance of str pattern in gen starting from start
    char *index = strstr(gen+start, str);
    
    //Loop until more str patters are present.
    //Stop when less than start distance away from the end of gen
    while (index != NULL && gen+genLen-index>start){
      int count;
      int outputCount = 0;
      
      //left half
      for (count = index-gen-start; count<(index-gen); count++){

	if (output[outputCount] == 'X') output[outputCount] = gen[count];
      
	else if (gen[count] != output[outputCount]) output[outputCount] = '-';
	outputCount++;
      }
      
      //Skip current occurance of str
      outputCount+=strLen;
      
      //right half
      for (count+=strLen; count<(index-gen)+ start+strLen; count++){

	if (output[outputCount] == 'X') output[outputCount] = gen[count];

	else if (gen[count] != output[outputCount]) output[outputCount] = '-';
	outputCount++;

      }
      
      //Next occurance
      index = strstr(index+1, str);

    }

    puts(output);          
  }
}
