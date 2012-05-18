#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helperfuncs.h"
const int BUFSIZE = 101; /* buffer size */

/* helperfuncs.c: This file implements the functions that use standard library types and
 * functionalities. This helps with being able to modularize the code for other
 * functions in the future that require these functionalities.
 */

/* Split: tokenizes input by using delim,
*   the function returns a NULL terminated array of NULL terminated strings
*   or a NULL pointer, if memory cannot be allocated for the array.
*/
char ** Split(const char * input, const char delim) {
/* what if the string doesn't have anything to tokenize ? */
    char * inStr = NULL;   /* Input stream pointer */
    char * prevStr = NULL; /* Previous occurance pointer */
    char ** output = NULL; /* Array of NULL terminated strings */
    unsigned int i = 0; /* Elements in the output array */

    /* Initialize the pointers so that the pointers point
    *   to the beginning of the string. */
    prevStr = (char *) input;
    inStr = prevStr;

    /* Initialize the output array */
    output = (char **) malloc(sizeof(char **));
    if (!output) {
        printf("Split_error: Cannot create output array.\r\n");
        fflush(stdout);
        return NULL; /* malloc failed */
    }

    /* Line tokenizing loop: This loop will check for empty fields,
     * and correct that input, thus avoiding segmentation faults
     * when the buffer normalizing array is accessed.
     */
     while(*inStr){
     /* Check for delimeter */
         if(*inStr == delim){
             /* The input pointer matches the delimter */
             if(inStr - prevStr < 1){ /* Check to see if the string is empty */
                 /* Empty string case */
                 output[i] = emptyStr();
             }
             else { /* Unempty string case */
                 output[i] = fillStr(prevStr, inStr-1, delim);
             }
             /* Create another array element for strings to reside */
             ++i; /* add another element to output ** */
             output = (char **) realloc(output, (i+1) * sizeof(char **));
             if(!output) {
                 printf("Split_error: Cannot resize output array.\r\n");
                 fflush(stdout);
                 return NULL;
             }
             /* Set pointers for the next token */
             inStr++;
             prevStr = inStr;
         }
         /* check for the end of the buffer */
         else if((*inStr == '\r') || (*inStr == '\n') || (*inStr == '\0') ){
             /* We reached the end of the buffer, the field could be empty */
             if(inStr - prevStr < 1) output[i] = emptyStr(); /* Empty string case */

             else output[i] = fillStr(prevStr, inStr-1, delim); /* Unempty string case */
             *inStr = 0; /* Break out of the tokenization loop */
         }
         /* for all other inputs */
         else inStr++; /* Keep moving along the input string */
     } /* End of tokenization loop */

    /* Terminate the output array with a NULL */
    ++i; /* add another element to output ** */
    output = (char **) realloc(output, (i+1) * sizeof(char **));
    if(!output) {
        printf("Split_error: Cannot resize output array.\r\n");
        fflush(stdout);
        return NULL;
    }
    output[i] = NULL;
    return output;
}


/*  emptyStr: returns the string "*" when the Split function encounters
*   an empty token, thus preventing Segmentation and/or Protection Faults.
*   Prints error message and returns NULL if string cannot be generated.
*/
char * emptyStr(void) {
    int i; /* counter vars */
    char * s = NULL; /* clear the string */
    s = (char *) malloc(2 * sizeof(char)); /* string to be returned */
    
    /* Check if malloc failed */
    if(!s) {
        printf("emptyStr_error: Cannot allocate string.\r\n");
        fflush(stdout);
        return NULL; /* malloc failed */
    }
    /* Clear string out */
    for(i = 0; i < 2; ++i){
        s[i] = 0;
    }
    /* Fill the array with a non-NULL item */
    return strncpy(s, "*", strlen("*"));
}

