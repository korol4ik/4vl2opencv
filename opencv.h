#ifndef OPENCV_H
#define OPENCV_H

#endif // OPENCV_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#include <QtGui/QApplication>
#include "mainwindow.h"
void komiks(IplImage* img_in,IplImage* img_out);
int v4l2init();
