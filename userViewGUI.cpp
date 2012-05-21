/* File: userViewGUI.cpp
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
 * Created on May 11, 2012
 */

#include <QtGui>
#include <QStringList>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "userViewGUI.h"
#include "adprog.h"
#include "userattrib.h"

/***********************************************************************
* Module Name: UserViewGUI
* Original Author: Will
* Module Creation Date: May 11, 2012
* Description: This is the constructor for the GUI to be used in order
*              to view or edit user records.
*
* Calling Arguments:
* Name   Input/Output  Type         Description
* prog   Input         ImportUsers* The address of the calling program
*                                   on the heap.
* parent Input         QWidget*     The address of the parent QObject
*                                   building this GUI.
*
* Required Files/Databases:
*  None
*
* Non System Routines Called:
* Name           Description
* displayEdits   Populates the fields of the GUI with the User information.
*
* Return Value:
* Type           Description
* UserViewGUI    The pointer to the GUI Object that is created on the Heap.
*
* Error Codes/Exceptions:
*  None
*
* OS Specific Assumptions if any:
*  None
* Local Variables:
* Type Name Description
*  Many
* Global Variables Used:
* Type Name Origin Description
*  Many
* Constant and Macro Substitutions:
*
* Name Header File Description
* Modification History:
* Date Developer Action
*
***********************************************************************/
UserViewGUI::UserViewGUI(ImportUsers * prog, QWidget *parent):QWidget(parent) {
    calling_prog = prog; // Save the calling program address for functions.

    /* Build the main window for the GUI */
    mainLayout = new QGridLayout;
    setLayout(mainLayout); // Couples the layout with the window that's showing
    setWindowTitle("View and Edit users...");

    /* Build the top text fields in the GUI */
    editLayout1 = new QGridLayout;
    editLayout1->setGeometry(QRect(0, 50, 561, 121));

    /* Build userName text field */
    editLayout1->setContentsMargins(0, 0, 0, 0);
    uNameLabel = new QLabel("User Name: ");
    editLayout1->addWidget(uNameLabel, 0, 0, 1, 1);
    uNameEdit = new QLineEdit;
    uNameEdit->setEnabled(false);
    editLayout1->addWidget(uNameEdit, 0, 1, 1, 1);

    /* Build firstName text field */
    fNameLabel = new QLabel("First Name: ");
    editLayout1->addWidget(fNameLabel, 1, 0, 1, 1);
    FNameEdit = new QLineEdit;
    FNameEdit->setEnabled(false);
    editLayout1->addWidget(FNameEdit, 1, 1, 1, 1);

    /* Build middleName text field */
    mNameLabel = new QLabel("Middle Name: ");
    editLayout1->addWidget(mNameLabel, 1, 2, 1, 1);
    MNameEdit = new QLineEdit;
    MNameEdit->setEnabled(false);
    editLayout1->addWidget(MNameEdit, 1, 3, 1, 1);

    /* Build the lastName text field */
    lNameLabel = new QLabel("Last Name: ");
    editLayout1->addWidget(lNameLabel, 1, 4, 1, 1);
    LNameEdit = new QLineEdit;
    LNameEdit->setEnabled(false);
    editLayout1->addWidget(LNameEdit, 1, 5, 1, 1);

    /* Build the department text field */
    deptLabel = new QLabel("Department: ");
    editLayout1->addWidget(deptLabel, 0, 4, 1, 1);
    deptEdit = new QLineEdit;
    deptEdit->setEnabled(false);
    editLayout1->addWidget(deptEdit, 0, 5, 1, 1);

    /* Build the initials text field */
    initLabel = new QLabel("Initials: ");
    editLayout1->addWidget(initLabel, 2, 0, 1, 1);
    InitEdit = new QLineEdit;
    InitEdit->setEnabled(false);
    editLayout1->addWidget(InitEdit, 2, 1, 1, 1);

    /* Build the title text field */
    titleLabel = new QLabel("Title: ");
    editLayout1->addWidget(titleLabel, 2, 2, 1, 1);
    titleEdit = new QLineEdit;
    titleEdit->setEnabled(false);
    editLayout1->addWidget(titleEdit, 2, 3, 1, 1);

    /* Build the preferred name field */
    pNameLabel = new QLabel("Preferred Name: ");
    editLayout1->addWidget(pNameLabel, 2, 4, 1, 1);
    pNameEdit = new QLineEdit;
    pNameEdit->setEnabled(false);
    editLayout1->addWidget(pNameEdit, 2, 5, 1, 1);
    /* End building editLayout1 */

    /* Build the viewOnlyLayout1 */
    viewOnlyLayout1 = new QGridLayout;
    viewOnlyLayout1->setContentsMargins(0, 0, 0, 0);
    viewOnlyLayout1->setGeometry(QRect(0, 320, 571, 134));

    /* Build the officeView text field */
    officeNameView = new QLineEdit;
    officeNameView->setEnabled(false);
    viewOnlyLayout1->addWidget(officeNameView, 0, 1, 1, 1);

    /* Build the officeName label */
    officeLabel = new QLabel("Office Name: ");
    viewOnlyLayout1->addWidget(officeLabel, 0, 0, 1, 1);

    /* Build the officeAddress text box */
    addrLabel = new QLabel("Office Address: ");
    viewOnlyLayout1->addWidget(addrLabel, 1, 0, 1, 1);
    officeAddrDisp = new QTextEdit;
    officeAddrDisp->setEnabled(false);
    viewOnlyLayout1->addWidget(officeAddrDisp, 1, 1, 1, 1);

    /* Build the profilePath text field */
    ppathLabel = new QLabel("Profile Path: ");
    viewOnlyLayout1->addWidget(ppathLabel, 2, 0, 1, 1);
    ppathview = new QLineEdit;
    ppathview->setEnabled(false);
    viewOnlyLayout1->addWidget(ppathview, 2, 1, 1, 1);

    /* Build the homeDirectory text field */
    hDirLabel = new QLabel("Home Directory: ");
    viewOnlyLayout1->addWidget(hDirLabel, 0, 2, 1, 1);
    homeDirView = new QLineEdit;
    homeDirView->setEnabled(false);
    viewOnlyLayout1->addWidget(homeDirView, 0, 3, 1, 1);

    /* Build the companyView text field */
    coLabel = new QLabel("Company: ");
    viewOnlyLayout1->addWidget(coLabel, 1, 2, 1, 1);
    coView = new QLineEdit;
    coView->setEnabled(false);
    viewOnlyLayout1->addWidget(coView, 1, 3, 1, 1);

    /* Build the script path text field */
    spathLabel = new QLabel("Script Path: ");
    viewOnlyLayout1->addWidget(spathLabel, 2, 2, 1, 1);
    scriptPathView = new QLineEdit;
    scriptPathView->setEnabled(false);
    viewOnlyLayout1->addWidget(scriptPathView, 2, 3, 1, 1);
    /* End of viewOnlyLayout1 */

    /* Build the editLayout2 */
    editLayout2 = new QGridLayout;
    editLayout2->setContentsMargins(0, 0, 0, 0);
    editLayout2->setGeometry(QRect(10, 190, 561, 80));

    /* Build the modifyCheckBox */
    ModCheck = new QCheckBox("Modify", this);
    ModCheck->setEnabled(false);
    editLayout2->addWidget(ModCheck, 0, 0, 1, 1);

    /* Build the manager text field */
    managerLabel = new QLabel("Manager: ");
    editLayout2->addWidget(managerLabel, 0, 1, 1, 1);
    managerEdit = new QLineEdit;
    managerEdit->setEnabled(false);
    editLayout2->addWidget(managerEdit, 0, 2, 1, 1);

    /* Build the email text field */
    emailLabel = new QLabel("Email: ");
    editLayout2->addWidget(emailLabel, 0, 3, 1, 1);
    EmailEdit = new QLineEdit;
    EmailEdit->setEnabled(false);
    editLayout2->addWidget(EmailEdit, 0, 4, 1, 1);
    /* End of editLayout2 */

    /* Build the viewOnlyLayout2 */
    viewOnlyLayout2 = new QGridLayout;

    /* Build the password text field */
    passLabel = new QLabel("Password: ");
    passLabel->setGeometry(QRect(290, 475, 53, 16));
    viewOnlyLayout2->addWidget(passLabel, 0, 2, 1, 1);
    passwordView = new QLineEdit;
    passwordView->setEnabled(false);
    passwordView->setGeometry(QRect(364, 475, 110, 20));
    viewOnlyLayout2->addWidget(passwordView, 0, 3, 1, 1);

    /* Build the description text field */
    descView = new QLineEdit;
    descView->setEnabled(false);
    descView->setGeometry(QRect(67, 475, 110, 20));
    viewOnlyLayout2->addWidget(descView, 0, 1, 1, 1);
    descLabel = new QLabel("Description: ");
    descLabel->setGeometry(QRect(1, 475, 60, 16));
    viewOnlyLayout2->addWidget(descLabel, 0, 0, 1, 1);

    /* Build the displayName text field */
    dispNameLabel = new QLabel("Display Name: ");
    dispNameLabel->setGeometry(QRect(290, 535, 68, 16));
    viewOnlyLayout2->addWidget(dispNameLabel, 1, 2, 1, 1);
    dispNameView = new QLineEdit;
    dispNameView->setEnabled(false);
    dispNameView->setGeometry(QRect(364, 535, 110, 20));
    viewOnlyLayout2->addWidget(dispNameView, 1, 3, 1, 1);

    /* Build the homeDrive text field */
    hDriveLabel = new QLabel("Home Drive: ");
    hDriveLabel->setGeometry(QRect(1, 505, 59, 16));
    viewOnlyLayout2->addWidget(hDriveLabel, 1, 0, 1, 1);
    hDriveView = new QLineEdit;
    hDriveView->setEnabled(false);
    hDriveView->setGeometry(QRect(67, 535, 110,20));
    viewOnlyLayout2->addWidget(hDriveView, 1, 1, 1, 1);

    // Some Layouts will not be shown
    mainLayout->addLayout(editLayout1, 1, 0, 1, 3);
    mainLayout->addLayout(editLayout2, 2, 0, 1, 3);
    mainLayout->addLayout(viewOnlyLayout1, 3, 0, 1, 3);
    mainLayout->addLayout(viewOnlyLayout2, 4, 0, 1, 3);

    /* Populate the GUI on end of construction */
    displayEdits(calling_prog->dispPersonList());
}

