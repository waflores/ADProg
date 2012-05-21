#include <QtGui>
#include <QStringList>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "editUsers.h"
#include "adprog.h"
#include "userattrib.h"

/*
 * EditUsers Class: This class implements the editing layout for the user interface.
 */
EditUsers::EditUsers(ImportUsers * prog, QWidget *parent):UserViewGUI(prog, parent){
 /* This Object calls the super class, so that the user database displays users
  * to be edited.
  */       
    setWindowTitle("View and Edit users...");
    /* Build the navigation layout */
    /* Build the previous record button */
    prevRecord = new QPushButton("Previous");
    prevRecord->show();

    /* Build the next record button */
    nextRecord = new QPushButton("Next");
    nextRecord->show();

    /* Build the delete record button */
    delUser = new QPushButton("Delete User");
    delUser->show();

    /* Build the edit record button */
    editUser = new QPushButton("Edit User");
    editUser->show();

    /* Build the submitEdit and cancelEdit Buttons, but hide these */
    cancelEdit = new QPushButton("Cancel/Finish Edit");
    cancelEdit->hide();

    submitEdit = new QPushButton("Submit Edit");
    submitEdit->hide();

    /* navigation layout for submitEdit and cancelEdit buttons to reside */
    navLayout = new QHBoxLayout;
    navLayout->addWidget(prevRecord);
    navLayout->addWidget(nextRecord);
    navLayout->addWidget(delUser);
    navLayout->addWidget(editUser);
    navLayout->addWidget(submitEdit);
    navLayout->addWidget(cancelEdit);

    navLayout->setGeometry(QRect(200, 610, 161, 51));
    navLayout->setContentsMargins(0, 0, 0, 0);
    /* End navigation Layout */
    
    mainLayout->addLayout(navLayout, 5, 0, 1, 3);
    /* Connect some functions to the buttons on the GUI */
    connect(nextRecord, SIGNAL(clicked()), this, SLOT(nextPerson()));
    connect(prevRecord, SIGNAL(clicked()), this, SLOT(prevPerson()));
    connect(delUser, SIGNAL(clicked()), this, SLOT(deletePerson()));
    connect(editUser, SIGNAL(clicked()), this, SLOT(editPerson()));
    connect(submitEdit, SIGNAL(clicked()), this, SLOT(submitChange()));
    connect(cancelEdit, SIGNAL(clicked()), this, SLOT(cancelChange()));
    
    /* Populate the GUI on end of construction */
    displayEdits(calling_prog->dispPersonList());
}

/****************** EDITUSER MEMBER FUNCTIONS *******************************/
void EditUsers::nextPerson(){
    if(current_person->next) {
        displayEdits(current_person->next);
    }
    else {
        while(current_person->prev){
            current_person = current_person->prev;
        }
        displayEdits(current_person);
    }

}
void EditUsers::prevPerson(){
    if(current_person->prev){
        displayEdits(current_person->prev);
    }
    else {
        while(current_person->next){
            current_person = current_person->next;
        }
        displayEdits(current_person);
    }
}

void EditUsers::deletePerson(){
    int ret;
    ret = QMessageBox::warning(this,"Delete this User", "Are you sure you want to delete this user?",
                        QMessageBox::Cancel, QMessageBox::Ok);
    switch(ret){
        case QMessageBox::Ok:
            current_person = deleteOneUser(current_person);
            QMessageBox::information(this, "Deletion Successful!", "User was deleted.");
            if (current_person) displayEdits(current_person);
            else {
                this->close();
                QMessageBox::information(this, "Deleted all users...", "All users in database were deleted.");
            }
            break;
        case QMessageBox::Cancel:
            return;
        default:
            break;
    }
}

void EditUsers::editPerson(){
    updateInterface(EDIT_MODE_BUTTONS);
}
void EditUsers::submitChange() {
    updateInterface(NAVIGATION_MODE);
    processChanges();
    displayEdits(current_person);
    updateInterface(EDIT_MODE);
}

void EditUsers::cancelChange() {
    updateInterface(NAVIGATION_MODE_BUTTONS);
}

