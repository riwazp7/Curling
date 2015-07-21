/* painter.c 
 * --(c) Riwaz Poudyal 2015
 * --Generates postscript to graphically represent a sequence of 2s & 3s or As and Bs
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Change these to change the default values
 */
#define maxSize (1024*1024*1024)
#define DEFAULT 60
#define SMALL 90
#define LARGE 35

/*
 * Change these to set color. COL1 is for A and COL2 for B
 */
static const char* COL1 =  "{ 89 255 div 17 255 div 142 255 div }";
static const char* COL2 = "{ 1 1 0 }";



/*
 * Print Help
 */
static void printUsage(){
  printf("painter.c: Generates postscript to represent sequences graphically\n" );
  printf("Usage: painter -[optional key]\nKeys:\n");
  printf("Default: Medium Boxes\n-s : Small boxes\n-l : Large Boxes \n-c <Value> : Custom Value\n");
}

/*
 * Print postscript
 */
void makeScript(char *str, int max, int strLength){  
  
  fputs("\%!PS-Adobe-3.0\n\n", stdout);

  /* 
   * Constants
   */
  fputs("\%Constants\n\n", stdout);
  fputs("/origin {0 0} def \n", stdout);
  fputs("/color1 ", stdout);
  fputs(COL1, stdout);
  fputs(" def\n", stdout);
  
  fputs("/color2 ", stdout);
  fputs(COL2, stdout);
  fputs(" def\n", stdout);

  fputs("/cols ", stdout);
  printf("%d ", max);
  fputs("def\n", stdout);

  fputs("/scval { 72 8 mul cols div dup neg } def\n", stdout);
  fputs("/transval { 72 .25 mul 10.75 72 mul} def\n", stdout);
  fputs("/lwidval {.022} def\n\n", stdout);

  /*
   * Initialize graphics
   */
  fputs("\%Initialize graphics\n\n", stdout);
  fputs("transval translate\n", stdout);
  fputs("scval scale\n", stdout);
  fputs("lwidval setlinewidth\n\n", stdout);

  /*
   * bx: Draw a box
   */
  fputs("\%Draw a box\n\n", stdout);
  fputs("/bx {\n", stdout);
  fputs("newpath\n", stdout);
  fputs("2 copy\n", stdout);
  fputs("moveto\n", stdout);
  fputs("1 0 rlineto\n", stdout);
  fputs("0 1 rlineto\n", stdout);
  fputs("-1 0 rlineto\n", stdout);
  fputs("0 -1 rlineto\n", stdout);
  fputs("closepath\n", stdout);
  fputs("} def\n\n", stdout);

  /*
   *  A: Draw and color A
   */
  fputs("\%Draw and paint A\n\n",stdout);
  fputs("/A {\n", stdout);
  fputs("bx\n", stdout);
  fputs("color1 setrgbcolor\n", stdout);
  fputs("fill\n", stdout);
  fputs("bx 1 setgray\n", stdout);
  fputs("stroke\n", stdout);
  fputs("spc\n", stdout);
  fputs("} def\n\n", stdout);

  /*
   * Draw and color B
   */
  fputs("\%Draw and paint B\n\n",stdout);
  fputs("/B {\n", stdout);
  fputs("bx\n", stdout);
  fputs("color2 setrgbcolor\n", stdout);
  fputs("fill\n", stdout);
  fputs("bx 1 setgray\n", stdout);
  fputs("stroke\n", stdout);
  fputs("spc\n", stdout);
  fputs("} def\n\n", stdout);

  /*
   * spc: Leave a space
   */
  fputs("\%Leave a space\n\n", stdout);
  fputs("/spc {\n", stdout);
  fputs("exch 1 add exch\n", stdout);
  fputs("} def\n\n", stdout);

  /*
   * nl: move to start of next line
   */
  fputs("\%Move to new line\n\n",stdout);
  fputs("/nl {\n", stdout);
  fputs("1 add\n", stdout);
  fputs("exch\n", stdout);
  fputs("pop\n", stdout);
  fputs("0 exch\n", stdout);
  fputs("} def\n\n", stdout);

  /*
   *  Put origin on the stack
   */
  fputs("origin\n", stdout);

  /*
   * Divide output into lines based max
   */ 
  max *= 2; //Spaces!

  //Count: No. of lines to print sequence in
  int i, count = strLength/max;

  char* temp = (char*) calloc (max*2+1, sizeof(char));
  
  for(i = 0; i < count; i++){

    strncpy(temp, str+i*max, max);

    //Print sequence chunk and new line
    fputs(temp, stdout);
    fputs("nl\n", stdout);    
  }

  //Last incomplete line
  fputs((str+count*max), stdout);
  fputs("\n\n", stdout);
  fputs("showpage\n\n\n\n", stdout);
  free(temp);
}

/*
 *  Converts 2s and 3s to As and Bs
 */
char* convert (char *input){
  
  int i, inputLen = strlen(input);

  for ( i = 0; i < inputLen; i++) {

    if (input[i] == '2') input[i] = 'A';
    else if (input[i] == '3') input[i] = 'B';
			   
  }

  return input;  
}

/*
 *  parse input and add spaces between each character
 */
char* parseInput (char *input){

  input = strdup(input);
  if (input[0] == '2' || input[0] == '3') input = convert(input);

  int i, inputLen = strlen(input);

  char *buffer = calloc(2 * inputLen + 1, sizeof(char));
  char *bp  = buffer;

  for (i = 0; i < inputLen; i++){
    
    if (*(input + i) == 'A'){

      
      strcpy(bp, "A ");
      bp+=2;
    
    } else if (*(input+i) == 'B') {

      strcpy(bp, "B ");
      bp+=2;     
    }
  }
  
  input = NULL;
  input = strdup(buffer);
  free(buffer);

  return input;
}

int main (int argc, char **argv){

  //No of boxes in a line
  int max = DEFAULT;  //Default
  int error = 0;

  if (argc>1) {

    if (strcmp(argv[1], "-s") == 0) max = SMALL;

    else if (strcmp(argv[1], "-l") == 0) max = LARGE;

    else if (strcmp(argv[1], "-c") == 0 && argc>2 ) max = atoi(argv[2]); //Custom

    else {
      
      error = 1;
      printUsage();
      
    }
  }

  if (!error){
    char *str = (char*) calloc (maxSize, sizeof(char));
    fgets(str, maxSize/2-1, stdin); //Spaces!

    str = parseInput(str);
    makeScript( str, max, strlen(str) );
  }
}

