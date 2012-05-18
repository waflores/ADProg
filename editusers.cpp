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
//        calling_prog = prog;

//        mainLayout = new QGridLayout;
//        setLayout(mainLayout); // Couples the layout with the window that's showing
//        setWindowTitle("View and Edit users...");

//        /* editLayout1 */
//        editLayout1 = new QGridLayout;
//        editLayout1->setGeometry(QRect(0, 50, 561, 121));

//        editLayout1->setContentsMargins(0, 0, 0, 0);
//        uNameLabel = new QLabel("User Name: ");
//        editLayout1->addWidget(uNameLabel, 0, 0, 1, 1);

//         uNameEdit = new QLineEdit;
//         uNameEdit->setEnabled(false);
//         editLayout1->addWidget(uNameEdit, 0, 1, 1, 1);

//        fNameLabel = new QLabel("First Name: ");
//        editLayout1->addWidget(fNameLabel, 1, 0, 1, 1);
//        FNameEdit = new QLineEdit;
//        FNameEdit->setEnabled(false);
//        editLayout1->addWidget(FNameEdit, 1, 1, 1, 1);

//        mNameLabel = new QLabel("Middle Name: ");
//        editLayout1->addWidget(mNameLabel, 1, 2, 1, 1);

//        MNameEdit = new QLineEdit;
//        MNameEdit->setEnabled(false);
//        editLayout1->addWidget(MNameEdit, 1, 3, 1, 1);

//        lNameLabel = new QLabel("Last Name: ");
//        editLayout1->addWidget(lNameLabel, 1, 4, 1, 1);

//        LNameEdit = new QLineEdit;
//        LNameEdit->setEnabled(false);
//        editLayout1->addWidget(LNameEdit, 1, 5, 1, 1);

//        deptLabel = new QLabel("Department: ");
//        editLayout1->addWidget(deptLabel, 0, 4, 1, 1);

//        deptEdit = new QLineEdit;
//        deptEdit->setEnabled(false);
//        editLayout1->addWidget(deptEdit, 0, 5, 1, 1);

//        initLabel = new QLabel("Initials: ");
//        editLayout1->addWidget(initLabel, 2, 0, 1, 1);

//        InitEdit = new QLineEdit;
//        InitEdit->setEnabled(false);
//        editLayout1->addWidget(InitEdit, 2, 1, 1, 1);

//        titleLabel = new QLabel("Title: ");
//        editLayout1->addWidget(titleLabel, 2, 2, 1, 1);

//        titleEdit = new QLineEdit;
//        titleEdit->setEnabled(false);
//        editLayout1->addWidget(titleEdit, 2, 3, 1, 1);

//        pNameLabel = new QLabel("Preferred Name: ");
//        editLayout1->addWidget(pNameLabel, 2, 4, 1, 1);

//        pNameEdit = new QLineEdit;
//        pNameEdit->setEnabled(false);
//        editLayout1->addWidget(pNameEdit, 2, 5, 1, 1);
//        /* End editLayout1 */

//   /* navigation layout */
//    // previous record button
//    prevRecord = new QPushButton("Previous");
//    prevRecord->show();

//    // next record button
//    nextRecord = new QPushButton("Next");
//    nextRecord->show();

//    // delete record button
//    delUser = new QPushButton("Delete User");
//    delUser->show();

//    // edit record button
//    editUser = new QPushButton("Edit User");
//    editUser->show();

//    // Build the submitEdit and cancelEdit Buttons, but hide these
//    cancelEdit = new QPushButton("Cancel/Finish Edit");
//    cancelEdit->hide();

//    submitEdit = new QPushButton("Submit Edit");
//    submitEdit->hide();

//    // navigation layout for previous 2 buttons to reside
//    navLayout = new QHBoxLayout;
//    navLayout->addWidget(prevRecord);
//    navLayout->addWidget(nextRecord);
//    navLayout->addWidget(delUser);
//    navLayout->addWidget(editUser);
//    navLayout->addWidget(submitEdit);
//    navLayout->addWidget(cancelEdit);

//    navLayout->setGeometry(QRect(200, 610, 161, 51));
//    navLayout->setContentsMargins(0, 0, 0, 0);
//        /* End navigation Layout */

//        /* viewOnlyLayout1 */
//   viewOnlyLayout1 = new QGridLayout;
//   viewOnlyLayout1->setContentsMargins(0, 0, 0, 0);
//   viewOnlyLayout1->setGeometry(QRect(0, 320, 571, 134));

//   officeNameView = new QLineEdit;
//   officeNameView->setEnabled(false);
//   viewOnlyLayout1->addWidget(officeNameView, 0, 1, 1, 1);

