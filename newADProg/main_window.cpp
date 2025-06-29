#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setWindowTitle("Active Directory New User Import Utility"); // Program title

  // TODO:(@waflores) 2025-06-27: figure out a way to iteratively set this up
  mainLayout_.addWidget(&programTitle_);
  mainLayout_.addWidget(&addUser_);
  mainButtonGroup_.addButton(&addUser_);
  mainLayout_.addWidget(&editUser_);
  mainButtonGroup_.addButton(&editUser_);
  mainLayout_.addWidget(&delUsers_);
  mainButtonGroup_.addButton(&delUsers_);
  mainLayout_.addWidget(&loadFile_);
  mainButtonGroup_.addButton(&loadFile_);
  mainLayout_.addWidget(&exportFile_);
  mainButtonGroup_.addButton(&exportFile_);
  mainLayout_.addWidget(&importUsers_);
  mainButtonGroup_.addButton(&importUsers_);
  mainLayout_.addWidget(&options_);
  mainButtonGroup_.addButton(&options_);

  setLayout(&mainLayout_);

  connect(&mainButtonGroup_,
          reinterpret_cast<void (QButtonGroup::*)(QPushButton *)>(
              &QButtonGroup::buttonClicked),
          this, &MainWindow::buttonMessage);

  /*
  for (auto child : findChildren<QPushButton *>()) {
  connect(child, &QPushButton::clicked, this, &MainWindow::doMessage);
  }
  */
}

void MainWindow::doMessage([[maybe_unused]] bool something) {
  // TODO:(@waflores) 2025-06-28: figure out who called us
  QMessageBox::information(this, "AHHHHH", "A button was pressed!");
}

void MainWindow::buttonMessage(QPushButton *button) {
  QMessageBox::information(this, "AHHHHH", button->text());
}