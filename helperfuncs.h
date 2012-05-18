/* 
 * File:   helperfuncs.h
 * Author: Will
 *
 * Created on January 6, 2012, 4:59 PM
 */

/* helperfuncs.h: This file defines the functions that use standard library types
 * and functionalities. This helps with being able to modularize the code for
 * other functions in the future that require these functionalities.
 */

#ifndef HELPERFUNCS_H
#define	HELPERFUNCS_H

/* Split: tokenizes input by using delim,
*   the function returns a NULL terminated array of NULL terminated strings
*   or a NULL pointer, if memory cannot be allocated for the array.
*/
char ** Split(const char * input, const char delim);

/*  emptyStr: returns the string "*" when the Split function encounters
*   an empty token, thus preventing Segmentation and/or Protection Faults.
*   Prints error message and returns NULL if string cannot be generated.
*/
char * emptyStr(void);

/*  fillStr: returns the string indicated by the start pointer, sPtr, and
*   end pointer, ePtr. The string is trimmed of leading whitespaces and trailing
*   whitespaces before returned to the caller. Prints error message and returns
*   NULL if string cannot be generated.
*/
char * fillStr(char * sPtr, char* ePtr, const char delim);

/* readLine: returns a trimmed string to caller, given a limit.
 */
char * readLine(FILE * stream, unsigned int limit);

/* getOutFile: retrieves the output file from the user. Returns the file pointer.
 */
FILE * getOutFile();

#endif	/* HELPERFUNCS_H */

