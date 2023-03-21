#include "s21_Viewer.h"

int vLine = 0, fLine = 0;

int s21_ParserFile(char* fileName, Model* model) {
  int err = 0;
  vLine = 0, fLine = 0;
  FILE* fp = NULL;
  if ((fp = fopen(fileName, "r")) != NULL) {
    // SendMessage("Open file succes ", fileName);
    for (char line[256] = {'\0'}; !feof(fp); fgets(line, 256, fp)) {
      if (line[0] == 'v' && line[1] == ' ') {
        model->vertex->count += 1;
      } else if (line[0] == 'f' && line[1] == ' ') {
        model->facets->count += 1;
      }
    }

    err = InitStruct(model);

    fseek(fp, SEEK_SET, 0);

    for (char line[256] = {'\0'}; !feof(fp) && err == 0; fgets(line, 256, fp)) {
      if (line[0] == 'v' && line[1] == ' ') {
        ParserVLine(line, model->vertex);
        vLine++;
      } else if (line[0] == 'f' && line[1] == ' ') {
        ParserFLine(line, model->facets);
        fLine++;
      }
    }
    fclose(fp);

  } else {
    //  файл не открылся или не существует
    err = 1;
  }

  return err;
}

ArrayDouble* ParserVLine(char* line, ArrayDouble* vertex) {
  char c = 1;
  if (vertex->arr[vLine] != NULL) {
    sscanf(line, "%c %lf %lf %lf", &c, &(vertex->arr[vLine][0]),
           &(vertex->arr[vLine][1]), &(vertex->arr[vLine][2]));
  }

  return vertex;
}

ArrayInt* ParserFLine(char* line, ArrayInt* facets) {
  int i = 0;
  char line_copy[256] = {'\0'};
  strcpy(line_copy, line);

  if (/*strcmp(ptr, "f") == 0*/ line[0] == 'f' && line[1] == ' ') {
    facets->data[fLine]->count_vertex = CountFacetsInLine(line);
    // printf("facets->data[%d]->countVertex = %d\n", fLine,
    // facets->data[fLine]->count_vertex);
    InitFacetsData(facets, fLine);

    char* ptr = strtok(line_copy, " ");
    char* string_number = "0123456789.";
    while ((ptr = strtok(NULL, " ")) != NULL &&
           (unsigned int)i < facets->data[fLine]->count_vertex) {
      char buffer[256] = {'\0'};
      for (; *ptr != '/' && *ptr; ptr++) {
        if (strchr(string_number, *ptr)) {
          int j = 0;
          for (; *ptr && strchr(string_number, *ptr); ptr++) {
            buffer[j] = *ptr;
            j++;
          }
          ptr--;
        }
      }
      facets->data[fLine]->arr[i] = abs(atoi(buffer)) - 1;
      // printf("[%d] = %d\n", i , facets->data[fLine]->arr[i]);
      i++;
    }
  }
  return facets;
}

int CountFacetsInLine(char* line) {
  int sum = 0;
  // printf("%s\n", line);
  // char* ptr = strtok(line, " ");
  // while ((ptr = strtok(NULL, " ")) != NULL) {
  //   sum++;
  // }
  char* ptr = NULL;
  while ((ptr = strchr(line, ' ')) != NULL) {
    if (ptr != NULL && *(ptr + 1) > 31 && *(ptr + 1) != ' ') {
      sum++;
    }
    line = ptr + 1;
  }

  return sum;
}