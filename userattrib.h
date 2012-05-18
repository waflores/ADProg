/*
 * File: userattrib.h
 * Author: Will Flores
 * Usage: Implemented by userattrib.c
 * Description: This file specifies structs, typedefs, and function prototypes
 *      that create and manipulate the records for the importation program.
 * Environment: Windows 7, 64 bit build
 * Notes: 
 * Revisions: NONE
 * Created on January 18, 2012
 */

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef USERATTRIB_H
#define	USERATTRIB_H

/* Definition of return values for functions */
#define FAIL 0
#define SUCCESS 1

/* The specification of the User type */
typedef struct userBin * User;

/* User linked list node */
struct userNode {
    User user; /* User's information */
    struct userNode * prev; /* Previous user */
    struct userNode * next; /* Next user */
};

/* linked list of users */
typedef struct userNode * userList;

/* The implementation of the locations */
typedef struct location * Location;

/* Location linked list node */
struct locNode{
    Location loc;
    struct locNode * next;
};

/* linked list of locations */
typedef struct locNode * locList;

/* The implementation of the particulars for files in the future */
typedef struct particulars * Particulars;

/* Active Directory linked list */
typedef struct ADlist * ADList;

/*
 * FUNCTIONS
 */

/* create a new user and add to master list;
 * if another user with the same username exists
 * don't create it and return NULL
 */
User addOneUser(char ** properties);

/* get list of all Users */
userList allUsers();
/* A NEW User list is going to be generated since the user interface will
 * delete this list when it's done using it.
 */

/* query functionality -- finds all Users in the Global
 * user list that match the search critieria.
 *
 * Any of these parameters can be NULL, which means that
 * the value is a wildcard.
 */
userList findUsers();
/* A NEW User list is going to be generated since the user interface will
 * delete this list when it's done using it.
*/

/* create a bunch of users from a csv file stream
 */
userList batchImport(const char * fileStream);

Location findLocation(const char * place, const locList locs);

Particulars createMasterParticulars(void);
ADList createMasterADList(void);

/* getSettings: will take in a file and set the appropriate attributes 
 * for the users to be imported in the program. Prints an error message
 * and returns 0 if settings importation fails or is halted. The 
 * function returns 1 on success.
 */
int getSettings(const char * file, const char * prog);

/*int errorCheck (ADList, Location, Particulars);*/

int appendToMasterLocList(Location place, locList * Master);
int appendToMasterUsers(User person, userList * Master);

int exportUsers(userList users, const char * file);
int getuserCount(void);
userList getMasterUserList(void);

userList deleteOneUser(userList users);

int deleteAllUsers(userList users);
/* ACCESSOR FUNCTIONS */
char * dispFirstName(User person);
char * dispMiddleName(User person);
char * dispLastName(User person);
char * dispPrefferedName(User person);
char * dispInitials(User person);

char * dispUserName(User person);
char * dispEmail(User person);
char * dispTitle(User person);
char * dispDept(User person);
char * dispPassword(User person);
char * dispMod(User person);
char * dispManager(User person);
char * dispDesc(User person);

/* office */
char * dispPlace(Location loc);
char * dispOfficeName(User person);
char * dispStreetAddr(User person);
char * dispCity(User person);
char * dispState(User person);
char * dispZip(User person);
char * dispCountry(User person);

/* AD attributes */
char * dispScriptPath(User person);
char * dispHomeDrive(User person);
char * dispProfilePath(User person);
char * dispHomeDir(User person);
char * dispUPN(User person);
char * dispCompanyName(void);

char * changeUserName(const char * username, User person);
char * changeFirstName(const char * firstname, User person);
char * changeLastName(const char * lastname, User person);
char * changeMiddleName(const char * middlename, User person);
char * changeInitials(const char * initials, User person);
char * changeTitle(const char * title, User person);
char * changeDepartment(const char * department, User person);
char * changePreferredName(const char * prefname, User person);
Location changeOfficeName(const char * officename, User person);
char * changeProfilePath(const char * path, User person);
char * changeHomeDirectory(const char * homedir, User person);
char * changeEmail(const char * email, User person);
char * changePassword(const char * password, User person);

#endif	/* USERATTRIB_H */
#ifdef __cplusplus
}
#endif
