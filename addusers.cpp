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

void AddUsers::submitAddForm(){}

void AddUsers::clearAddForm(){}