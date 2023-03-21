#include "glview.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent)
{
  sizeWidht = width();
  sizeHeight = height();
}
void glView::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  kProjection = 0;
  strip = 0;
  depth = 1;
//  screen_red = 95;
//  screen_green = 83;
//  screen_blue = 163;
  line_width = 1;
}
void glView::resizeGL(int w, int h) {
  float ratio = width() / height();
 w = width();
 h = height();
  double x = w, y = h, z = 20;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (kProjection == 0)
    if (x > y)
      glOrtho(-x * ratio, x * ratio, -y, y, -100*depth/10, 100*depth/10);
    else 
      glOrtho(-x, x, -y* ratio, y* ratio, -100*depth/10, 100*depth/10);
  else
    glFrustum(-x * ratio, x * ratio, -y, y,  0, 100*depth/10);
  glRotated(-45, 0, 1, 0);
  glRotated(10, 1, 0, 0);
}

void glView::paintGL() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        glClearColor((float)(screen_red/255), (float)(screen_green/255), (float)(screen_blue/255), 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (model != NULL && model->vertex->arr != NULL) {
//    resizeGL(sizeWidht, sizeHeight);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3f(line_red/255, line_green/255, line_blue/255);
    glVertexPointer(3, GL_DOUBLE, 0, model->vertex->arr[0]);

    glLineWidth(line_width);

    if (strip == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00F0);
    }
    for (unsigned long i = 0; i < model->facets->count && strip != 2; i++) {
        glDrawElements(GL_LINE_LOOP,
                            model->facets->data[i]->count_vertex,
                            GL_UNSIGNED_INT, model->facets->data[i]->arr);
    }

    if (strip == 1) glDisable(GL_LINE_STIPPLE);

    if (point_setup) {
      glPointSize(point_size);
      glColor3f(point_red, point_green, point_blue);
      if (point_setup == 1) glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, model->vertex->count);
      if (point_setup == 1) glDisable(GL_POINT_SMOOTH);
    }
      glDisableClientState(GL_VERTEX_ARRAY);
      // OZ
//      glColor3f(0 ,0 ,1);
//      glBegin(GL_LINES);
//      glVertex3d(0, 0, 10);
//      glVertex3d(0, 0, -10);
//      glEnd();

//      // OY
//      glColor3f(0 ,1 ,0);
//      glBegin(GL_LINES);
//      glVertex3d(0, 10, 0);
//      glVertex3d(0, -10, 0);
//      glEnd();
//      // OX
//      glColor3f(1 ,0 ,0);
//      glBegin(GL_LINES);
//      glVertex3d(10, 0, 0);
//      glVertex3d(-10, 0, 0);
//      glEnd();
  }
}