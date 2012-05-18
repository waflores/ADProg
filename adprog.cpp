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

#include <QtGui>
#include <QStringList>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "adprog.h"
#include "editUsers.h"
#include "userattrib.h"


/* ImportUsers Class: This class implements the main layout for the user to 
 *      interface with user information. 
 */
ImportUsers::ImportUsers(QWidget *parent) : QWidget(parent) {
    // Set up Main layout
    versionNum = "1.0";
    QGridLayout *mainLayout = new QGridLayout;
    
    // Format Program Title
    QLabel *progTitle = new QLabel("New User Import v " + versionNum);
    progTitle->setGeometry(QRect(210, 10, 151, 51));
    QFont font;
    font.setPointSize(14);
    progTitle->setFont(font);
    
    mainLayout->addWidget(progTitle, 0, 1);
    setLayout(mainLayout); // Where the buttons show up on the main screen
    setWindowTitle("Active Directory New User Import Utility"); // Program title
    
    // add user button
    addUser = new QPushButton("Add New User...");
    addUser->show();
    
    // delete user button
    delUsers = new QPushButton("Delete All Users");
    delUsers->show();
    
    // edit user button
    editUser = new QPushButton("Edit Users...");
    editUser->show();
    
    // layout for previous 3 buttons to reside
    recordLayout = new QVBoxLayout;
    recordLayout->addWidget(addUser);
    recordLayout->addWidget(editUser);
    recordLayout->addWidget(delUsers);
    recordLayout->setGeometry(QRect(30, 570, 101, 111));
    recordLayout->setContentsMargins(0, 0, 0, 0);
    
    // export file only button
    exportFile = new QPushButton("Export...");
    exportFile->show();
    
    // import users to Active Directory file button
    importUsers = new QPushButton("Import to AD...");
    importUsers->show();
    
    // load file full of users button
    loadFile = new QPushButton("Load...");
    loadFile->show();
    
    // options button
    options = new QPushButton("Options...");
    options->show();
    
    // layout where previous 4 buttons reside
    fileLayout = new QVBoxLayout;
    fileLayout->addWidget(loadFile);
    fileLayout->addWidget(exportFile);
    fileLayout->addWidget(importUsers);
    fileLayout->addWidget(options);
    fileLayout->setGeometry(QRect(460, 570, 113, 112));
    fileLayout->setContentsMargins(0, 0, 0, 0);

    // The previous layouts we created are now placed on the main layout for
    //          asthetic purposes
    mainLayout->addLayout(recordLayout, 1, 0, 1, 1);
    mainLayout->addLayout(fileLayout, 1, 2, 1, 1);
    
#ifndef QT_NO_SHORTCUT
#endif // QT_NO_SHORTCUT
    /* Set the tab order of buttons */
        QWidget::setTabOrder(addUser, editUser);
        QWidget::setTabOrder(editUser, delUsers);
        QWidget::setTabOrder(delUsers, loadFile);
        QWidget::setTabOrder(loadFile, exportFile);
        QWidget::setTabOrder(exportFile, importUsers);
        QWidget::setTabOrder(importUsers, options);
        
        // button press functions
    connect(loadFile, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(exportFile, SIGNAL(clicked()), this, SLOT(saveToFile()));
    connect(importUsers, SIGNAL(clicked()), this, SLOT(importToAD()));
    connect(addUser, SIGNAL(clicked()), this, SLOT(addUserPerson()));
    
    // Button stubs
    connect(editUser, SIGNAL(clicked()), this, SLOT(editPerson()));
    connect(delUsers, SIGNAL(clicked()), this, SLOT(deleteUserList()));
    connect(options, SIGNAL(clicked()), this, SLOT(buttonStub()));
    
    // Load settings file for the program

    if (settingsFile() != SUCCESS) throw FAIL;

    // Set the people field to null
    people = NULL;
}
void ImportUsers::editPerson() {
	if (getuserCount() > 0) {
		edit_GUI = new EditUsers(this,0);
		edit_GUI->show();
	}    
	else {
        QMessageBox::information(this, "No users in database...", "There are no users to edit.");
    }
}

userList ImportUsers::dispPersonList() {
    return this->people;
}

/* buttonStub: helps stub a button. Returns a message box when pressed.
 */
void ImportUsers::buttonStub() {
    // used to provide some functionality to button stub
    QMessageBox::information(this, "Button is a dummy...", "This button doesn't do anything in this release: " + versionNum);
}

/* 
 * settingsFile: This function interacts with the userattrib API and couples
 *      a GUI component for the settings file to initialize global data.
 */
int ImportUsers::settingsFile() { // Load settings from default settings file
    int retval;
    QString fileName = "settings.dat";
    
    retval = getSettings(fileName.toAscii(), "Import Users");
    
    // oops... we didn't get a vaild settings file
    while (retval != SUCCESS){
        QMessageBox openSetFile(this);
        QPushButton * SettingsOpen = openSetFile.addButton("Open Settings File...", QMessageBox::ActionRole);
        QPushButton * TerminateProg = openSetFile.addButton("Terminate program", QMessageBox::ActionRole);
        openSetFile.setWindowTitle("Settings file Missing...");
        openSetFile.setText("Please select a settings file to use or terminate program to cancel.");
        openSetFile.exec();
        if (openSetFile.clickedButton() == SettingsOpen) {
            fileName = QFileDialog::getOpenFileName(this, "Settings file to Open", "",
                                                "Settings File (*.dat);;All Files (*)");
            QMessageBox::information(this, "Settings File", "Rename this file \"settings.dat\" and place it into the directory this program runs.");
            retval = getSettings(fileName.toAscii(), "Import Users");
            if (retval == SUCCESS) {
                QMessageBox::information(this, "Settings File Opened!", "Settings file was imported successfully!");
                break;
            }
        }
        else if (openSetFile.clickedButton() == TerminateProg) {
            return FAIL;
        }
    }
     return SUCCESS;
}

/* 
 * saveToFile: This function provides a GUI for the userattrib API function
 *      'exportUsers.' It allows the user to use a file dialog to choose the
 *      appropriate file.
 */
QString ImportUsers::saveToFile() {
    int retval; // check return value of exportUsers
    
    QString fileName = QFileDialog::getSaveFileName(this,
                        "Export User Files to a csv...", "",
                            "Export (*.csv);;All Files(*)");
    if(fileName.isEmpty()) return NULL;
    else {
        // Export the users
        retval = exportUsers(people, fileName.toAscii());
        if(retval == SUCCESS){
            QMessageBox::information(this, "Exported a file", "Sucessful Export to " + fileName);
            return fileName;
        }
        else QMessageBox::information(this, "Failed to Export file", "Failed to Export to " + fileName);
    }
    return NULL;
}

/*
 * loadFromFile: This function provides a GUI for the userattrib API function
 *      'batchImport.' It allows the user to use a file dialog to choose the 
 *      appropriate file.
 */
void ImportUsers::loadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open New Users to import...",
                                                    "", "New User Files (*.csv);;All Files (*)");
    if(fileName.isEmpty()) return;
    else {
        people = batchImport(fileName.toAscii()); // from userattrib.c/h
        // check to see if everything panned out ok
        if (people) QMessageBox::information(this, "Imported a file", "Sucessful import of " + fileName);
        else QMessageBox::information(this, "Failed to Import file", "Failed to import from " + fileName);
    }
}

