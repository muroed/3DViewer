#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include "../OGlWidget/glview.h"
#include "../GIFCreation/gifImage/qgifimage.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include <string.h>
#include "../CPart/s21_Viewer.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_btnChangeFile_clicked();

  void on_for_oz_rotations_ScrollBar_sliderMoved(int position);

  void on_for_rotation_z_valueChanged(double arg1);

   void set_rotation(double arg1, int axis);

   void set_moved(double arg1, int axis);

   void InitFile();
   void ReadSettings();
   void WriteSettings();

   void on_for_ox_rotations_ScrollBar_sliderMoved(int position);

   void on_for_rotation_x_valueChanged(double arg1);

   void on_for_oy_rotations_ScrollBar_sliderMoved(int position);

   void on_for_rotation_y_valueChanged(double arg1);

   void on_for_move_on_ox_sliderMoved(int position);

   void on_for_ox_valueChanged(double arg1);

   void on_for_move_on_oy_sliderMoved(int position);

   void on_for_oy_valueChanged(double arg1);

   void on_for_move_on_oz_sliderMoved(int position);

   void on_for_oz_valueChanged(double arg1);

   void on_projection_comboBox_currentIndexChanged(int index);

   void on_line_comboBox_currentIndexChanged(int index);

   void on_unscaleBox_valueChanged(int arg1);

   void on_hsb_RedColor_sliderMoved(int position);

   void on_hsb_GreenColor_sliderMoved(int position);

   void on_hsb_BlueColor_sliderMoved(int position);

   void on_btn_pointColor_clicked();

   void on_btn_colorLine_clicked();

   void on_btn_colorBack_clicked();

   void on_hsb_pointsize_sliderMoved(int position);

   void on_sbx_lineWidth_valueChanged(int arg1);

   void on_hsb_lineWidth_sliderMoved(int position);

   void on_horizontalScrollBar_2_sliderMoved(int position);

   void on_comboBox_activated(int index);

   void on_projection_comboBox_activated(int index);

   void saveImage(QString format);

   void on_actionJPEG_triggered();

   void on_actionBMP_triggered();

   void on_actionGIF_triggered();

   void saveGIF();
   void recording();
   
private:
  Ui::MainWindow *ui;
  QString fileName;
  int err;
  Model objModel;
  int depth;
  QSettings settings;
  double moveX, moveY, moveZ;
  double rotationX, rotationY, rotationZ;
  double arg_scaling, arg_scale;
  float time;
  bool hiden, is_recording;
  QTimer *record_time;
  QVector<QImage> GIF;

//  glView mView;
};

#endif // MAINWINDOW_H