//   addrLabel = new QLabel("Office Address: ");
//   viewOnlyLayout1->addWidget(addrLabel, 1, 0, 1, 1);

//   ppathLabel = new QLabel("Profile Path: ");
//   viewOnlyLayout1->addWidget(ppathLabel, 2, 0, 1, 1);

//   ppathview = new QLineEdit;
//   ppathview->setEnabled(false);
//   viewOnlyLayout1->addWidget(ppathview, 2, 1, 1, 1);

//   officeLabel = new QLabel("Office Name: ");
//   viewOnlyLayout1->addWidget(officeLabel, 0, 0, 1, 1);

//   hDirLabel = new QLabel("Home Directory: ");
//   viewOnlyLayout1->addWidget(hDirLabel, 0, 2, 1, 1);

//   homeDirView = new QLineEdit;
//   homeDirView->setEnabled(false);
//   viewOnlyLayout1->addWidget(homeDirView, 0, 3, 1, 1);

//   coView = new QLineEdit;
//   coView->setEnabled(false);
//   viewOnlyLayout1->addWidget(coView, 1, 3, 1, 1);

//   spathLabel = new QLabel("Script Path: ");
//   viewOnlyLayout1->addWidget(spathLabel, 2, 2, 1, 1);

//   scriptPathView = new QLineEdit;
//   scriptPathView->setEnabled(false);
//   viewOnlyLayout1->addWidget(scriptPathView, 2, 3, 1, 1);

//   officeAddrDisp = new QTextEdit;
//   officeAddrDisp->setEnabled(false);
//   viewOnlyLayout1->addWidget(officeAddrDisp, 1, 1, 1, 1);

//   coLabel = new QLabel("Company: ");
//   viewOnlyLayout1->addWidget(coLabel, 1, 2, 1, 1);
//        /* End of viewOnlyLayout1 */

//        /* editLayout2 */
//   editLayout2 = new QGridLayout;
//   editLayout2->setContentsMargins(0, 0, 0, 0);
//   editLayout2->setGeometry(QRect(10, 190, 561, 80));
//   ModCheck = new QCheckBox("Modify", this);
//   ModCheck->setEnabled(false);
//   editLayout2->addWidget(ModCheck, 0, 0, 1, 1);

//   managerLabel = new QLabel("Manager: ");
//   editLayout2->addWidget(managerLabel, 0, 1, 1, 1);

//   managerEdit = new QLineEdit;
//   managerEdit->setEnabled(false);
//   editLayout2->addWidget(managerEdit, 0, 2, 1, 1);

//   emailLabel = new QLabel("Email: ");
//   editLayout2->addWidget(emailLabel, 0, 3, 1, 1);

//   EmailEdit = new QLineEdit;
//   EmailEdit->setEnabled(false);
//   editLayout2->addWidget(EmailEdit, 0, 4, 1, 1);
//        /* End of editLayout2 */

//   viewOnlyLayout2 = new QGridLayout;

//   passLabel = new QLabel("Password: ");
//   passLabel->setGeometry(QRect(290, 475, 53, 16));
//   viewOnlyLayout2->addWidget(passLabel, 0, 2, 1, 1);

//   descView = new QLineEdit;
//   descView->setEnabled(false);
//   descView->setGeometry(QRect(67, 475, 110, 20));
//   viewOnlyLayout2->addWidget(descView, 0, 1, 1, 1);

//   descLabel = new QLabel("Description: ");
//   descLabel->setGeometry(QRect(1, 475, 60, 16));
//   viewOnlyLayout2->addWidget(descLabel, 0, 0, 1, 1);

//   passwordView = new QLineEdit;
//   passwordView->setEnabled(false);
//   passwordView->setGeometry(QRect(364, 475, 110, 20));
//   viewOnlyLayout2->addWidget(passwordView, 0, 3, 1, 1);

//   dispNameLabel = new QLabel("Display Name: ");
//   dispNameLabel->setGeometry(QRect(290, 535, 68, 16));
//   viewOnlyLayout2->addWidget(dispNameLabel, 1, 2, 1, 1);

////   cnLabel = new QLabel("cn: ");
////   cnLabel->setGeometry(QRect(1, 535, 16, 16));
////   viewOnlyLayout2->addWidget(cnLabel, 2, 0, 1, 1);

//   hDriveLabel = new QLabel("Home Drive: ");
//   hDriveLabel->setGeometry(QRect(1, 505, 59, 16));
//   viewOnlyLayout2->addWidget(hDriveLabel, 1, 0, 1, 1);

