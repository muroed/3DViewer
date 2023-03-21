#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtGui>

//QString fileName = Q_NULLPTR;
//Model objModel;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    err = -1;
    moveX = 0;
    moveY = 0;
    moveZ = 0;
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    arg_scaling = 10;
    arg_scale = 1;

  ui->setupUi(this);
//   ui->oglView->resizeGL(ui->oglView->width(),ui->oglView->height());
  ReadSettings();
  ui->oglView->update();
  hiden = false, is_recording = false;
  time = 0.0;
  record_time = new QTimer(this);
  connect(record_time, &QTimer::timeout, this, &MainWindow::recording);
  s21_InitModel(&objModel);
}

MainWindow::~MainWindow()
{
  WriteSettings();
  s21_FreeModel(&objModel, err);
  delete ui;
}

void MainWindow::ReadSettings() {
    QSettings settings("settings.conf", QSettings::IniFormat );
    settings.beginGroup("Colors");
    ui->oglView->screen_red = settings.value("screen_red", 1).toFloat();
    ui->oglView->screen_green = settings.value("screen_green", 1).toFloat();
    ui->oglView->screen_blue = settings.value("screen_blue", 1).toFloat();
    ui->oglView->line_red = settings.value("line_red", 255).toFloat();
    ui->oglView->line_green = settings.value("line_green", 255).toFloat();
    ui->oglView->line_blue = settings.value("line_blue", 0).toFloat();
    ui->oglView->point_red = settings.value("point_red", 0).toFloat();
    ui->oglView->point_green = settings.value("point_green", 0).toFloat();
    ui->oglView->point_blue = settings.value("point_blue", 0).toFloat();
    ui->oglView->point_setup = settings.value("point_setup", 0).toInt();
    ui->oglView->point_size = settings.value("point_size", 1).toInt();
    ui->oglView->strip = settings.value("line_strip", 0).toInt();
    ui->oglView->line_width = settings.value("line_setup", 0).toInt();
    ui->oglView->kProjection = settings.value("projection", 0).toInt();
    ui->oglView->depth = settings.value("depth", 100000).toInt();
    settings.endGroup();
}

void MainWindow::WriteSettings() {
    QSettings settings("settings.conf", QSettings::IniFormat );
    settings.beginGroup("Colors");
    settings.setValue("screen_red", ui->oglView->screen_red);
    settings.setValue("screen_green", ui->oglView->screen_green);
    settings.setValue("screen_blue", ui->oglView->screen_blue);
    settings.setValue("line_red", ui->oglView->line_red);
    settings.setValue("line_green", ui->oglView->line_green);
    settings.setValue("line_blue", ui->oglView->line_blue);
    settings.setValue("point_red", ui->oglView->point_red);
    settings.setValue("point_green", ui->oglView->point_green);
    settings.setValue("point_blue", ui->oglView->point_blue);
    settings.setValue("point_setup", ui->oglView->point_setup);
    settings.setValue("point_size", ui->oglView->point_size);
    settings.setValue("line_strip", ui->oglView->strip);
    settings.setValue("line_setup", ui->oglView->line_width);
    settings.setValue("projection", ui->oglView->kProjection);
    settings.setValue("depth", ui->oglView->depth);
    settings.endGroup();
}

void MainWindow::InitFile() {
    s21_FreeModel(&objModel, err);
  err = s21_InitModel(&objModel);
  rotationX = 0;
  rotationY = 0;
  rotationZ = 0;
  moveX = 0;
  moveY = 0;
  moveZ = 0;
  arg_scaling = 1;
  arg_scale = 1;
  ui->unscaleBox->setValue(0);
  ui->for_move_on_ox->setValue(0);
  ui->for_move_on_oy->setValue(0);
  ui->for_move_on_oz->setValue(0);
  ui->for_ox->setValue(0);
  ui->for_oy->setValue(0);
  ui->for_oz->setValue(0);
  ui->for_ox_rotations_ScrollBar->setValue(0);
  ui->for_oy_rotations_ScrollBar->setValue(0);
  ui->for_oy_rotations_ScrollBar->setValue(0);
  ui->for_rotation_x->setValue(0);
  ui->for_rotation_y->setValue(0);
  ui->for_rotation_z->setValue(0);
}


