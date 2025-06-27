#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  layout_.addWidget(&label_);
  layout_.addWidget(&lineEdit_);
  setLayout(&layout_);
  setWindowTitle(QApplication::translate("windowlayout", "Window layout"));
}