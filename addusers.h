/* 
 * File:   adprog.c
 * Author: Will Flores
 * Usage:
 * Description: This file implements the functions and layout of the graphical
 *      user interface that uses the AD program API to import users.
 * Environment: Windows 7, 64 bit build
 * Notes:
 * Revisions: NONE
 *
 * Created on January 19, 2012, 10:42 AM
 */

#ifndef ADDUSERS_H
#define	ADDUSERS_H

#include <QWidget> /* For Gui */
#include "userattrib.h" /* The ADprogram API */
#include "userViewGUI.h"

/* Calling Program for GUI */
class ImportUsers;

/* User edit class */
class AddUsers : public UserViewGUI {
    Q_OBJECT
public:
    AddUsers(ImportUsers * prog, QWidget *parent = 0);
public slots:
    /* The child class's methods for the editing of attributes */
    void enableAdding();
    void clearAddForm();
    void submitAddForm();
private:
    QPushButton *clearForm;
    QPushButton *submitForm;
    QHBoxLayout *submitLayout;
};
#endif	/* ADDUSERS_H */

