#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *infile = stdin;
  FILE *outfile = stdout;
  int debug_flag = 0;
  int enc_value = 0;
  int enc_index = 0;
  int c = 0;
  char *enc_string = NULL;
  int len = 0;
  //Iterate over argv and check for debug mode , input or output files and encryption keys.
  for(int i=1 ; i < argc ; i++) {
    if(argv[i][0] == '+') {
      if(argv[i][1] == 'D')
        debug_flag = 1;
      else if(argv[i][1] == 'e') {
        enc_string = argv[i] + 2;
        enc_value = 1;
      }
    }
    else if(argv[i][0] == '-') {
      if(argv[i][1] == 'D')
        debug_flag = 0;
      else if(argv[i][1] == 'e') {
        enc_string = argv[i] + 2;
        enc_value = -1;
      }
      else if(argv[i][1] == 'i') {
        infile = fopen(argv[i] + 2 , "r");
        if (infile == NULL){
          fprintf(stderr , "Unsuccessful fopen operation");
          return 0;
        }
      }
      else if(argv[i][1] == 'o') {
        outfile = fopen(argv[i] + 2 , "w+");
        if (outfile == NULL){
          fprintf(stderr , "Unsuccessful fopen operation");
          return 0;
        }
      }
    }
    if(debug_flag == 1)
        fprintf(stderr , "%s\n" ,  argv[i]);
  }
  //check
  if(enc_string != NULL) {
    while(enc_string[len]!='\0')
      len++;
  }

  c = fgetc(infile);
  if(enc_value!=0) {
    while(c != EOF) {
      if(enc_value > 0) {
        if(48 <= c && c <= 57) // 0-9
          fputc(((c - 48 + (enc_string[enc_index%len] - 48)) % 10) + 48, outfile);
        else if(65 <= c && c <= 90) // A-Z
          fputc(((c - 65 + (enc_string[enc_index%len] - 48)) % 26) + 65, outfile);
        else if(97 <= c && c <= 122) // a-z
          fputc(((c - 97 + (enc_string[enc_index%len] - 48)) % 26) + 97, outfile);
        else // other character
          fputc(c,outfile);
      }
      else {
          if(48 <= c && c <= 57) // 0-9
          fputc(((c - 48 - (enc_string[enc_index%len] - 48) + 10) % 10) + 48, outfile);
        else if(65 <= c && c <= 90) // A-Z
          fputc(((c - 65 - (enc_string[enc_index%len] - 48) + 26) % 26) + 65, outfile);
        else if(97 <= c && c <= 122) // a-z
          fputc(((c - 97 - (enc_string[enc_index%len] - 48) + 26) % 26) + 97, outfile);
        else // other character
          fputc(c,outfile);
      }
      enc_index++;
      c = fgetc(infile);
    }
  }
  else {
    while(c != EOF) {
      fputc(c,outfile);
      c = fgetc(infile);
    }
  }
  if(infile!=stdin)
    fclose(infile);
  if(outfile!=stdout)
    fclose(outfile);
  return 0;
}