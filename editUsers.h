#ifndef EDITUSERS_H
#define EDITUSERS_H

#include <QWidget> /* For Gui */
#include "userattrib.h" /* The ADprogram API */
#include "userViewGUI.h"

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

/* User edit class */
class EditUsers : public UserViewGUI {
    Q_OBJECT
public:
    EditUsers(ImportUsers * prog, QWidget *parent = 0);
//    ImportUsers * calling_prog;
public slots:
//    void displayEdits(userList users);
    void nextPerson();
    void prevPerson();
    void deletePerson();
    void editPerson();
    void submitChange();
    void cancelChange();
    void processChanges();
    void updateInterface(int mode);

private:
//    // current person in the editusers
//    userList current_person;
//    QGridLayout *editLayout1;
//    QGridLayout *editLayout2;
//    QGridLayout *viewOnlyLayout1;
//    QGridLayout *mainLayout;
//    QGridLayout *viewOnlyLayout2;
//    QHBoxLayout *navLayout;
//    QCheckBox *ModCheck;
//    QLabel *addrLabel;
//    QLabel *cnLabel;
//    QLabel *coLabel;
//    QLabel *deptLabel;
//    QLabel *descLabel;
//    QLabel *dispNameLabel;
//    QLabel *emailLabel;
//    QLabel *fNameLabel;
//    QLabel *hDirLabel;
//    QLabel *hDriveLabel;
//    QLabel *initLabel;
//    QLabel *lNameLabel;
//    QLabel *managerLabel;
//    QLabel *mNameLabel;
//    QLabel *officeLabel;
//    QLabel *passLabel;
//    QLabel *pNameLabel;
//    QLabel *ppathLabel;
//    QLabel *progTitle;
//    QLabel *spathLabel;
//    QLabel *titleLabel;
//    QLabel *uNameLabel;
//    QLineEdit *cnView;
//    QLineEdit *coView;
//    QLineEdit *deptEdit;
//    QLineEdit *descView;
//    QLineEdit *dispNameView;
//    QLineEdit *EmailEdit;
//    QLineEdit *FNameEdit;
//    QLineEdit *hDriveView;
//    QLineEdit *homeDirView;
//    QLineEdit *InitEdit;
//    QLineEdit *LNameEdit;
//    QLineEdit *managerEdit;
//    QLineEdit *MNameEdit;
//    QLineEdit *officeNameView;
//    QLineEdit *passwordView;
//    QLineEdit *pNameEdit;
//    QLineEdit *ppathview;
//    QLineEdit *scriptPathView;
//    QLineEdit *titleEdit;
//    QLineEdit *uNameEdit;
//    QPushButton *cancelEdit;
//    QPushButton *submitEdit;
//    QPushButton *delUser;
//    QPushButton *editUser;
//    QPushButton *prevRecord;
//    QPushButton *nextRecord;
//    QTextEdit *officeAddrDisp;
//    QVBoxLayout *fileLayout;
//    QVBoxLayout *recordLayout;
};
#endif // EDITUSERS_H
