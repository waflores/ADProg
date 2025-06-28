#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setWindowTitle("Active Directory New User Import Utility"); // Program title

  // TODO:(@waflores) 2025-06-27: figure out a way to iteratively set this up
  mainLayout_.addWidget(&programTitle_);
  mainLayout_.addWidget(&addUser_);
  mainLayout_.addWidget(&editUser_);
  mainLayout_.addWidget(&delUsers_);
  mainLayout_.addWidget(&loadFile_);
  mainLayout_.addWidget(&exportFile_);
  mainLayout_.addWidget(&importUsers_);
  mainLayout_.addWidget(&options_);
  setLayout(&mainLayout_);

  for (auto child : findChildren<QPushButton *>()) {
    connect(child, &QPushButton::clicked, this, &MainWindow::doMessage);
  }
}

void MainWindow::doMessage([[maybe_unused]] bool something) {
  QMessageBox::information(this, "AHHHHH", "A button was pressed!");
}