void MainWindow::on_btnChangeFile_clicked()
{
    InitFile();
  
  if (err == 0) {
    fileName = QFileDialog::getOpenFileName(this,
                              QString::fromUtf8("Открыть файл"),
                              QDir::homePath(),
                              "Object File(*.obj)");
//  fileName = "/Users/nazeebod/21/C8_3DViewer_v1.0-0/src/test_obj/lamp.obj";
    char filename_char[1024];
    err = s21_ParserFile(fileName.toLocal8Bit().data(), &objModel);
  }
  ui->statusbar->showMessage("Parsing error: " + QString::number(err), 0);
  if (err == 0) {
    ui->oglView->model = &objModel;
    ui->oglView->update();
    ui->statusbar->showMessage("File: " + QFileInfo(fileName).fileName() + "(Vertex: " + QString::number(objModel.vertex->count) + " / Facets: " + QString::number(objModel.facets->count) + ")");
  }
}


void MainWindow::on_for_oz_rotations_ScrollBar_sliderMoved(int position)
{
    ui->for_rotation_z->setValue((double)position);

    set_rotation(position, 3);
}


void MainWindow::on_for_rotation_z_valueChanged(double arg1)
{
    ui->for_oz_rotations_ScrollBar->setValue(arg1);
    set_rotation(arg1, 3);
}

void MainWindow::set_rotation(double arg1, int axis) {
    if (axis == 1) {
        rotation(objModel.vertex, rotationX - M_PI / 180 * arg1, axis);
        rotationX = M_PI / 180 * arg1;
    } else if (axis == 2) {
        rotation(objModel.vertex, rotationY - M_PI / 180 * arg1, axis);
        rotationY = M_PI / 180 * arg1;
    } else if (axis == 3) {
        rotation(objModel.vertex, rotationZ - M_PI / 180 * arg1, axis);
        rotationZ = M_PI / 180 * arg1;
    } else {
//        printf("Error axis");
    }

    ui->oglView->update();
}


void MainWindow::on_for_ox_rotations_ScrollBar_sliderMoved(int position)
{
    ui->for_rotation_x->setValue((double)position);

    set_rotation(position, 1);
}


void MainWindow::on_for_rotation_x_valueChanged(double arg1)
{
    ui->for_ox_rotations_ScrollBar->setValue(arg1);
    set_rotation(arg1, 1);
}

void MainWindow::on_for_oy_rotations_ScrollBar_sliderMoved(int position)
{
    ui->for_rotation_y->setValue((double)position);
    set_rotation(position, 2);
}


void MainWindow::on_for_rotation_y_valueChanged(double arg1)
{
    ui->for_oy_rotations_ScrollBar->setValue(arg1);
    set_rotation(arg1, 2);
}



void MainWindow::set_moved(double arg1, int axis) {
    if (axis == 0) {
        move_obj(objModel.vertex, moveX - arg1, axis);
        moveX = arg1;
    } else if (axis == 1) {
        move_obj(objModel.vertex, moveY - arg1, axis);
        moveY = arg1;
    } else if (axis == 2) {
        move_obj(objModel.vertex, moveZ - arg1, axis);
        moveZ = arg1;
    }
    ui->oglView->update();

}

void MainWindow::on_for_move_on_ox_sliderMoved(int position)
{
    ui->for_ox->setValue((double)position);

    set_moved(position, 0);

}


void MainWindow::on_for_ox_valueChanged(double arg1)
{
    ui->for_move_on_ox->setValue(arg1);
    set_moved(arg1, 0);
}



void MainWindow::on_for_move_on_oy_sliderMoved(int position)
{
    ui->for_oy->setValue((double)position);
    set_moved(position, 1);

}


void MainWindow::on_for_oy_valueChanged(double arg1)
{
    ui->for_move_on_oy->setValue(arg1);
    set_moved(arg1, 1);
}


void MainWindow::on_for_move_on_oz_sliderMoved(int position)
{
    ui->for_oz->setValue((double)position);
    set_moved(position, 2);
}


void MainWindow::on_for_oz_valueChanged(double arg1)
{
    ui->for_move_on_oz->setValue(arg1);
    set_moved(arg1, 2);
}


void MainWindow::on_projection_comboBox_currentIndexChanged(int index)
{
    ui->oglView->kProjection = index;
//    ui->oglView->resizeGL(ui->oglView->width(), ui->oglView->height());
    ui->oglView->update();
}


void MainWindow::on_line_comboBox_currentIndexChanged(int index)
{
  ui->oglView->strip = index;
  ui->oglView->update();
}



void MainWindow::on_unscaleBox_valueChanged(int arg1)
{
    if (arg1 > 0) {
        scaling(objModel.vertex, arg_scaling / arg_scale * arg1);
        arg_scale = arg1;
    } else if (arg1 < 0) {
        scaling(objModel.vertex, arg_scaling / arg_scale * (-1) * 1./arg1);
        arg_scale = (-1) * 1./arg1;
    } else {
        scaling(objModel.vertex, arg_scaling / arg_scale);
        arg_scale = 1;
    }
//    scaling(ui->oglView->model->vertex, arg_scaling / arg_scale * arg1);
//    arg_scale = arg1;
    ui->oglView->update();
}


