/* File: userViewGUI.h
 * Author: Will
 * Usage: This class will be used as a parent class for GUIs to inherit from.
 * Description: This file contains the userViewGUI class which allows the user
 *              to choose a user record and depending on the implementation of
 *              the child class, will edit or view the user records from the ADPROG
 *              data structures.
 * Environment: Windows 7, x64 build
 *              Built in QtCreator compiler.
 * Notes: NONE
 * Revisions: 0.0, Initial Release
 *
 * Created on May 12, 2012
 */

#ifndef USERVIEWGUI_H
#define USERVIEWGUI_H
#include <QWidget> /* For Gui */
#include "userattrib.h" /* The ADprogram API */

/* Widgets for GUI */
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QCheckBox;
class ImportUsers;

#define ABSTRACT 0

/* Interface Mode Defines */
#define EDIT_MODE_BUTTONS 0
#define EDIT_MODE 1
#define ADD_USER_MODE 2
#define NAVIGATION_MODE_BUTTONS 3
#define NAVIGATION_MODE 4

/* User edit class */
class UserViewGUI : public QWidget {
    Q_OBJECT
public:
    UserViewGUI(ImportUsers * prog, QWidget *parent = 0);
    ImportUsers * calling_prog;
public slots:
    /* The method that displays the user information from the
     * Constructor's calling program.
     */
    void displayEdits(userList users);

protected:
    userList current_person; // current person in the editusers
    QGridLayout *editLayout1;
    QGridLayout *editLayout2;
    QGridLayout *viewOnlyLayout1;
    QGridLayout *mainLayout;
    QGridLayout *viewOnlyLayout2;
    QCheckBox *ModCheck;
    QLabel *addrLabel;
    QLabel *cnLabel;
    QLabel *coLabel;
    QLabel *deptLabel;
    QLabel *descLabel;
    QLabel *dispNameLabel;
    QLabel *emailLabel;
    QLabel *fNameLabel;
    QLabel *hDirLabel;
    QLabel *hDriveLabel;
    QLabel *initLabel;
    QLabel *lNameLabel;
    QLabel *managerLabel;
    QLabel *mNameLabel;
    QLabel *officeLabel;
    QLabel *passLabel;
    QLabel *pNameLabel;
    QLabel *ppathLabel;
    QLabel *progTitle;
    QLabel *spathLabel;
    QLabel *titleLabel;
    QLabel *uNameLabel;
    QLineEdit *cnView;
    QLineEdit *coView;
    QLineEdit *deptEdit;
    QLineEdit *descView;
    QLineEdit *dispNameView;
    QLineEdit *EmailEdit;
    QLineEdit *FNameEdit;
    QLineEdit *hDriveView;
    QLineEdit *homeDirView;
    QLineEdit *InitEdit;
    QLineEdit *LNameEdit;
    QLineEdit *managerEdit;
    QLineEdit *MNameEdit;
    QLineEdit *officeNameView;
    QLineEdit *passwordView;
    QLineEdit *pNameEdit;
    QLineEdit *ppathview;
    QLineEdit *scriptPathView;
    QLineEdit *titleEdit;
    QLineEdit *uNameEdit;
    QTextEdit *officeAddrDisp;
    QVBoxLayout *fileLayout;
    QVBoxLayout *recordLayout;
};
#endif // USERVIEWGUI_H
