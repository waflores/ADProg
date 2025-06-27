/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <QtWidgets>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QWidget window;

  //! [create, lay out widgets and show]
  QLabel label{QApplication::translate("windowlayout", "Name:")};
  QLineEdit lineEdit{};

  QHBoxLayout layout{};
  layout.addWidget(&label);
  layout.addWidget(&lineEdit);
  window.setLayout(&layout);
  //! [create, lay out widgets and show]
  window.setWindowTitle(
      QApplication::translate("windowlayout", "Window layout"));
  window.show();
  return app.exec();
}