void MainWindow::on_hsb_RedColor_sliderMoved(int position)
{
    ui->colorwidget->screen_red = position;
    ui->colorwidget->update();
}


void MainWindow::on_hsb_GreenColor_sliderMoved(int position)
{
    ui->colorwidget->screen_green = position;
    ui->colorwidget->update();
}


void MainWindow::on_hsb_BlueColor_sliderMoved(int position)
{
    ui->colorwidget->screen_blue = position;
    ui->colorwidget->update();
}

void MainWindow::on_btn_pointColor_clicked()
{
    ui->oglView->point_red = ui->hsb_RedColor->value();
    ui->oglView->point_green = ui->hsb_GreenColor->value();
    ui->oglView->point_blue = ui->hsb_BlueColor->value();
    ui->oglView->update();
}


void MainWindow::on_btn_colorLine_clicked()
{
    ui->oglView->line_red = ui->hsb_RedColor->value();
    ui->oglView->line_green = ui->hsb_GreenColor->value();
    ui->oglView->line_blue = ui->hsb_BlueColor->value();
    ui->oglView->update();
}


void MainWindow::on_btn_colorBack_clicked()
{
    ui->oglView->screen_red = ui->hsb_RedColor->value();
    ui->oglView->screen_green = ui->hsb_GreenColor->value();
    ui->oglView->screen_blue = ui->hsb_BlueColor->value();
    ui->oglView->update();
}


void MainWindow::on_hsb_pointsize_sliderMoved(int position)
{
    ui->oglView->point_size = position;
    ui->oglView->update();
}


void MainWindow::on_sbx_lineWidth_valueChanged(int arg1)
{
    ui->oglView->line_width = arg1;
    ui->oglView->update();
    ui->hsb_lineWidth->setValue(arg1);
}


void MainWindow::on_hsb_lineWidth_sliderMoved(int position)
{
    ui->oglView->line_width = position;
    ui->oglView->update();
    ui->sbx_lineWidth->setValue(position);
}


void MainWindow::on_horizontalScrollBar_2_sliderMoved(int position)
{
    ui->oglView->depth = position;
    ui->oglView->resizeGL(ui->oglView->width(), ui->oglView->height());
    ui->oglView->update();
    depth = position;
}


void MainWindow::on_comboBox_activated(int index)
{
  ui->oglView->point_setup = index;
  if (!index) {
      ui->hsb_pointsize->setEnabled(false);
  } else {
      ui->hsb_pointsize->setEnabled(true);
      ui->oglView->point_size = ui->hsb_pointsize->value();
  }
  ui->oglView->update();
}


void MainWindow::on_projection_comboBox_activated(int index)
{
  ui->oglView->kProjection = index;
//    ui->oglView->resizeGL(ui->oglView->width(), ui->oglView->height());
  ui->oglView->update();
}

void MainWindow::saveImage(QString format) {
  QString str = QFileDialog::getSaveFileName(this, "Save file as",
                                             QDir::homePath(), format);
  if (str != "") ui->oglView->grabFramebuffer().save(str);
}


void MainWindow::on_actionJPEG_triggered() { saveImage("*.jpeg"); }

void MainWindow::on_actionBMP_triggered() { saveImage("*.bmp"); }

void MainWindow::on_actionGIF_triggered() {
  if (!is_recording) {
    is_recording = true;
    this->setStyleSheet("QMainWindow{ background-color: red;}");
    record_time->start(100);
  }
}

void MainWindow::recording() {
  if (is_recording && time <= 5.0) {
    GIF.push_back(ui->oglView->grab().toImage());
    time += 0.1;
  } else {
    saveGIF();
    record_time->stop();
  }
}

void MainWindow::saveGIF() {
  QString str = QFileDialog::getSaveFileName(
      this, tr("Save GIF"), QDir::homePath(), tr("GIF (*.gif)"));
  if (str != "") {
    QGifImage gif(QSize(640,480));

    gif.setDefaultTransparentColor(Qt::black);
    gif.setDefaultDelay(100);

    for (QVector<QImage>::Iterator frame = GIF.begin(); frame != GIF.end();
         frame++) {
      gif.addFrame(*frame);
    }

    gif.save(str);
    GIF.clear();
  }
  time = 0.0;
  is_recording = false;

  this->setStyleSheet("QMainWindow{ background-color: rgb(" +
                      QString::number(95) + ", " +
                      QString::number(63) + ", " +
                      QString::number(183) + ");}");
}
