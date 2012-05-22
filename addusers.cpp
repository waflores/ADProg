/* 
 * File:   addusers.cpp
 * Author: Will Flores
 * Usage:
 * Description: This file implements the functions and layout of the graphical
 *      user interface that uses the AD program API to import users.
 * Environment: Windows 7, 64 bit build
 * Notes:
 * Revisions: NONE
 *
 * Created on May 20, 2012, 10:42 AM
 */
#include <QtGui>
#include "adprog.h"
#include "userattrib.h"
#include "addusers.h"

AddUsers::AddUsers(ImportUsers * prog, QWidget *parent)
        :UserViewGUI(prog, parent) 
{
    /* Set the title of the GUI */
    setWindowTitle("Add a User to the database...");
    
    /* Build a submit button */
    submitForm = new QPushButton("Submit");
    submitForm->show();
    
    /* Build a clear form button */
    clearForm = new QPushButton("Clear Form");
    clearForm->show();
    
    /* Build a layout and add it to the main window */
    submitLayout = new QHBoxLayout();
    submitLayout->addWidget(submitForm);
    submitLayout->addWidget(clearForm);
    
    mainLayout->addLayout(submitLayout, 5, 0, 1, 3);
    
    /* Connect signals to functions in the GUI */
    connect(submitForm, SIGNAL(clicked()), this, SLOT(submitAddForm()));
    connect(clearForm, SIGNAL(clicked()), this, SLOT(clearAddForm()));
    
    enableAdding();
}

void AddUsers::enableAdding() {
    /* Make everything editable */
    uNameEdit->setEnabled(true);
    FNameEdit->setEnabled(true);
    MNameEdit->setEnabled(true);
    LNameEdit->setEnabled(true);
    deptEdit->setEnabled(true);
    InitEdit->setEnabled(true);
    titleEdit->setEnabled(true);
    pNameEdit->setEnabled(true);
    officeNameView->setEnabled(true);
    ppathview->setEnabled(true);
    homeDirView->setEnabled(true);
    //coView->setEnabled(true);
    //scriptPathView->setEnabled(true);
    //officeAddrDisp->setEnabled(true);
    ModCheck->setEnabled(true);
    //managerEdit->setEnabled(true);
    EmailEdit->setEnabled(true);
    //descView->setEnabled(true);
    passwordView->setEnabled(true);
    //hDriveView->setEnabled(true);
    //dispNameView->setEnabled(true);
}
void AddUsers::disableAdding() {
        /* Make everything editable */
    uNameEdit->setEnabled(false);
    FNameEdit->setEnabled(false);
    MNameEdit->setEnabled(false);
    LNameEdit->setEnabled(false);
    deptEdit->setEnabled(false);
    InitEdit->setEnabled(false);
    titleEdit->setEnabled(false);
    pNameEdit->setEnabled(false);
    officeNameView->setEnabled(false);
    ppathview->setEnabled(false);
    homeDirView->setEnabled(false);
    //coView->setEnabled(true);
    //scriptPathView->setEnabled(true);
    //officeAddrDisp->setEnabled(true);
    ModCheck->setEnabled(false);
    //managerEdit->setEnabled(true);
    EmailEdit->setEnabled(false);
    //descView->setEnabled(true);
    passwordView->setEnabled(false);
    //hDriveView->setEnabled(true);
    //dispNameView->setEnabled(true);
}

/* Submit data to addUser_c */
void AddUsers::submitAddForm(){
    char ** str = NULL; // this is what's going to be passed to addUser_c function
    
}

void AddUsers::clearAddForm(){
    int ret = QMessageBox::warning(this,"Reset Form", "Are you sure you want to reset all fields?",
                        QMessageBox::Cancel, QMessageBox::Ok);
    switch(ret) {
        case QMessageBox::Ok:
            uNameEdit->clear();
            FNameEdit->clear();
            MNameEdit->clear();
            LNameEdit->clear();
            deptEdit->clear();
            InitEdit->clear();
            titleEdit->clear();
            pNameEdit->clear();
            officeNameView->clear();
            ppathview->clear();
            homeDirView->clear();
            ModCheck->setChecked(false);
            EmailEdit->clear();
            passwordView->clear();
            break;
        case QMessageBox::Cancel: /* Don't Do anything but fall through */
        default:
            break;
    }
}