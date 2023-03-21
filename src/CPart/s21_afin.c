#include "s21_Viewer.h"

/*
axis:
0 - ox
1 - oy
2 - oz
*/

void move_obj(ArrayDouble *A, double a, int axis) {
  if (A != NULL)
    if (A->arr != NULL)
      for (size_t i = 0; i < A->count; i++) A->arr[i][axis] += a;
}

void rotation(ArrayDouble *A, double angle, int axis) {
  if (A != NULL)
    for (size_t i = 0; i < A->count; i++) {
      if (axis == 1) {  // for ox
        double temp_y = A->arr[i][1];
        double temp_z = A->arr[i][2];
        A->arr[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
        A->arr[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
      } else if (axis == 2) {  // for oy
        double temp_x = A->arr[i][0];
        double temp_z = A->arr[i][2];
        A->arr[i][0] = temp_x * cos(angle) + temp_z * sin(angle);
        A->arr[i][2] = temp_z * cos(angle) - temp_x * sin(angle);
      } else if (axis == 3) {  // for oz
        double temp_x = A->arr[i][0];
        double temp_y = A->arr[i][1];
        A->arr[i][0] = temp_x * cos(angle) - temp_y * sin(angle);
        A->arr[i][1] = temp_y * cos(angle) + temp_x * sin(angle);
      }
    }
}

void scaling(ArrayDouble *A, double a) {
  if (a != 0 && A != NULL)
    if (A->arr != NULL)
      for (size_t i = 0; i < A->count; i++) {
        A->arr[i][0] *= a;
        A->arr[i][1] *= a;
        A->arr[i][2] *= a;
      }
}
