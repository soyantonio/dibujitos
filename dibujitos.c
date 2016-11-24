/**
* @author Antonio Perez
* @brief (Ubuntu 16.04) Library for my own purposes
* @date  23 Nov 2016
* @file test.c
* @version 1.0.0
* @compilation_number 119
*/
#include "SupportLibrary.h"

void draw();
void drawNow(char command[128]);
void drawShow();
void initDrawings();
void learnDraw();
void learnDrawInsert(FILE *fp, char line[512], int max[1]);
void learnDrawSave(int end[1], FILE *temp_file);
void learnDrawShow(FILE *temp_file);
void menu(const char *const *options, const char *const *options_label, const char *label, char option[128]);

int main () {
 int compilation, end = 0;
 const char *options[] = {"A", "B", "C", NULL };
 const char *options_label[] = {"Enseniar a dibujar", "Dibujar", "Salir", NULL};
 const char *label = "Tu opcion: ";
 char option[128];
 FILE *compilation_number;
 initDrawings();
 //Update compilation number
 if(1){
  compilation_number = fopen("compilation_number.txt", "r");fscanf(compilation_number, "%i", &compilation);fclose(compilation_number);
  compilation += 1;compilation_number = fopen("compilation_number.txt", "w"); fprintf(compilation_number, "%i", compilation);fclose(compilation_number);
 }

 do {
   menu(options, options_label, label, option);
   if(!strcmp(options[0], option)){
    learnDraw();
   }
   else if(!strcmp(options[1], option)){
    draw();
   }
   else if(!strcmp(options[2], option)){
    end = 1;
   }
   else{
    slToContinue((char*)"Opcion no valida, code 0000. ");
   }
 }while(!end);

 puts("Fin del programa. Ten un buen dia (◠‿◠)\nTu voto ayudara que mi programador siga mejorandome");
 slToContinue((char*)"");
 return EXIT_SUCCESS;
}

void draw(){
  int end = 0;
  char command[128];
  slCreateFile((char*)"drawings/temp.txt");

  //Main program
  do {
    puts("¿Sabre dibujar? \\_( o .o)_/ \nPara salir, escribe en una nueva linea 111\nEscribe lo que quieras dibujar y da enter\n");
    //Print options to draw
    slPrintFile((char*)"drawings/drawings.txt", (char*)"Puedes utilizar d", stdout, 0);

    //Show the picture
    drawShow();

    //Start program
    printf("\nTu comando: ");
    slGetString(command, 128);

    if(!strcmp(command, "111")) end = 1;
    else drawNow(command);

    slClearWindow();
  }while(!end);
}

void drawNow(char command[128]){
  FILE *drawing_file;
  FILE *fp;
  FILE *fp_temp;
  int length[2];
  int how[2];
  char line[512];
  char line_temp[512];
  char second_command[128];
  char route[256] = "drawings/";

  slEncryptB(command, 0); strcat(route, command); strcat(route, ".txt");
  drawing_file = fopen(route, "r");
  if(drawing_file != NULL){
    //Get second command
    fp = fopen("drawings/temp.txt", "r");
    fp_temp = fopen("drawings/temp_temp.txt", "w");
    not_option: printf("Donde imprimir? izquierda[A], derecha[D]: ");
    slGetString(second_command, 128);
    slToUprStr(second_command);
    //Print right
    if(!strcmp(second_command, "D")){
      how[0] = 0; how[1] = 0; length[0] = 0; length[1] = 0;
      while (!feof(fp) || !feof(drawing_file)) {
        fgets(line, 512, fp); fgets(line_temp, 512, drawing_file);

        if(feof(fp)){
          strcpy(line, "");
          for(how[0] = 0; how[0] < length[0]; how[0]++){
            strcat(line, " ");
          }
        }
        else{
          strtok(line, "\n");
          length[0] = strlen(line);
        }

        if(feof(drawing_file)){
          strcpy(line_temp, "");
          for(how[1] = 0; how[1] < length[1]; how[1]++){
            strcat(line_temp, " ");
          }
          strcat(line_temp, "\n");
        }else{
          length[1] = strlen(line_temp) - 1;
        }
        fprintf(fp_temp, "%s%s", line, line_temp);
      }
    }
    //Print left
    else if(!strcmp(second_command, "A")){
      how[0] = 0; how[1] = 0; length[0] = 0; length[1] = 0;
      while (!feof(fp) || !feof(drawing_file)) {
        fgets(line, 512, fp); fgets(line_temp, 512, drawing_file);

        if(feof(fp)){
          strcpy(line, "");
          for(how[0] = 0; how[0] < length[0]; how[0]++){
            strcat(line, " ");
          }
          strcat(line, "\n");
        }
        else{
          length[0] = strlen(line) - 1;
        }

        if(feof(drawing_file)){
          strcpy(line_temp, "");
          for(how[1] = 0; how[1] < length[1]; how[1]++){
            strcat(line_temp, " ");
          }
        }else{
          strtok(line_temp, "\n");
          length[1] = strlen(line_temp);
        }

        fprintf(fp_temp, "%s%s", line_temp, line);
      }
    }
    else{
      goto not_option;
    }

    fclose(fp_temp);
    fclose(fp);
    fclose(drawing_file);

    //Print in temp.txt
    fp = fopen("drawings/temp.txt", "w");
    slPrintFile((char*)"drawings/temp_temp.txt", (char*)"", fp, 0);
    fclose(fp);
  }
}

