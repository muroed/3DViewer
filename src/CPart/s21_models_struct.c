#include "s21_Viewer.h"
int s21_InitModel(Model* model) {
  int err = 0;
  if ((model->facets = (ArrayInt*)malloc(sizeof(ArrayInt) + 1)) == NULL) {
    err = 1;
  }
  model->facets->count = 0;
  model->facets->data = NULL;

  if ((model->vertex = (ArrayDouble*)malloc(sizeof(ArrayDouble) + 1)) == NULL &&
      err == 0) {
    err = 1;
  }
  model->vertex->count = 0;
  model->vertex->arr = NULL;
  return err;
}

int InitStruct(Model* model) {
  int err = 0;
  double* ptr_arr = NULL;
  if ((ptr_arr = (double*)malloc(
           sizeof(double) * NUMBER_POINT * (model->vertex->count) + 1)) ==
      NULL) {
    err = 2;
  }
  if ((model->vertex->arr = (double**)malloc(
           sizeof(double*) * model->vertex->count + 1)) == NULL) {
    err = 3;
  }
  for (size_t i = 0; i < model->vertex->count; i += 1) {
    model->vertex->arr[i] = &(ptr_arr[i * NUMBER_POINT]);
  }
  if ((model->facets->data = (polygon_t**)malloc(
           sizeof(polygon_t*) * model->facets->count + 1)) == NULL) {
    err = 4;
  }
  for (size_t i = 0; i < model->facets->count; i++) {
    if ((model->facets->data[i] = (polygon_t*)malloc(sizeof(polygon_t) + 1)) ==
        NULL) {
      err = 5;
    } else {
      model->facets->data[i]->count_vertex = 0;
      model->facets->data[i]->arr = NULL;
    }
  }
  return err;
}

int InitFacetsData(ArrayInt* facets, int fLine) {
  int err = 0;
  if ((facets->data[fLine]->arr = (unsigned int*)malloc(
           sizeof(unsigned int) * facets->data[fLine]->count_vertex)) == NULL) {
    err = 1;
  }
  return err;
}

int s21_FreeModel(Model* model, int err) {
  if (err != -1) {
    if (model->vertex->arr != NULL && err == 0) {
      free(model->vertex->arr[0]);
      free(model->vertex->arr);
    }
    free(model->vertex);

    if (model->facets->data != NULL && err == 0) {
      for (size_t j = 0; j < model->facets->count; j++) {
        free(model->facets->data[j]->arr);
      }

      for (size_t j = 0; j < model->facets->count; j++) {
        free(model->facets->data[j]);
      }

      free(model->facets->data);
    }
    free(model->facets);
  }
  return err;
}