//   hDriveView = new QLineEdit;
//   hDriveView->setEnabled(false);
//   hDriveView->setGeometry(QRect(67, 535, 110,20));
//   viewOnlyLayout2->addWidget(hDriveView, 1, 1, 1, 1);

////   cnView = new QLineEdit;
////   cnView->setGeometry(QRect(67, 535, 110, 20));
////   viewOnlyLayout2->addWidget(cnView, 2, 1, 1, 1);

//   dispNameView = new QLineEdit;
//   dispNameView->setEnabled(false);
//   dispNameView->setGeometry(QRect(364, 535, 110, 20));
//   viewOnlyLayout2->addWidget(dispNameView, 1, 3, 1, 1);

//      // Some Layouts will not be shown
//   mainLayout->addLayout(editLayout1, 1, 0, 1, 3);
//   mainLayout->addLayout(editLayout2, 2, 0, 1, 3);
//   mainLayout->addLayout(viewOnlyLayout1, 3, 0, 1, 3);
//   mainLayout->addLayout(viewOnlyLayout2, 4, 0, 1, 3);
//   mainLayout->addLayout(navLayout, 5, 0, 1, 3);

//   connect(nextRecord, SIGNAL(clicked()), this, SLOT(nextPerson()));
//   connect(prevRecord, SIGNAL(clicked()), this, SLOT(prevPerson()));
//   connect(delUser, SIGNAL(clicked()), this, SLOT(deletePerson()));
//   connect(editUser, SIGNAL(clicked()), this, SLOT(editPerson()));
//   connect(submitEdit, SIGNAL(clicked()), this, SLOT(submitChange()));
//   connect(cancelEdit, SIGNAL(clicked()), this, SLOT(cancelChange()));
//   displayEdits(calling_prog->dispPersonList());
}

/****************** EDITUSER MEMBER FUNCTIONS *******************************/
//void EditUsers::displayEdits(userList users){
//    current_person = users;
//    char * place = NULL;
//    char * streetAddr = NULL;
//    char * city = NULL;
//    char * state = NULL;
//    char * zip = NULL;
//    char * country = NULL;
//    char * firstName = NULL;
//    char * middleName = NULL;
//    char * lastName = NULL;
//    char * prefName = NULL;
//    char * initials = NULL;
//    char * userName = NULL;
//    char * email = NULL;
//    char * title = NULL;
//    char * dept = NULL;
//    char * password = NULL;
//    char * mod = NULL;
//    char * manager = NULL;
//    char * desc = NULL;
//    char * scriptPath = NULL;
//    char * homeDrive = NULL;
//    char * profilePath = NULL;
//    char * homeDir = NULL;
//    char * UPN = NULL;
//    char * coName = NULL;

//    /* person's office info */
//    place = dispOfficeName(users->user);
//    streetAddr = dispStreetAddr(users->user);
//    city = dispCity(users->user);
//    zip = dispZip(users->user);
//    state = dispState(users->user);
//    country = dispCountry(users->user);
//    /* end person's office info */
//    officeNameView->setText(place);
//    officeAddrDisp->clear();
//    officeAddrDisp->append(streetAddr);
//    officeAddrDisp->append(city);
//    officeAddrDisp->append(state);
//    officeAddrDisp->append(zip);
//    officeAddrDisp->append(country);

//    /* person's AD attributes */
//    scriptPath = dispScriptPath(users->user);
//    homeDrive = dispHomeDrive(users->user);
//    profilePath = dispProfilePath(users->user);
//    homeDir = dispHomeDir(users->user);
//    UPN = dispUPN(users->user);
//    coName = dispCompanyName();
//    /* end person's AD attributes */

//    scriptPathView->setText(scriptPath);
//    ppathview->setText(profilePath);
//    hDriveView->setText(homeDrive);
//    homeDirView->setText(homeDir);
//    coView->setText(coName);

//    /* Person's name */
//    firstName = dispFirstName(users->user);
//    middleName = dispMiddleName(users->user);
//    lastName = dispLastName(users->user);
//    prefName = dispPrefferedName(users->user);
//    initials = dispInitials(users->user);
//    userName = dispUserName(users->user);
//    email = dispEmail(users->user);
//    title = dispTitle(users->user);
//    dept = dispDept(users->user);
//    password = dispPassword(users->user);
//    mod = dispMod(users->user);
//    manager = dispManager(users->user);
//    desc = dispDesc(users->user);
//    /* end person's name info */

