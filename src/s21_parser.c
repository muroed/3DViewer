#include "s21_Viewer.h"


int Parser(char* fileName) {
  int err = 0;
  FILE* fp = NULL;
  // double* vector = NULL; 
  double** arrV = (double**)malloc(sizeof(double*) * 3 );
  int** arrF = (int**)malloc(sizeof(int*) * 3 );
  int countV = 0, countF = 0;
  int arrVSize = 2, arrFSize = 2;

  if ((fp = fopen(fileName, "r")) != NULL) {
    for (char line[256] = {'\0'}; !feof(fp); fgets(line, 256, fp)) {
      char c = 1;
      if (line[0] == 'v' && line[1] == ' ') {

        if (countV == pow(2, arrVSize)) {
          arrVSize++;
          printf("Realloced %lf\n", pow(2, arrVSize));
          arrV = (double**)realloc(arrV, sizeof(double*) * pow(2, arrVSize));
        }

        arrV[countV] = (double*)malloc(sizeof(double) * NUMBER_POINT);
        sscanf(line, "%c %lf %lf %lf", &c, &(arrV[countV][0]), &(arrV[countV][1]), &(arrV[countV][2]));

        printf("Vector[%d]: %lf %lf %lf\n", countV, arrV[countV][0], arrV[countV][1], arrV[countV][2]);

        countV++;



      } else if (line[0] == 'f' && line[1] == ' ') {

        if (countF == pow(2, arrFSize)) {
          arrFSize++;
          printf("Realloced %lf\n", pow(2, arrFSize));
          arrF = (double**)realloc(arrF, sizeof(double*) * pow(2, arrFSize));
        }

        arrF[countF] = (double*)malloc(sizeof(double) * NUMBER_POINT);
        sscanf(line, "%c %lf %lf %lf", &c, &(arrF[countF][0]), &(arrF[countF][1]), &(arrF[countF][2]));

        printf("Vector[%d]: %lf %lf %lf\n", countF, arrF[countF][0], arrF[countF][1], arrF[countF][2]);
        
        countF++;

        // printf("F line\n");
      } else {
        // printf("Another string: %s \n", line);
      }
    }
    fclose(fp);
  } else {
    //  файл не открылся или не существует
    err = 1;
  }
  for (int i = 0; i <= pow(2, arrVSize); i++) {
    free(arrV[i]);
  }
  free(arrV);
  for (int i = 0; i <= pow(2, arrFSize); i++) {
    free(arrF[i]);
  }
  free(arrF);
  return err;
}

int main() {
  printf("Error code: %d\n", Parser("../cube.obj"));
  printf("Error code: %d\n", Parser("../lamp.obj"));
  return 0;
}