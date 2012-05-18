/*
 * File: main.cpp
 * Author: Will Flores
 * Usage: 
 * Description: This file defines the main function for the program to enter.
 * Environment: Windows 7, 64 bit build
 * Notes:
 * Revisions: NONE
 * 
 * Created on January 19, 2012, 10:39 AM
 */

#include <QtGui/QApplication>
#include <stdlib.h>
#include "adprog.h"

 /***********************************************************************
* Module Name: main
* Original Author: Will
* Module Creation Date: January 19, 2012
* Description: This is the main function for the AD Program.
*
* Calling Arguments:
* Name   Input/Output  Type         Description
* argc   Input         int          The count of the arguments passed into
*                                   the program.
* argv   Input         char**       The array of strings of arguments.
*
* Required Files/Databases:
*  None
*
* Non System Routines Called:
* Name           Description
* ImportUsers    Loads the constructor for the AD Program.
*
* Return Value:
* Type           Description
* int            The status to the operating system when the program exits.
*
* Error Codes/Exceptions:
*  EXIT_SUCCESS - When the program exits successfully, returns a 0.
*  EXIT_FAILURE - When the program is terminated before reaching the main
*      window.
*
* OS Specific Assumptions if any:
*  None
* 
* Local Variables:
* Type          Name Description
* ImportUsers*  obj  The constructor for the AD program to be loaded.
* 
* Global Variables Used:
* Type Name Origin Description
*  NONE
* Constant and Macro Substitutions:
* Name Header File Description
* 
* Modification History:
* Date Developer Action
***********************************************************************/
int main(int argc, char *argv[]) {
    /* The entry point for the Qt Gui Program. */
    QApplication app(argc, argv);
    
    /* create and show your widgets here */
    ImportUsers * obj;
    
    /* Load main window for program */
    try {
        obj = new ImportUsers();
    }
    catch (int exception) {
        /* The program ternminated prematurely. */
        return EXIT_FAILURE;
    }
    /* Show the GUI */
    obj->show();
    
    return app.exec();
}
