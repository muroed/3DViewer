#include "./glview.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent)
{
  ReadSettings();
}
void glView::initializeGL() {
  glEnable(GL_DEPTH_TEST);
}
void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void glView::paintGL() {
  float ratio = width() / height();
  double x = width(), y = height(), z = 20;
  glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
  glLoadIdentity();
  if (kProjection == 0)
    if (x > y)
      glOrtho(-x * ratio, x * ratio, -y, y, -100*depth/10, 100*depth/10);
    else 
      glOrtho(-x, x, -y* ratio, y* ratio, -100*depth/10, 100*depth/10);
  else
    glFrustum(-x * ratio, x * ratio, -y, y,  0, 100*depth/10);
  glClearColor((float)(screen_red/255), (float)(screen_green/255), (float)(screen_blue/255), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (model != NULL && model->vertex->arr != NULL) {
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
      WriteSettings();
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

void glView::ReadSettings() {
  QSettings settings("settings_widget.conf", QSettings::IniFormat );
  settings.beginGroup("Colors");
  screen_red = settings.value("screen_red", 1).toFloat();
  screen_green = settings.value("screen_green", 1).toFloat();
  screen_blue = settings.value("screen_blue", 1).toFloat();
  line_red = settings.value("line_red", 255).toFloat();
  line_green = settings.value("line_green", 255).toFloat();
  line_blue = settings.value("line_blue", 0).toFloat();
  point_red = settings.value("point_red", 0).toFloat();
  point_green = settings.value("point_green", 0).toFloat();
  point_blue = settings.value("point_blue", 0).toFloat();
  point_setup = settings.value("point_setup", 0).toInt();
  point_size = settings.value("point_size", 1).toInt();
  strip = settings.value("line_strip", 0).toInt();
  line_width = settings.value("line_setup", 0).toInt();
  kProjection = settings.value("projection", 0).toInt();
  depth = settings.value("depth", 100000).toInt();
  settings.endGroup();
}

void glView::WriteSettings() {
  QSettings settings("settings_widget.conf", QSettings::IniFormat );
  settings.beginGroup("Colors");
  settings.setValue("screen_red", screen_red);
  settings.setValue("screen_green", screen_green);
  settings.setValue("screen_blue", screen_blue);
  settings.setValue("line_red", line_red);
  settings.setValue("line_green", line_green);
  settings.setValue("line_blue", line_blue);
  settings.setValue("point_red", point_red);
  settings.setValue("point_green", point_green);
  settings.setValue("point_blue", point_blue);
  settings.setValue("point_setup", point_setup);
  settings.setValue("point_size", point_size);
  settings.setValue("line_strip", strip);
  settings.setValue("line_setup", line_width);
  settings.setValue("projection", kProjection);
  settings.setValue("depth", depth);
  settings.endGroup();
}