#include "s21_Viewer.h"

int main() {
  // printf("Error code: %d\n", ParserFile("../cube.obj"));
  Model model;
  int err = s21_InitModel(&model);
  printf("Error Init code: %d\n", err);
  //  int err =0 ;
  err = s21_ParserFile("test_obj/cube.obj", &model);
  printf("Error code: %d\n", err);
  // printf("%d \n", model.facets->data[0]->count_vertex);
  //   for (size_t i = 0; i < model.vertex->count; i++) {
  //     printf("До X %f\n", model.vertex->arr[i][0]);
  //     printf("До Y %f\n", model.vertex->arr[i][1]);
  //   }
  //         // rotation(model.vertex, M_PI/3, 3);
  //         // rotation(model.vertex, M_PI/3, 3);
  //         // rotation(model.vertex, M_PI/3, 3);
  //         rotation(model.vertex, M_PI, 3);

  //   for (size_t i = 0; i < model.vertex->count; i++) {
  //     printf("После X %f\n", model.vertex->arr[i][0]);
  //     printf("После Y %f\n", model.vertex->arr[i][1]);
  //   }

  err = s21_FreeModel(&model, err);
  printf("Error Free code: %d\n", err);
  return 0;
}