/*
 * importToAD: This function provides a GUI for the userattrib API function
 *      'batchImport' and invoking the VBS to import thses users into Active
 *      Directory. It allows the user to use a file dialog to choose the 
 *      appropriate file.
 */
void ImportUsers::importToAD() {
    QString fileName = saveToFile();
    if (fileName.isNull()) QMessageBox::information(this, "Failed to Save File", "Did not import to AD. Please try again.");
    else {
        QString scriptName = QFileDialog::getOpenFileName(this,
                                        "Select script to execute...", "", 
                                        "Visual Basic Scripts (*.vbs);;All Files (*)");
        if(scriptName.isEmpty()) return;
        else{
            // from windows API
            ShellExecuteA(NULL, NULL, scriptName.toAscii(), fileName.toAscii(), NULL, SW_SHOW);
            QMessageBox::information(this, "Export Complete", "w00t");
        }
        
    }
}

/*
 * addUserPerson: This function provides a GUI for the userattrib API function
 *      'addOneUser.' It allows the user to add a user one at a time.
 */
void ImportUsers::addUserPerson() {
    QStringList prompts;
    QString input;
    int peopleCount;
    char ** str = NULL; // this is what's going to be passed to addUser_c function
    User retval; 
    bool ok;
    QStringList inputArray;
    prompts << "user name." << "first name." << "last name." << "email address.";
    prompts << "title." << "department." << "office name." << "password.";
    prompts << "preferred name." << "middle name." << "modify value (TRUE or FALSE).";
    //prompts << "manager.";
    
    for (int index = 0; index < prompts.size(); ++index) {
        input = QInputDialog::getText(this, "Input " + prompts.at(index),
                                        "Please input " + prompts.at(index), 
                                    QLineEdit::Normal, QDir::home().dirName(),
                                    &ok);
        
        if (ok && !input.isEmpty()) {
                inputArray << input.trimmed();
        }
        else {
            QMessageBox cancelConfirm(this);
            QPushButton * omitField = cancelConfirm.addButton("Omit", QMessageBox::ActionRole);
            QPushButton * exitAdd = cancelConfirm.addButton(QMessageBox::Abort);
            cancelConfirm.setWindowTitle("Leave Blank or Exit?");
            cancelConfirm.setText("Click \"Omit\" to leave field blank or \"Abort\" to cancel adding a user.");
            cancelConfirm.exec();
            
            // check the message box's ret val
            if (cancelConfirm.clickedButton() == omitField) { 
                inputArray << "*"; // push a star to omit field
            }
            else if (cancelConfirm.clickedButton() == exitAdd) {
                QMessageBox::information(this, "User adding cancelled", "User was not added.");
                return; // abort adding a person
            }
        }
    }
    
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
        people = getMasterUserList();
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

}

/*
 * deleteUserList: This function provides a GUI for the userattrib API function
 *      'deleteAllUsers.' It allows the user to delete all the users on the heap.
 */
void ImportUsers::deleteUserList() {
    int delval;
    int ret = QMessageBox::warning(this,"Delete all users", "Are you sure you want to delete all users?",
                        QMessageBox::Cancel, QMessageBox::Ok);
    
    switch(ret){
        case QMessageBox::Ok:
            delval = deleteAllUsers(people);
            // check if we deleted anyone
            if (delval == SUCCESS) QMessageBox::information(this, "Deletion Successful!", "All users were deleted.");
            else QMessageBox::information(this, "Deletion Unsuccessful", "No users were deleted.");
            break;
        case QMessageBox::Cancel:
            return;
        default:
            break;
    }
}

