#ifndef GLVIEW_H
#define GLVIEW_H
#define GL_SILENCE_DEPRECATION
#include <QOpenGLWidget>
#include <QWidget>
#include <QMovie>
#include <QtGui>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../CPart/s21_Viewer.h"
#ifdef __cplusplus
}
#endif

class glView : public QOpenGLWidget
{
  Q_OBJECT
 private:

 public:
  Model* model = NULL;
  int kProjection;
  int strip, line_width;
  int depth;
  int point_setup, point_size;
  float screen_red, screen_blue, screen_green;
  float line_red, line_green, line_blue;
  float point_red, point_green, point_blue;

  glView(QWidget *parent = Q_NULLPTR);
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  // void updateGL();
  void PaintModel(Model* objModel);
  void WriteSettings();
  void ReadSettings();
};

#endif // GLVIEW_H
