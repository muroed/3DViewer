#ifndef SRC_S21_VIEWER_H_
#define SRC_S21_VIEWER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include "telegrambot/bot.h"

#define NUMBER_POINT 3

//для каждой строчки в полигоне
typedef struct polygon_t {
  unsigned int count_vertex; 
  unsigned int *arr;
} polygon_t;

//vertex
typedef struct ArrayDouble{
  double** arr;
  size_t count;
} ArrayDouble;

//polygon
typedef struct ArrayInt{ 
  size_t count;
  polygon_t **data; //массив структур
} ArrayInt;


//Main struct
typedef struct Model{
  ArrayDouble *vertex;
  ArrayInt *facets;
} Model;

int s21_ParserFile(char* fileName, Model* model);
ArrayDouble* ParserVLine(char* line, ArrayDouble* vector);
ArrayInt* ParserFLine(char* line, ArrayInt* plane);

int s21_InitModel(Model* model);
int s21_FreeModel(Model* model, int err);
int InitStruct(Model* model);
int InitFacetsData(ArrayInt* facets, int fLine);
int CountFacetsInLine(char* line);

//for afins
// void move_obj_by_ox(ArrayDouble *A, double a);
// void move_obj_by_oy(ArrayDouble *A, double a);
// void move_obj_by_oz(ArrayDouble *A, double a);
void move_obj(ArrayDouble *A, double a, int axis);

void rotation(ArrayDouble *A, double angle, int axis); //axis 1 - x; 2 - y; 3 - z
void scaling(ArrayDouble *A, double a);

#endif  //  SRC_S21_VIEWER_H_
