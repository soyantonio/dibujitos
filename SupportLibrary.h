/**
* @author Antonio Perez
* @brief (Ubuntu 16.04) Library for my own purposes
* @date  23 Nov 2016
* @file SupportLibrary.h
* @version 1.1.0
*/

#ifndef SUPPORTLIBRARY_H_INCLUDED
#define SUPPORTLIBRARY_H_INCLUDED

#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

extern int    slRandom(int lwr_lim, int upr_lim);
extern double slPower(double base, int exponent);
extern void   slAddInFile(char *filename, char *before, char *now, char *after, int add_line_break);
extern void   slClearBuffer();
extern void   slClearWindow();
extern void   slCreateFile(char *filename);
extern void   slEncrypt();
extern void   slGetString(char *string, int max_char);
extern void   slPrintFile(char *filename, char *before, FILE *dest, int remove_line_break);
extern void   slToContinue(char *text);
extern void   slToLwrStr(char *str);
extern void   slToUprStr(char *str);


/**
* @brief Generate a random number
* @param lwr_lim Inferior limit of the random number
* @param upr_lim Superior limit of the random number
* @return number
*/
extern int slRandom(int lwr_lim, int upr_lim){
  int number = rand()%(upr_lim - lwr_lim + 1) + (lwr_lim);
  return number;
}

/**
* @brief Get Power of a number
* @param double base
* @param int exponent
* @return number
*/
extern double slPower(double base, int exponent){
  double result = 1, i;
  for(i = 0; i < exponent || i < (exponent * -1); i++) result *= base;
  if(exponent < 0) result = 1 / result;
  return result;
}

extern void slAddInFile(char *filename, char *before, char *now, char *after, int add_line_break){
  FILE *fp = fopen(filename, "a");
  char line_break[10] = "";
  if(add_line_break) strcpy(line_break, "\n");
  fprintf(fp, "%s%s%s%s", before, now, after, line_break);
  fclose(fp);
}


/**
* @brief Remove \n from buffer
* @param Nothing
* @return Nothing
*/
extern void slClearBuffer(){
  int cls;
  while ((cls = getchar()) != '\n' && cls != EOF);
}

/**
* @brief Execute "clear" or "cls" to clear console
* @param Nothing
* @return Nothing
*/
extern void slClearWindow(){
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

extern void slCreateFile(char *filename){
  FILE *fp = fopen(filename, "w"); fclose(fp);
}


extern void slEncryptB(char *str, int key){
  int i = 0, str_int;

  while(str[i]){
      //Para los caracteres en minuscula
      if((int)str[i] > 96 && (int)str[i] < 123){
          str_int = (int)str[i] + key;
          while( str_int > 122 ){ str_int = 96 + ( str_int - 122); }
          str[i] = (char) str_int;
      }
      //Para los caracteres en mayuscula
      if((int)str[i] > 64 && (int)str[i] < 91){
          str_int = (int)str[i] + key;
          while( str_int > 90 ){ str_int = 64 + ( str_int - 90); }
          str[i] = (char) str_int;
      }
      //For spaces
      if((int)str[i] == 32) str[i] = '-';
      i++;
  }
}

/**
* @brief Get a String with fgets, and remove \n
* @param Nothing
* @return Nothing
*/
extern void slGetString(char *string, int max_char){
  fgets(string, max_char, stdin);
  strtok(string, "\n");
}

extern void slPrintFile(char *filename, char *before, FILE *dest, int remove_line_break){
  char line[512];
  FILE *fp = fopen(filename, "r");

  if(fp != NULL){
    while (!feof(fp)) {
      fgets(line, 512, fp);
      if(!feof(fp)){
        if(remove_line_break) strtok(line, "\n");
        fprintf(dest, "%s%s", before, line);
      }
    }
    fclose(fp);
  }
  else printf("%s no existe", filename);
}


extern void slToContinue(char *text){
    char any[256], message[256];
    strcpy(message, strcmp(text,"") == 0 ? "\n" : text);
    printf("%sPresiona enter para continuar.\n", message);
    slGetString(any, 256);
    slClearWindow();
}

extern void slToLwrStr(char *str){
  int i = 0;
  while(str[i] != '\0'){ str[i] = tolower(str[i]); i++; }
}

extern void slToUprStr(char *str){
  int i = 0;
  while(str[i] != '\0'){ str[i] = toupper(str[i]); i++; }
}

#endif // SUPPORTLIBRARY_H_INCLUDED
