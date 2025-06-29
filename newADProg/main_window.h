/**
 * @file main_window.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_
#include <QButtonGroup>
#include <QtWidgets>

#include <iostream>

class MainWindow : public QWidget {
public:
  MainWindow(QWidget *parent = nullptr);
  void doMessage(bool);
  void buttonMessage(QAbstractButton *button);

private:
  QVersionNumber versionNumber_{2, 0, 0};

  QVBoxLayout mainLayout_{};
  QLabel programTitle_{"New User Import v" % versionNumber_.toString()};
  QButtonGroup mainButtonGroup_;
  QPushButton addUser_{"Add New User..."};
  QPushButton delUsers_{"Delete All Users"};
  QPushButton editUser_{"Edit Users..."};
  QPushButton exportFile_{"Export..."};
  QPushButton importUsers_{"Import to AD..."};
  QPushButton loadFile_{"Load..."};
  QPushButton options_{"Options..."};
  QVBoxLayout fileLayout_{};
  QVBoxLayout recordLayout_{};
  // EditUsers *edit_GUI;
  // AddUsers *add_GUI;
};

class AddUsers : public QWidget {
  Q_OBJECT
public:
  AddUsers(QWidget *parent = nullptr);
public slots:
  /* The child class's methods for the editing of attributes */
  void enableAdding();
  void disableAdding();
  void clearAddForm(bool warn = true);
  void submitAddForm();

private:
  QPushButton *clearForm;
  QPushButton *submitForm;
  QHBoxLayout *submitLayout;
};

#endif // MAIN_WINDOW_H_