/***********************************************************************
* Module Name: displayEdits
* Original Author: Will
* Module Creation Date: May 11, 2012
* Description: This function displays all of the user information on to
*              the GUI for viewing.
* Calling Arguments:
* Name   Input/Output  Type      Description
* users  Input         userList  The pointer to the linked list of user
*                                information.
* Required Files/Databases:
*  None
* Non System Routines Called:
* Name Description
* disp...
* Return Value:
* Type Description
*  None
* Error Codes/Exceptions:
*  None
* OS Specific Assumptions if any:
* Local Variables:
* Type   Name        Description
* char*  place       User's office name.
* char*  streetAddr  Office's street Address.
* char*  city        Office's city.
* char*  state       Office's state.
* char*  zip         Office's zip code.
* char*  country     Office's country.
* char*  firstName   User's first name.
* char*  middleName  User's middle name.
* char*  lastName
* char*  prefName
* char*  initials
* char*  userName
* char*  email
* char*  title
* char*  dept
* char*  password
* char*  mod
* char*  manager
* char*  desc
* char*  scriptPath
* char*  homeDrive
* char*  profilePath
* char*  homeDir
* char*  UPN
* char*  coName
* Global Variables Used:
* Type Name Origin Description
* Constant and Macro Substitutions:
* Name Header File Description
* Modification History:
* Date Developer Action
***********************************************************************/
void UserViewGUI::displayEdits(userList users) {
    current_person = users; // Save the pointer to the user objects

    /* Clear the local variables for the display of the fields */
    char * place = NULL;
    char * streetAddr = NULL;
    char * city = NULL;
    char * state = NULL;
    char * zip = NULL;
    char * country = NULL;
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
    char * manager = NULL;
    char * desc = NULL;
    char * scriptPath = NULL;
    char * homeDrive = NULL;
    char * profilePath = NULL;
    char * homeDir = NULL;
    char * UPN = NULL;
    char * coName = NULL;

    /* Retreive person's office info */
    place = dispOfficeName(users->user);
    streetAddr = dispStreetAddr(users->user);
    city = dispCity(users->user);
    zip = dispZip(users->user);
    state = dispState(users->user);
    country = dispCountry(users->user);
    /* end person's office info */

    /* Display the office info */
    officeNameView->setText(place);
    officeAddrDisp->clear();
    officeAddrDisp->append(streetAddr);
    officeAddrDisp->append(city);
    officeAddrDisp->append(state);
    officeAddrDisp->append(zip);
    officeAddrDisp->append(country);

    /* Retrieve person's AD attributes */
    scriptPath = dispScriptPath(users->user);
    homeDrive = dispHomeDrive(users->user);
    profilePath = dispProfilePath(users->user);
    homeDir = dispHomeDir(users->user);
    UPN = dispUPN(users->user);
    coName = dispCompanyName();
    /* end person's AD attributes */

    /* Display the AD attributes */
    scriptPathView->setText(scriptPath);
    ppathview->setText(profilePath);
    hDriveView->setText(homeDrive);
    homeDirView->setText(homeDir);
    coView->setText(coName);

    /* Retrieve the Person's name */
    firstName = dispFirstName(users->user);
    middleName = dispMiddleName(users->user);
    lastName = dispLastName(users->user);
    prefName = dispPrefferedName(users->user);
    initials = dispInitials(users->user);
    userName = dispUserName(users->user);
    email = dispEmail(users->user);
    title = dispTitle(users->user);
    dept = dispDept(users->user);
    password = dispPassword(users->user);
    mod = dispMod(users->user);
    manager = dispManager(users->user);
    desc = dispDesc(users->user);
    /* end person's name info */

    /* Display all user attributes */
    uNameEdit->setText(userName);
    FNameEdit->setText(firstName);
    MNameEdit->setText(middleName);
    LNameEdit->setText(lastName);
    pNameEdit->setText(prefName);
    InitEdit->setText(initials);
    deptEdit->setText(dept);
    EmailEdit->setText(email);
    titleEdit->setText(title);
    descView->setText(desc);
    managerEdit->setText(manager);
    passwordView->setText(password);

    /* Retrieve the modify attribute and display */
    if (!strcasecmp(mod, "true")) ModCheck->setChecked(true);
    else ModCheck->setChecked(false);
}

/********** Template for functions below **********************/
/***********************************************************************
* Module Name:
* Original Author:
* Module Creation Date:
* Description:
* Calling Arguments:
* Name Input/Output Type Description
* Required Files/Databases:
* Non System Routines Called:
* Name Description
* Return Value:
* Type Description
* Error Codes/Exceptions:
* OS Specific Assumptions if any:
* Local Variables:
* Type Name Description
* Global Variables Used:
* Type Name Origin Description
* Constant and Macro Substitutions:
* Name Header File Description
* Modification History:
* Date Developer Action
***********************************************************************/