/*  fillStr: returns the string indicated by the start pointer, sPtr, and
*   end pointer, ePtr. The string is trimmed of leading whitespaces and trailing
*   whitespaces before returned to the caller. Prints error message and returns
*   NULL if string cannot be generated.
*/
/* FIX FOR 1 CHARACTER ALGORITHMS */
char * fillStr(char * sPtr, char* ePtr, const char delim) {
    char * s = NULL; /* string to be returned after trimming and trailing operations on string */
    const int SPACER = 2; /* Space between last char and NULL */
    /* Check if both pointers are not NULL and trim the respective whitespaces */
    if(sPtr && ePtr) {
        while(isspace(*sPtr)){
           if(sPtr < ePtr) ++sPtr;
           else break;
        }
	while(isspace(*ePtr)) {
            if (ePtr > sPtr) --ePtr;
            else break;
        }
    }
    else {
        printf("fillStr_error: One of the arguments are NULL, recheck function call.\r\n");
        fflush(stdout);
        return NULL; /* either pointer is NULL */
    }

    /* Check to see if we overran pointers in our token */
    if((ePtr-sPtr) < 0) return emptyStr(); /* Gracefully handles fields that are only spaces */
    /* Single character token fix */
    else if (((ePtr-sPtr) == 0) && (*ePtr == delim))  return emptyStr();
    
    /* Allocate space for new string */
    s = (char *) malloc( (ePtr-sPtr+SPACER) * sizeof(char));
    if(!s) {
        printf("fillStr_error: Cannot allocate string.\r\n");
        fflush(stdout);
        return NULL;
    }

    /* Clear out garbage in new space */
    memset(s, 0, (ePtr-sPtr+SPACER) * sizeof(char));

    /* Copy string data to allocated space,
     * which is the difference of the end and start ptrs plus SPACER - 1 */
    return (char *) memmove(s, sPtr, (ePtr-sPtr+1) * sizeof(char));
}

/* readLine: returns a trimmed string to caller, given a limit.
 */
char * readLine(FILE * stream, unsigned int limit){
    char * buffer = (char *) malloc(limit*sizeof(char)); /* buffer array */
    char * endBuffer = NULL; /* this pointer will point the end of the buffer */
    char * output = NULL;
    const int SPACER = 2; /* the space between the last char and NULL */

    if (!buffer) {
        printf("readLine_error: Could not allocate buffer.\r\n");
        fflush(stdout);
        return NULL; /* malloc failed */
    }
    /* clear the garbage in the buffer */
    memset(buffer, 0, limit*sizeof(char));
    fgets(buffer, limit, stream);
    endBuffer = &buffer[(int)strlen(buffer)-1];

    while(isspace(*buffer)) {
        if( buffer < endBuffer)++buffer; /* trim the leading white space*/
        else break;
    }
    while(isspace(*endBuffer)){
        if(endBuffer > buffer) --endBuffer; /* trim the ending white space*/
        else break;
    }
    if(endBuffer-buffer <= 0){
        return NULL; /* perhaps there is an implementation specific reason
                      * for only whitespace input */
    }
    else {
        output = (char *) malloc((endBuffer - buffer + SPACER)* sizeof(char));
        if(!output) {
            printf("readLine_error: Could not allocate output.\r\n");
            fflush(stdout);
            return NULL; /* malloc failed */
        }

        /* Clear garbage out of output string */
        memset(output, 0, (endBuffer-buffer+SPACER)*sizeof(char));

        /* Copy string data to allocated space, which is the difference
         of the end and start ptrs plus SPACER - 1 */
        memmove(output, buffer, (endBuffer - buffer + 1)*sizeof(char));
        free(buffer);   /* memory leak prevention */
        buffer = NULL; /* terminates buffer */
        return output;
    }
}

/* getOutFile: retrieves the output file from the user. Returns the file pointer.
 */
FILE * getOutFile() {
    char * out; /* The output file that will be returned */
    printf("Enter the path or filename of out file:\r\n");
    fflush(stdout);

    /* Implementation dependant! */
    out = readLine(stdin, BUFSIZE);
    return fopen(out, "w");
}
