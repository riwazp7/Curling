/* active.c
 * © 2015 Riwaz Poudyal 
 * Only print Sequences that are active
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tailCount (char* str, int l);
int curl (char* str, int l);

int main(int argc, char**argv)
{
  //Sequence and its 2-extension, 3-extention	
  char str[BUFSIZ], cpy[BUFSIZ], ext2[BUFSIZ], ext3[BUFSIZ] ;
	
  //Tail of the sequence	
  int tail;
	
	
  while ( fgets (str, BUFSIZ, stdin)){

    int l = strlen(str);

    if (str[l-1] == '\n') {	  
      str[l-1] = '\0';
      l--;
    }
    strcpy(cpy, str);
    //Create extension sequences
    sprintf (ext2, "2%s", str); //here
    sprintf (ext3, "3%s", str);
			
    //Find and compare tail lengths	
			
    tail = tailCount(str, l);
			
   
    if ((tailCount (ext2, l+1) > tail) || ( tailCount (ext3, l+1) > tail))
      {
	fputs(cpy, stdout);
	fputs("\n", stdout);
      }
  }
	
}

//Return length of tail
int tailCount (char* str, int l){
	
  int count = 0;
	
  while (str[l-1] != '1'){

    str[l] = curl ( str, l) + '0';
    str[++l] = '\0';
    count++;
  }
	
  return count;
}

int curl (char* str, int l){
  int sz, kurl = 1;

  for (sz = 1; sz <= l/2; sz++){

    char* rt = str + l - sz;
    char* lt = rt - sz;

    int k = 1;

    while (lt >= str) {

      if (strncmp(lt, rt, sz) == 0) {
	k++;
	lt -= sz;
      } else break;
    }

    if (k > kurl) kurl = k;
		
  }

  return kurl;

}
