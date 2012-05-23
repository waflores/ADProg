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
//    InitEdit->setEnabled(true);
    titleEdit->setEnabled(true);
    pNameEdit->setEnabled(true);
    officeNameView->setEnabled(true);
//    ppathview->setEnabled(true);
//    homeDirView->setEnabled(true);
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
    QStringList inputArray;
    /* Place all the fields that we're coing to collect in the input list */
    QString formStr; 
    int columnCount;
    int peopleCount;
    User retval = NULL; // determine if people were added
    
    disableAdding(); // don't allow applying edits
    /* Place inputs into an array to process */
     for (columnCount = 0; columnCount < 11; ++columnCount){
            switch(columnCount){
                case 0:
                    formStr = uNameEdit->text();
                    break;
                case 1:
                    formStr = FNameEdit->text();
                    break;
                case 2:
                    formStr = LNameEdit->text();
                    break;
                case 3:
                    formStr = EmailEdit->text();
                    break;
                case 4:
                    formStr = titleEdit->text();
                    break;
                case 5:
                    formStr = deptEdit->text();
                    break;
                case 6:
                    formStr = officeNameView->text();
                    break;
                case 7:
                    formStr = passwordView->text();
                    break;
                case 8:
                    formStr = pNameEdit->text();
                    break;
                case 9:
                    formStr = MNameEdit->text();
                    break;
                case 10:
                    if (ModCheck->isChecked()) formStr = "TRUE";
                    else formStr = "FALSE";
                    break;
                default:
                    formStr = "";
                    break;
            }
            if(formStr.trimmed().isNull() || formStr.trimmed().isEmpty()) inputArray << "*";
            else inputArray << formStr.trimmed();
        }
      
//    for (int index = 0; index < prompts.size(); ++index) {
//        input = QInputDialog::getText(this, "Input " + prompts.at(index),
//                                        "Please input " + prompts.at(index), 
//                                    QLineEdit::Normal, QDir::home().dirName(),
//                                    &ok);
//        
//        if (ok && !input.isEmpty()) {
//                inputArray << input.trimmed();
//        }
//        else {
//            QMessageBox cancelConfirm(this);
//            QPushButton * omitField = cancelConfirm.addButton("Omit", QMessageBox::ActionRole);
//            QPushButton * exitAdd = cancelConfirm.addButton(QMessageBox::Abort);
//            cancelConfirm.setWindowTitle("Leave Blank or Exit?");
//            cancelConfirm.setText("Click \"Omit\" to leave field blank or \"Abort\" to cancel adding a user.");
//            cancelConfirm.exec();
//            
//            // check the message box's ret val
//            if (cancelConfirm.clickedButton() == omitField) { 
//                inputArray << "*"; // push a star to omit field
//            }
//            else if (cancelConfirm.clickedButton() == exitAdd) {
//                QMessageBox::information(this, "User adding cancelled", "User was not added.");
//                return; // abort adding a person
//            }
//        }
//    }

        // convert the StringList to a char **
    str = new char * [inputArray.size() + 1];
    for (int i = 0; i < inputArray.size(); ++i) {
        str[i] = new char[strlen(inputArray.at(i).toStdString().c_str()) + 1];
        strcpy(str[i], inputArray.at(i).toStdString().c_str());
    }
    str[inputArray.size()] = ((char) NULL); // NULL Terminated array
    // push these items into master user linked list

    /******************************* get the people field filled **********************/
    retval = addOneUser(str);
    peopleCount = getuserCount();
    if (peopleCount == 1) {
        UserViewGUI::calling_prog->people = getMasterUserList();
    }

    /**************************/

    // check return value of addOneUser
    if (retval != NULL) QMessageBox::information(this, "User added", inputArray.at(0) + " was successfully added.");
    else QMessageBox::information(this, "User not added", inputArray.at(0) + " was not added.");
    //Delete the output array
    int i = 0;
    while (str[i]) {
        delete str[i];
        ++i;
    }
    delete str; // get rid of this string array when we're through with this
    
    clearAddForm(false);
    enableAdding();
}

void AddUsers::clearAddForm(bool warn){
    int ret;
    if (warn) ret = QMessageBox::warning(this,"Reset Form", "Are you sure you want to reset all fields?",
                        QMessageBox::Cancel, QMessageBox::Ok);
    else ret = QMessageBox::Ok;
    
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