void EditUsers::processChanges() {
    char * place = NULL;
//    char * streetAddr = NULL;
//    char * city = NULL;
//    char * state = NULL;
//    char * zip = NULL;
//    char * country = NULL;
    char * firstName = NULL;
    char * middleName = NULL;
    char * lastName = NULL;
    char * prefName = NULL;
    char * initials = NULL;
    char * userName = NULL;
    char * email = NULL;
    char * title = NULL;
    char * dept = NULL;
    char * password = NULL;
    char * mod = NULL;
//    char * manager = NULL;
//    char * desc = NULL;
//    char * scriptPath = NULL;
//    char * homeDrive = NULL;
    char * profilePath = NULL;
    char * homeDir = NULL;
//    char * UPN = NULL;
//    char * coName = NULL;

    /* person's office info */
    place = dispOfficeName(current_person->user);
    /* person's AD attributes */
    profilePath = dispProfilePath(current_person->user);
    homeDir = dispHomeDir(current_person->user);

    /* Person's name */
    firstName = dispFirstName(current_person->user);
    middleName = dispMiddleName(current_person->user);
    lastName = dispLastName(current_person->user);
    prefName = dispPrefferedName(current_person->user);
    initials = dispInitials(current_person->user);
    userName = dispUserName(current_person->user);
    email = dispEmail(current_person->user);
    title = dispTitle(current_person->user);
    dept = dispDept(current_person->user);
    password = dispPassword(current_person->user);
    mod = dispMod(current_person->user);

    /* first compare the contents of the text box with the field,
       If there is no string already, create one and assign it.
       else, if there are no changes, don't do anything,
       else, if there is a change -> make it into a c string
        and add it to the field, then trash the original.
        done.
     *
     */
    
    if (uNameEdit->isModified()) {
        char * retval = NULL;
        retval = changeUserName(uNameEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "User Name changed!", "Username has been changed.");
        else QMessageBox::information(this, "User Name not changed!", "Username has not been changed.");
    }
    if (FNameEdit->isModified()) {
        char * retval = NULL;
        retval = changeFirstName(FNameEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "First Name changed!", "First name has been changed.");
        else QMessageBox::information(this, "First Name not changed!", "First name has not been changed.");
    }
    if (MNameEdit->isModified()) {
        char * retval = NULL;
        retval = changeMiddleName(MNameEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Middle Name changed!", "Middle name has been changed.");
        else QMessageBox::information(this, "Middle Name not changed!", "Middle name has not been changed.");
    }
    if (LNameEdit->isModified()) {
        char * retval = NULL;
        retval = changeLastName(LNameEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Last Name changed!", "Last name has been changed.");
        else QMessageBox::information(this, "Last Name not changed!", "Last name has not been changed.");
    }
    if (deptEdit->isModified()) {
        char * retval = NULL;
        retval = changeDepartment(deptEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Department changed!", "Department has been changed.");
        else QMessageBox::information(this, "Department not changed!", "Department has not been changed.");
    }
    if (InitEdit->isModified()) {
        char * retval = NULL;
        retval = changeInitials(InitEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Initials changed!", "Initials have been changed.");
        else QMessageBox::information(this, "Initials not changed!", "Initials have not been changed.");
    }
    if (titleEdit->isModified()) {
        char * retval = NULL;
        retval = changeTitle(titleEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Title changed!", "Title has been changed.");
        else QMessageBox::information(this, "Title not changed!", "Title has not been changed.");
    }
    if (pNameEdit->isModified()) {
        char * retval = NULL;
        retval = changePreferredName(pNameEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Preferred Name changed!", "Preferred Name has been changed.");
        else QMessageBox::information(this, "Preferred Name not changed!", "Preferred Name has not been changed.");
    }
    if (officeNameView->isModified()) {
        // special case, needs to be carefully debugged
        Location retval = NULL;
        retval = changeOfficeName(officeNameView->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Office Name changed!", "Office Name has been changed.");
        else QMessageBox::information(this, "Office Name not changed!", "Office Name has not been changed.");
    }
    if (ppathview->isModified()) {
        //(strcmp(uNameEdit->text().toStdString().c_str(), userName))
    }
    if (homeDirView->isModified()) {
        //(strcmp(uNameEdit->text().toStdString().c_str(), userName))
    }
    if (/*ModCheck*/ 0) {
        //(strcmp(uNameEdit->text().toStdString().c_str(), userName))
    }
    if (EmailEdit->isModified()) {
        char * retval = NULL;
        retval = changeEmail(EmailEdit->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Email address changed!", "Email has been changed.");
        else QMessageBox::information(this, "Email address not changed!", "Email has not been changed.");
    }
    if (passwordView->isModified()) {
        char * retval = NULL;
        retval = changePassword(passwordView->text().toStdString().c_str(), current_person->user);
        if (retval) QMessageBox::information(this, "Password changed!", "Password has been changed.");
        else QMessageBox::information(this, "Password not changed!", "Password has not been changed.");
    }
}

void EditUsers::updateInterface(int mode) {
    /* Decide which GUI attributes are active */
    switch (mode) {
        case EDIT_MODE_BUTTONS:
            /* Change the state of the buttons */
            nextRecord->hide();
            prevRecord->hide();
            editUser->hide();
            submitEdit->show();
            cancelEdit->show();
        case EDIT_MODE: // falls through from Edit mode buttons
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
            break;
        case NAVIGATION_MODE_BUTTONS:
            /* change the state of the buttons */
            nextRecord->show();
            prevRecord->show();
            editUser->show();
            submitEdit->hide();
            cancelEdit->hide();
        case NAVIGATION_MODE: // Falls through from Navigation Mode
            /* make everything uneditable */
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
            coView->setEnabled(false);
            scriptPathView->setEnabled(false);
            officeAddrDisp->setEnabled(false);
            ModCheck->setEnabled(false);
            managerEdit->setEnabled(false);
            EmailEdit->setEnabled(false);
            descView->setEnabled(false);
            passwordView->setEnabled(false);
            hDriveView->setEnabled(false);
            dispNameView->setEnabled(false);
            break;
        default:
            break;
    }
}