//    /* Get all user attributes */
//    uNameEdit->setText(userName);
//    FNameEdit->setText(firstName);
//    MNameEdit->setText(middleName);
//    LNameEdit->setText(lastName);
//    pNameEdit->setText(prefName);
//    InitEdit->setText(initials);
//    deptEdit->setText(dept);
//    EmailEdit->setText(email);
//    titleEdit->setText(title);
//    descView->setText(desc);
//    managerEdit->setText(manager);
//    passwordView->setText(password);
//    if (!strcasecmp(mod, "true")) ModCheck->setChecked(true);
//    else ModCheck->setChecked(false);
//}

void EditUsers::nextPerson(){
//    if(current_person->next) {
//        displayEdits(current_person->next);
//    }
//    else {
//        while(current_person->prev){
//            current_person = current_person->prev;
//        }
//        displayEdits(current_person);
//    }

}
void EditUsers::prevPerson(){
//    if(current_person->prev){
//        displayEdits(current_person->prev);
//    }
//    else {
//        while(current_person->next){
//            current_person = current_person->next;
//        }
//        displayEdits(current_person);
//    }
}

void EditUsers::deletePerson(){
//    int ret = QMessageBox::warning(this,"Delete this User", "Are you sure you want to delete this user?",
//                        QMessageBox::Cancel, QMessageBox::Ok);
//    switch(ret){
//        case QMessageBox::Ok:
//            current_person = deleteOneUser(current_person);
//            QMessageBox::information(this, "Deletion Successful!", "User was deleted.");
//            if (current_person) displayEdits(current_person);
//            else {
//                this->close();
//                QMessageBox::information(this, "Deleted all users...", "All users in database were deleted.");
//            }
//            break;
//        case QMessageBox::Cancel:
//            return;
//        default:
//            break;
//    }
}

void EditUsers::editPerson(){
//    /* Change the state of the buttons */
//    nextRecord->hide();
//    prevRecord->hide();
//    editUser->hide();
//    submitEdit->show();
//    cancelEdit->show();

//    /* Make everything editable */
//    uNameEdit->setEnabled(true);
//    FNameEdit->setEnabled(true);
//    MNameEdit->setEnabled(true);
//    LNameEdit->setEnabled(true);
//    deptEdit->setEnabled(true);
//    InitEdit->setEnabled(true);
//    titleEdit->setEnabled(true);
//    pNameEdit->setEnabled(true);
//    officeNameView->setEnabled(true);
//    ppathview->setEnabled(true);
//    homeDirView->setEnabled(true);
//    //coView->setEnabled(true);
//    //scriptPathView->setEnabled(true);
//    //officeAddrDisp->setEnabled(true);
//    ModCheck->setEnabled(true);
//    //managerEdit->setEnabled(true);
//    EmailEdit->setEnabled(true);
//    //descView->setEnabled(true);
//    passwordView->setEnabled(true);
//    //hDriveView->setEnabled(true);
//    //dispNameView->setEnabled(true);

}
void EditUsers::submitChange() {
//    processChanges();
//    displayEdits(current_person);
}

void EditUsers::cancelChange() {
//    /* change the state of the buttons */
//    nextRecord->show();
//    prevRecord->show();
//    editUser->show();
//    submitEdit->hide();
//    cancelEdit->hide();

//    /* make everything uneditable */
//    uNameEdit->setEnabled(false);
//    FNameEdit->setEnabled(false);
//    MNameEdit->setEnabled(false);
//    LNameEdit->setEnabled(false);
//    deptEdit->setEnabled(false);
//    InitEdit->setEnabled(false);
//    titleEdit->setEnabled(false);
//    pNameEdit->setEnabled(false);
//    officeNameView->setEnabled(false);
//    ppathview->setEnabled(false);
//    homeDirView->setEnabled(false);
//    coView->setEnabled(false);
//    scriptPathView->setEnabled(false);
//    officeAddrDisp->setEnabled(false);
//    ModCheck->setEnabled(false);
//    managerEdit->setEnabled(false);
//    EmailEdit->setEnabled(false);
//    descView->setEnabled(false);
//    passwordView->setEnabled(false);
//    hDriveView->setEnabled(false);
//    dispNameView->setEnabled(false);

}

