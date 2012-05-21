/* 
 * File:   adprog.h
 * Author: Will Flores
 * Usage: Implemented by adprog.cpp
 * Description: This file defines the functions and layout of the graphical
 *      user interface that uses the AD program API to import users.
 * Environment: Windows 7, 64 bit build
 * Notes:
 * Revisions: NONE
 *
 * Created on January 19, 2012, 10:42 AM
 */

#ifndef ADPROG_H
#define	ADPROG_H

#include <QWidget> /* For Gui */
#include "userattrib.h" /* The ADprogram API */
#include "editUsers.h"
#include "addusers.h"

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
class EditUsers;
class AddUsers;

/* GUI Class */
class ImportUsers : public QWidget {
    Q_OBJECT
            
public:
    ImportUsers(QWidget *parent = 0);
    
public slots:
    void loadFromFile();
    QString saveToFile();
    int settingsFile();
    void importToAD();
    void addUserPerson();
    void deleteUserList();
    void buttonStub();
    void editPerson();
    userList dispPersonList();
    
private:
    QString versionNum;
    QHBoxLayout *navLayout;
    QLabel *progTitle;
    QPushButton *addUser;
    QPushButton *delUsers;
    QPushButton *editUser;
    QPushButton *exportFile;
    QPushButton *importUsers;
    QPushButton *loadFile;
    QPushButton *options;
    QVBoxLayout *fileLayout;
    QVBoxLayout *recordLayout;
    EditUsers *edit_GUI;
    AddUsers *add_GUI;
    userList people;
};

#endif	/* ADPROG_H */