void drawShow(){
  puts("\nTu dibujo ...\n");
  slPrintFile((char*)"drawings/temp.txt", (char*)"", stdout, 0);
}

void initDrawings(){
  FILE *database;
  char database_name[] = "drawings/drawings.txt";
  no_base: database = fopen(database_name, "r");
  if(database == NULL){
    slCreateFile(database_name);
    goto no_base;
  }
  fclose(database);
}

void learnDraw(){
  int end[1] = {0};
  int max[1] = {0};
  FILE *temp_file = fopen("drawings/temp.txt", "w");
  char line[512];

  puts("Estoy aprendiendo a dibujar.\nTen paciencia, por favor.\nPues a mi programador le dio flojera hacerme mas inteligente (¬_¬)\n\nPara guardar dibujo y salir, escribe en una nueva linea 123\nPara ver dibujo, escribe en una nueva linea 321\nPara salir sin guardar dibujo, escribe en una nueva linea 111\nDeja fluir tu imaginacion U^-^U\n");

  do {
    slGetString(line, 512);
    if(!strcmp(line, "\n")) strcpy(line, "");
    //Save drawing
    if(!strcmp(line, "123")){
      learnDrawSave(end, temp_file);
    }
    //Show drawings
    else if(!strcmp(line, "321")){
      learnDrawShow(temp_file);
    }
    //Exit
    else if(!strcmp(line, "111")){
      printf("Has salido sin guardar. ");
      fclose(temp_file);
      end[0] = 1;
    }
    //Insert drawing_file
    else{
      learnDrawInsert(temp_file, line, max);
    }
  } while(!end[0]);

  slToContinue((char*)"");
}

void learnDrawInsert(FILE *fp, char line[512], int max[1]){
  FILE *temp_fp;
  int length = strlen(line);
  char temp_line[512];
  char spaces[512];

  fprintf(fp, "%s\n", line);
  fclose(fp);
  if(max[0] < length) max[0] = length;
  fp = fopen("drawings/temp.txt", "r");
  temp_fp = fopen("drawings/temp_temp.txt", "w");//Cerrrar
  while (!feof(fp)) {
    strcpy(spaces, "");
    fgets(temp_line, 512, fp);
    if(!feof(fp)){
      strtok(temp_line, "\n");
      if(!strcmp(temp_line, "\n")) strcpy(temp_line, "");
      length = strlen(temp_line);
      while (max[0] > length) {
        strcat(spaces, " ");
        length++;
      }
      fprintf(temp_fp, "%s%s\n", temp_line, spaces);
    }
  }
  fclose(temp_fp);
  fclose(fp);

  fp = fopen("drawings/temp.txt", "a");
}

void learnDrawSave(int end[1], FILE *temp_file){
  FILE *drawing_file;
  char route[] = "drawings/d";
  char name[128];
  char name_temp[128];

  fclose(temp_file);
  printf("Nombre de tu dibujo/forma: ");
  slGetString(name, 128); slToUprStr(name);slEncryptB(name, 0); strcpy(name_temp, name); strcat(route, name); strcat(route, ".txt");

  drawing_file = fopen(route, "w");
  slPrintFile((char*)"drawings/temp_temp.txt", (char*)"", drawing_file, 0);
  slAddInFile((char*)"drawings/drawings.txt", (char*)"", name_temp, (char*)"", 1);

  fclose(drawing_file);
  end[0] = 1;
  printf("Se ha guardado tu figura llamada %s", name_temp);
}

void learnDrawShow(FILE *temp_file){
  fclose(temp_file);
  slPrintFile((char*)"drawings/temp.txt", (char*)"", stdout, 0);
  temp_file = fopen("drawings/temp.txt", "a");
}

void menu(const char *const *options, const char *const *options_label, const char *label, char option[128]){
  int i;

  for (i = 0; options[i] != NULL; i++) { printf("[%s] %s\n", options[i], options_label[i]); }
  printf("%s", label);

  slGetString(option, 128);
  slToUprStr(option);
  slClearWindow();
}