void EditUsers::processChanges() {
//    char * place = NULL;
////    char * streetAddr = NULL;
////    char * city = NULL;
////    char * state = NULL;
////    char * zip = NULL;
////    char * country = NULL;
//    char * firstName = NULL;
//    char * middleName = NULL;
//    char * lastName = NULL;
//    char * prefName = NULL;
//    char * initials = NULL;
//    char * userName = NULL;
//    char * email = NULL;
//    char * title = NULL;
//    char * dept = NULL;
//    char * password = NULL;
//    char * mod = NULL;
////    char * manager = NULL;
////    char * desc = NULL;
////    char * scriptPath = NULL;
////    char * homeDrive = NULL;
//    char * profilePath = NULL;
//    char * homeDir = NULL;
////    char * UPN = NULL;
////    char * coName = NULL;

//    /* person's office info */
//    place = dispOfficeName(current_person->user);
//    /* person's AD attributes */
//    profilePath = dispProfilePath(current_person->user);
//    homeDir = dispHomeDir(current_person->user);

//    /* Person's name */
//    firstName = dispFirstName(current_person->user);
//    middleName = dispMiddleName(current_person->user);
//    lastName = dispLastName(current_person->user);
//    prefName = dispPrefferedName(current_person->user);
//    initials = dispInitials(current_person->user);
//    userName = dispUserName(current_person->user);
//    email = dispEmail(current_person->user);
//    title = dispTitle(current_person->user);
//    dept = dispDept(current_person->user);
//    password = dispPassword(current_person->user);
//    mod = dispMod(current_person->user);

//    /* first compare the contents of the text box with the field,
//       If there is no string already, create one and assign it.
//       else, if there are no changes, don't do anything,
//       else, if there is a change -> make it into a c string
//        and add it to the field, then trash the original.
//        done.
//     *
//     */


//    if (uNameEdit->isModified()) {
//            char * retval = NULL;
//            retval = changeUserName(uNameEdit->text().toStdString().c_str(), current_person->user);
//            if (retval) QMessageBox::information(this, "User Name changed!", "Username has been changed.");
//            else QMessageBox::information(this, "User Name not changed!", "Username has not been changed.");
//    }
//    if (FNameEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeFirstName(FNameEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "First Name changed!", "First name has been changed.");
//        else QMessageBox::information(this, "First Name not changed!", "First name has not been changed.");
//    }
//    if (MNameEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeMiddleName(MNameEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Middle Name changed!", "Middle name has been changed.");
//        else QMessageBox::information(this, "Middle Name not changed!", "Middle name has not been changed.");

//    }
//    if (LNameEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeLastName(LNameEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Last Name changed!", "Last name has been changed.");
//        else QMessageBox::information(this, "Last Name not changed!", "Last name has not been changed.");

//    }
//    if (deptEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeDepartment(deptEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Department changed!", "Department has been changed.");
//        else QMessageBox::information(this, "Department not changed!", "Department has not been changed.");
//    }
//    if (InitEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeInitials(InitEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Initials changed!", "Initials have been changed.");
//        else QMessageBox::information(this, "Initials not changed!", "Initials have not been changed.");
//    }
//    if (titleEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeTitle(titleEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Title changed!", "Title has been changed.");
//        else QMessageBox::information(this, "Title not changed!", "Title has not been changed.");
//    }
//    if (pNameEdit->isModified()) {
//        char * retval = NULL;
//        retval = changePreferredName(pNameEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Preferred Name changed!", "Preferred Name has been changed.");
//        else QMessageBox::information(this, "Preferred Name not changed!", "Preferred Name has not been changed.");
//    }
//    if (officeNameView->isModified()) {
//        // special case, needs to be carefully debugged
//        Location retval = NULL;
//        //retval = changeOfficeName(officeNameView->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Office Name changed!", "Office Name has been changed.");
//        else QMessageBox::information(this, "Office Name not changed!", "Office Name has not been changed.");
//    }
//    if (ppathview->isModified()) {
//        //(strcmp(uNameEdit->text().toStdString().c_str(), userName))

//    }
//    if (homeDirView->isModified()) {
//        //(strcmp(uNameEdit->text().toStdString().c_str(), userName))

//    }
//    if (/*ModCheck*/ 0) {
//        //(strcmp(uNameEdit->text().toStdString().c_str(), userName))

//    }
//    if (EmailEdit->isModified()) {
//        char * retval = NULL;
//        retval = changeEmail(EmailEdit->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Email address changed!", "Email has been changed.");
//        else QMessageBox::information(this, "Email address not changed!", "Email has not been changed.");
//    }
//    if (passwordView->isModified()) {
//        char * retval = NULL;
//        retval = changePassword(passwordView->text().toStdString().c_str(), current_person->user);
//        if (retval) QMessageBox::information(this, "Password changed!", "Password has been changed.");
//        else QMessageBox::information(this, "Password not changed!", "Password has not been changed.");
//    }
}

void EditUsers::updateInterface(int mode) {

}
