/*
 * File:   main.cpp
 * Author: Will
 *
 * Created on January 19, 2012, 10:39 AM
 */

#include <QtGui/QApplication>
#include <stdlib.h>
#include "adprog.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    // create and show your widgets here
    ImportUsers * obj;
    try {
        obj = new ImportUsers();
    }
    catch (int exception) {
        return EXIT_FAILURE;
    }

    obj->show();
    
    return app.exec();
}
