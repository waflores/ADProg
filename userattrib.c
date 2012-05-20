/*
 * File: userattrib.c
 * Author: Will Flores
 * Usage: This is the implementation of the Active Directory importation program.
 * Description: Implementation of 'userattrib.h' which a programmer can modify
 *      in the future.
 * Environment: Windows 7, 64 bit build
 * Notes:
 * Revisions: NONE
 * Created on January 18, 2012
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "userattrib.h"
#include "helperfuncs.h"

locList MasterLocs;     /* Global Locations Linked List */
ADList MasterADlist;    /* Master Active Directory information */
Particulars MasterPart; /* Master Particulars information */
userList MasterUsers; /* Global Users Linked List */
int userCount = 0; /* Count user nodes */
#define MAXLEN 201 /* define length of string buffer */
static const int INCOLUMNS = 11; /* define the number of columns in the input file */
static const int OUTCOLUMNS = 26; /* define the number of columns in the output file */

/* User's name */
struct name{
    char * f_name;  /* first name */
    char * m_name;  /* middle name */
    char * L_name;  /* last name */
    char * pref_name;   /* preferred name */
    char * initials;    /* user's initials */
};

/* One user record */
struct userBin {
    struct name User;   /* user's name information */
    struct location * loc;  /* user's location information */
    ADList attrib;  /* user's Active Directory information */
    char * userName;    /* user's username */
    char * email;   /* user's email address */
    char * title;   /* user's title */
    char * dept;    /* user's department */
    char * password;    /* user's password*/
    char * mod; /* user's modify attribute (True or False) */
    char * manager; /* user's manager */
    char * desc;    /* description for Active Directory listing */
};

/* Company's information from the settings file */
struct particulars{
    char * companyName; /* Name of the company */
    char * desc;        /* Master description for users from settings file */
};

/* User's Active directory information */
struct ADlist{
    char * scriptPath;  /* file for script path */
    char * homeDrive;   /* user's home drive */
    char * profilePath; /* user's profile path */
    char * homeDir;     /* user's home directory */
    char * UPN;         /* user principal name: "username@domainName" */
};

/* Company location information */
struct location{
    char * place;   /* the name of the location that's being documented */
    char * sAddr;   /* the street name of the location */
    char * sAddr2;  /* the second street name if needed */
    char * city;    /* the city name of the location */
    char * state;   /* the state name or abbreviation of the location */
    int zip;        /* zip code of the location */
    char * country; /* country where the location resides */
};

int getuserCount(void) {
	return userCount;
}

userList getMasterUserList(void){
    return MasterUsers;
}

/* getSettings: will take in a file and set the appropriate attributes 
 * for the users to be imported in the program. Prints an error message
 * and returns 0 if settings importation fails or is halted. The 
 * function returns 1 on success.
 */
int getSettings(const char * file, const char * prog){
    FILE * stream = NULL;   /* Settings file stream */
    char buffer[MAXLEN];    /* Text buffer */
    char * inStr;           /* Text parsing pointer */
    int fieldCount;         /* Count the Fields filled in MasterLocs */
    Location place;         /* new location information */

    MasterLocs = NULL;      /* Locations Linked list = empty */
    stream = fopen(file, "rb"); /* Open the settings file */
    
    /* Open the file stream and check for correctness */
    if (!stream) return FAIL;
    
    /* Create the Particulars List */
    MasterPart = createMasterParticulars();
    if (!MasterPart){
        printf("getSettings_error: Master Particulars List was not created.\r\n");
        fflush(stdout);
        return FAIL; /* malloc failed */
    }

    /* Create the Master Active Directory attributes list */
    MasterADlist = createMasterADList();
    if(!MasterADlist){
        printf("getSettings_error: Master Active Directory List was not created.\r\n");
        fflush(stdout);
        return FAIL;
    }

    /* Settings file opening successful - start importation process */
    while(fgets(buffer, MAXLEN, stream)){ /* get line of info from settings file */
        /* Normalize input */
        inStr = strtok(buffer, "\r");
        if(!inStr) inStr = strtok(buffer, "\n");

        /* Parse the settings file */
        inStr = strtok(buffer, ": ");
        if (strcasecmp(buffer, "//") == 0){
            /* We reached a comment in the file, disregard the rest of the line */
            continue;
        }
        else if (strcasecmp(buffer, "Company") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the Company Name */
            MasterPart->companyName = (char *)malloc(strlen(inStr)+1);
            strcpy(MasterPart->companyName, inStr);
        }
        else if(strcasecmp(buffer, "Description") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the description */
            MasterPart->desc = (char *)malloc(strlen(inStr)+1);
            strcpy(MasterPart->desc, inStr);
        }
        else if(strcasecmp(buffer, "Script_Path") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the Script Path */
            MasterADlist->scriptPath = (char *)malloc(strlen(inStr)+1);
            strcpy(MasterADlist->scriptPath, inStr);
        }
        else if(strcasecmp(buffer, "Home_Drive") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the Home Drive */
            MasterADlist->homeDrive = (char *) malloc(strlen(inStr)+1);
            strcpy(MasterADlist->homeDrive, inStr);
        }
        else if(strcasecmp(buffer, "Profile_Path") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the Profile path */
            MasterADlist->profilePath = (char *)malloc(strlen(inStr)+1);
            strcpy(MasterADlist->profilePath, inStr);
        }
        else if(strcasecmp(buffer, "Home_Directory") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the Home Directory */
            MasterADlist->homeDir = (char *)malloc(strlen(inStr)+1);
            strcpy(MasterADlist->homeDir, inStr);
        }
        else if(strcasecmp(buffer, "User_Principal_Name") == 0){
            inStr = strtok(NULL, "\0");
            /* Establish the Domain Name */
            MasterADlist->UPN = (char *)malloc(strlen(inStr)+1);
            strcpy(MasterADlist->UPN, inStr);
        }
        else if(strcasecmp(buffer, "Start_Location") == 0){
            /* Create a new location bin */
            place = (Location)malloc(sizeof(struct location));
            if(!place) { /* error checking code */;
                printf("getSettings_error: a Location could not be allocated.");
                fflush(stdout);
                return FAIL;
            }
            fieldCount = 0; /* initialize the field count */
            while(fgets(buffer, MAXLEN, stream)){
                /* Normalize input */
                inStr = strtok(buffer, "\r");
                if(!inStr) inStr = strtok(buffer, "\n");

                /* Error checking code */
                if(strcasecmp(buffer, "End_Location") == 0) break;
                /* Populate the fields */
                switch(fieldCount){
                    case 0: /* Establish the Location's Abreviation */
                        place->place = (char *)malloc(strlen(buffer)+1);
                        strcpy(place->place, buffer);
                        fieldCount++;
                        break;
                    case 1: /* Establish the Street Address for the Location */
                        place->sAddr = (char * )malloc(strlen(buffer)+1);
                        strcpy(place->sAddr, buffer);
                        fieldCount++;
                        break;
                    case 2: /* populate the City and State info */
                        inStr = strtok(buffer, ",");
                        place->city = (char *)malloc(strlen(inStr)+1);
                        strcpy(place->city, inStr);
                        inStr = strtok(NULL, " ");
                        place->state = (char *)malloc(strlen(inStr)+1);
                        strcpy(place->state, inStr);
                        inStr = strtok(NULL, "\0");
                        place->zip = atoi(inStr);
                        fieldCount++;
                        break;
                    case 3: /* Establish the Location's Country */
                        place->country = (char *)malloc(strlen(buffer)+1);
                        strcpy(place->country, buffer);
                        break;
                    default:    /* Break out of populating the Location fields */
                        break;
                }
            }
            /* End of location retrieval append to Global list of locations */
            if(appendToMasterLocList(place, &MasterLocs) != SUCCESS) {
                printf("getSettings_error: %s was not appended to the Master Location List.\r\n", place->place);
                fflush(stdout);
                return FAIL;
            }
        }
    }
    /* error checking code for settings.dat, will showup in stdout for corrections */
    fclose(stream); /* Close the settings file */
    return SUCCESS;
}

/* appendToMasterLocList: This function will append a Location Node to a
 * given Master Locations List. The function returns FAIL on failure and SUCCESS
 * when it successfully appends a node to the linked list.
 */
int appendToMasterLocList(Location place, locList * Master){
    locList p = NULL;   /* The location node pointer */
    /* Create a new Linked list node to for place to be in */
    locList newList = (locList)malloc(sizeof(struct locNode));

    /* Check if new node has been created */
    if(!newList){
        printf("appendToMasterLocList_error: Cannot create a node for the Locations Linked List.\r\n");
        fflush(stdout);
        return FAIL;
    }

    newList->loc = place; /* connect the location with its node */
    newList->next = NULL; /* terminate the node */

    p = *Master; /* allows for traversal of Master list */
    if(p){
        while(p->next != NULL) p = p->next;
        p->next = newList; /* append the location to the end of the list */
    }
    else{
        *Master = newList; /* create head of list */
    }
    return SUCCESS;
}

/* findLocation: This function will return the location information for a user
 * given a place name. The function returns NULL if the location is not found.
 */
Location findLocation(const char * place, const locList locs){
    if (!place || !strlen(place)) return NULL;
    locList p = locs;
    /* Start with the begining of the Locations linked list */
    while(p){
        /* Try to match the place name with the ones in the linked list */
        if(strcasecmp(dispPlace(p->loc), place) == 0){
            /* We have a match! */
            return p->loc;
        }
        /* We didn't find it, move to the next one */
        p = p->next;
    }
    /* Either the Locations Linked List doesn't exist or we didn't get a match */
    return NULL;
}

/* errorCheck: This function will check whether or not critical parts of the settings
 * file were imported into the program's memory. This allows the user to input
 * the information before importing users.
 * The function prints and error returns Zero for error handling.
 */
/*
int errorCheck(ADList ADlist, Location Location, Particulars Particulars){
    char msg[] = "Check settings file to see if attributes were established.";
    if(!ADList) {
        printf("errorCheck_error: Master Active Directory list was not created. %s\r\n", msg);
        fflush(stdout);
        return FAIL;
    }
    if(!Location) {
        printf("errorCheck_error: Master Locations list was not created. %s\r\n", msg);
        fflush(stdout);
        return FAIL;
    }
    if(!Particulars) {
        printf("errorCheck_error: Master Particulars list was not created. %s\r\n", msg);
        fflush(stdout);
        return FAIL;
    }
    if(!ADlist->UPN);
    if(!ADlist->homeDir);
    if(!ADlist->homeDrive);
    if(!ADlist->profilePath);
    if(!ADlist->scriptPath);

    if(!Location->city);
    if(!Location->country);
    if(!Location->place);
    if(!Location->sAddr);
    if(!Location->state);

    if(!Particulars->companyName);
    if(!Particulars->desc);

    return SUCCESS;
}
 */

/* dispUserName: This function returns the User's user name */
char * dispUserName(User person){
    if (person) return person->userName;
    else return NULL;
}

/* dispEmail: This function returns the User's email address */
char * dispEmail(User person){
    if (person) return person->email;
    else return NULL;
}

/* disTitle: This function returns the User's title */
char * dispTitle(User person){
    if (person) return person->title;
    else return NULL;
}

/* dispDept: This function returns the User's department */
char * dispDept(User person){
    if (person) return person->dept;
    else return NULL;
}

/* dispPassword: This function returns the User's password */
char * dispPassword(User person){
    if (person) return person->password;
    else return NULL;
}

/* dispMod: This function returns the User's Modification attributes */
char * dispMod(User person){
    if (person) return person->mod;
    else return NULL;
}

/* dispManager: This function returns the User's manager */
char * dispManager(User person){
    if (person) return person->manager;
    else return NULL;
}

/* dispDesc: This function returns the User's description */
char * dispDesc(User person){
    if (person) return person->desc;
    else return NULL;
}
/* dispPlace: This function returns the User's location */
char * dispPlace(Location loc) {
    if (loc) return loc->place;
    else return NULL;
}

char * dispOfficeName (User person) {
    if (person && (person->loc)) return person->loc->place;
    else return NULL;
}

char * dispStreetAddr(User person) {
    if (person && (person->loc)) return person->loc->sAddr;
    else return NULL;
}

char * dispCity(User person) {
    if (person && (person->loc)) return person->loc->city;
    else return NULL;
}

char * dispState(User person) {
    if (person && (person->loc)) return person->loc->state;
    else return NULL;
}

char * dispZip(User person) {
    if (person && (person->loc)) {
        char * buff = (char *) malloc(sizeof(char) * 6); /* size of zip code */
        int counter;
        for (counter = 0; counter < 6; counter++) buff[counter] = 0; /* clears buffer */
        int zip = person->loc->zip;
        sprintf(buff, "%d", zip);
        return buff;
    }
    else return NULL;
}

char * dispCountry(User person) {
    if (person && (person->loc)) return person->loc->country;
    else return NULL;
}

char * dispFirstName(User person) {
        if (person /*&& (person->User)*/) return person->User.f_name;
        else return NULL;
}
char * dispMiddleName(User person) {
        if (person /*&& (person->User)*/) return person->User.m_name;
        else return NULL;
}

char * dispLastName(User person) {
        if (person /*&& (person->User)*/) return person->User.L_name;
        else return NULL;
}

char * dispPrefferedName(User person) {
        if (person /*&& (person->User)*/) return person->User.pref_name;
        else return NULL;
}

char * dispInitials(User person) {
        if (person /*&& (person->User)*/) return person->User.initials;
        else return NULL;
}
char * dispScriptPath(User person) {
    if (person && (person->attrib)) return person->attrib->scriptPath;
    else return NULL;
}
char * dispHomeDrive(User person) {
    if (person && (person->attrib)) return person->attrib->homeDrive;
    else return NULL;
}

char * dispProfilePath(User person) {
    if (person && (person->attrib)) return person->attrib->profilePath;
    else return NULL;
}

char * dispHomeDir(User person) {
    if (person && (person->attrib)) return person->attrib->homeDir;
    else return NULL;
}

char * dispUPN(User person) {
    if (person && (person->attrib)) return person->attrib->UPN;
    else return NULL;
}

char * dispCompanyName(void) {
    if (MasterPart) return MasterPart->companyName;
    else return NULL;
}

/* createMasterParticulars: This function will allocate a Master Particulars 
 * list. The function returns NULL on failure.
 */
Particulars createMasterParticulars(void){
    Particulars p = (Particulars) malloc(sizeof(struct particulars));
    /* Check if we created a Master Particulars list */
    if (!p){
        printf("createMasterParticulars_error: Cannot create Master Particulars List.\r\n");
        fflush(stdout);
        return (void *) FAIL; /* malloc failed */
    }
    return p;
}

/* createMasterADList: This function will allocate a Master AD list. The
 * function returns NULL on failure.
 */
ADList createMasterADList(void) {
    ADList p = (ADList) malloc(sizeof(struct ADlist));
    /* Check if we created a Master AD list */
    if(!p){
        printf("createMasterADList_error: Cannot create Master Active Directory List.\r\n");
        fflush(stdout);
        return (void *) FAIL;
    }
    return p;
}

/* exportUsers: This function will take all the information in from the Master
 * linked lists and write them to a file. This function destroys all information
 * in the userList it is passed. The function returns FAIL on failure and SUCCESS
 * on successfully writing to the file.
 */
int exportUsers(userList users, const char * file){
    Location office;
    struct name person;
    ADList ad_attrib;
    //userList tmp;
    char * userName;
    char * email;
    char * title;
    char * dept;
    char * password;
    char * mod;
    char * manager;
    char * desc;
    char * ptr;
    FILE * outFile = NULL;
    int columnCount;
    char buffer[MAXLEN];

    outFile = fopen(file, "wb");
    fprintf(outFile,"sAMAccountName,givenName,sn,mail,title,department,physicalDeliveryOfficeName,password,PreferredName,MiddleName,Modify,");
    fprintf(outFile, "l,st,streetAddress,postalCode,c,scriptPath,company,description,homeDrive,cn,displayName,profilePath,");
    fprintf(outFile, "homeDirectory,manager,initials\r\n");
    while(users){
        /* Get all user attributes */
        office = users->user->loc;
        person = users->user->User;
        ad_attrib = users->user->attrib;
        userName = dispUserName(users->user);
        email = dispEmail(users->user);
        title = dispTitle(users->user);
        dept = dispDept(users->user);
        password = dispPassword(users->user);
        mod = dispMod(users->user);
        manager = dispManager(users->user);
        desc = dispDesc(users->user);

        for (columnCount = 0; columnCount < OUTCOLUMNS; columnCount++){
            switch(columnCount){
                case 0:
                    ptr = userName;
                    break;
                case 1:
                    ptr = person.f_name;
                    break;
                case 2:
                    ptr = person.L_name;
                    break;
                case 3:
                    ptr = email;
                    break;
                case 4:
                    ptr = title;
                    break;
                case 5:
                    ptr = dept;
                    break;
                case 6:
                    if(office) ptr = office->place;
                    else ptr = NULL;
                    break;
                case 7:
                    ptr = password;
                    break;
                case 8:
                    ptr = person.pref_name;
                    break;
                case 9:
                    ptr = person.m_name;
                    break;
                case 10:
                    ptr = mod;
                    break;
                case 11:
                    if (office) ptr = office->city;
                    else ptr = NULL;
                    break;
                case 12:
                    if (office) ptr = office->state;
                    else ptr = NULL;
                    break;
                case 13:
                    if (office) ptr = office->sAddr;
                    else ptr = NULL;
                    break;
                case 14: /* zip code */
                    if (office) {
                        memset(buffer, 0, MAXLEN);
                        sprintf(buffer, "%d", office->zip);
                        ptr = buffer;
                    }
                    else ptr = NULL;
                    break;
                case 15:
                    if (office) ptr = office->country;
                    else ptr = NULL;
                    break;
                case 16:
                    if (ad_attrib) ptr = ad_attrib->scriptPath;
                    else ptr = NULL;
                    break;
                case 17:
                    ptr = MasterPart->companyName;
                    break;
                case 18:
                    ptr = desc;
                    break;
                case 19:
                    if (ad_attrib) ptr = ad_attrib->homeDrive;
                    else ptr = NULL;
                    break;
                case 20: /* cn - same as displayName */
                case 21: /* displayName */
                    memset(buffer, 0, MAXLEN);
                    strcpy(buffer,"\"");
                    if (person.L_name)strcat(buffer, person.L_name);
                    strcat(buffer,", ");
                    if (person.initials) strcat(buffer, person.initials);
                    strcat(buffer, "(");
                    if (person.pref_name) strcat(buffer, person.pref_name);
                    strcat(buffer, ")\"");
                    ptr = buffer;
                    break;
                case 22:
                    if(ad_attrib) ptr = ad_attrib->profilePath;
                    else ptr = NULL;
                    break;
                case 23:
                    if (ad_attrib) ptr = ad_attrib->homeDir;
                    else ptr = NULL;
                    break;
                case 24: // currently there is no way to input the manager str
                    //ptr = manager;
                    ptr = NULL;
                    break;
                case 25: /* initials */
                    ptr = person.initials;
                    break;
                default:
                    ptr = NULL;
                    break;
            }
            if(ptr) fprintf(outFile,"%s",ptr);
            if(columnCount != OUTCOLUMNS-1)fprintf(outFile, ",");
        }
        fprintf(outFile, "\r\n");
        users = users->next;
    }

    fclose(outFile); /* close the file we're writing to */
    return SUCCESS;
}

/* batchImport: This function allows the user to import information into the 
 * program via a csv file. The function returns NULL on failure and the userList
 * it generated on success.
 */
userList batchImport(const char * fileStream){
    FILE * inFile;      /* Input file stream */
    char buffer[MAXLEN];    /* Stream buffer */
    char ** s = NULL;       /* Buffer normalizing array */
    int lineCount = 0;  /* The line counter in the file */

    /* Open up the user's import file */
    inFile= fopen(fileStream, "rb");
    if (!inFile){ /* This checks if the file opened successfully */
/*
        printf("batchImport_error: Cannot open user import file: %s.\r\n",
                fileStream);
*/
        return NULL; /* fopen failed */
    }

    /* The file opened successfully */
    while(fgets(buffer, MAXLEN, inFile)){
        s = Split(buffer, ',');

        if(!lineCount){ /* This is the case when the first row is discarded */
            lineCount++;    /* The first row is usually the name of the columns */
            continue;
        }
        else{
            addOneUser(s);
            /* Move on to the next line of importation file */
            lineCount++;
        }
    } /* Finished parsing file */
    fclose(inFile);
    return MasterUsers;
}

/* appendToMasterUsers: The function appends a User to a given Master Linked
 * list. The function returns FAIL on failure and SUCCESS on successfully
 * appending the User to linked list.
 */
int appendToMasterUsers(User person, userList * Master){
    userList newNode = NULL;   /* A new person's record */
    userList p = NULL;         /* The pointer to the head of the user's list */
    userList prev = NULL;      /* The pointer to the previous element of the user's list */
    
    /* New user node */
    newNode = (userList)malloc(sizeof(struct userNode));
    if(!newNode){
        printf("appendToMasterUsers_error: Cannot create a new Person's record for %s.\r\n",
                person->userName);
        fflush(stdout);
        return FAIL; /* malloc failed */
    }
    /* Initialize user node pointers */
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->user = person; /* Couple data with user node */

    if(userCount){
    /* find the last user in the list */
        p = *Master; /* Start of the Master List */
        prev = NULL;
        while(p){
            prev = p;
            p = p->next;
        }
        prev->next = newNode; /* Append New User Data */
        newNode->prev = prev; /* Keep track of previous user */
        ++userCount;
    }
    else {
        *Master = newNode; /* create head of list */
        newNode->prev = prev; /* Keep track of previous user */
        ++userCount;
    }
    return SUCCESS;
}

User addOneUser(char ** s) {
    char buffer[MAXLEN];    /* Stream buffer */
    User newPerson = NULL; 
    int userField = 0;
    
    /* Create a new person's record */
    newPerson = (User)malloc(sizeof(struct userBin));
    if(!newPerson){ /* This checks malloc for failure */
/*
        printf("batchImport_error: Cannot create a new Person's record.\r\n");
        fflush(stdout);
*/
        return NULL; /* malloc failed */
    }

        /* User Input Loop: Cycles through the buffer normalizing array
        * for information. The input is normalized to avoid segmentation
        * faults.
        */
    while((userField < INCOLUMNS) && s[userField]){
        /* Refactor the code so that certain instructions are not repeated :p */
        switch(userField){
            case 0: /* Insert username */
                if(strcmp(s[userField],"*") != 0){
                    newPerson->userName = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->userName, s[userField]);
                }
                else newPerson->userName = NULL;
                break;
            case 1: /* Insert first name */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->User.f_name = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->User.f_name, s[userField]);
                }
                else newPerson->User.f_name = NULL;
                break;
            case 2: /* Insert last name */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->User.L_name = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->User.L_name, s[userField]);
                }
                else newPerson->User.L_name = NULL;
                break;
            case 3: /* Insert email */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->email = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->email, s[userField]);
                }
                else newPerson->email = NULL;
                break;
            case 4: /* Insert title */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->title = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->title, s[userField]);
                }
                else newPerson->title = NULL;
                break;
            case 5: /* Insert department */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->dept = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->dept, s[userField]);
                }
                else newPerson->dept = NULL;
                break;
            case 6: /* Insert location */
                if(strcmp(s[userField], "*") != 0){
                /* find the location and append it to this record */
                    newPerson->loc = findLocation(s[userField], MasterLocs);
                }
                else newPerson->loc = NULL;
                break;
            case 7: /* Insert password */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->password = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->password, s[userField]);
                }
                else newPerson->password = NULL;
                break;
            case 8: /* check the strlen and create the pref_name from that */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->User.pref_name = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->User.pref_name, s[userField]);
                }
                else {
                    if(!newPerson->User.f_name){ /* The user's first name doesn't exist */
                        newPerson->User.pref_name = NULL;
                    }
                    else newPerson->User.pref_name = newPerson->User.f_name;
                }
                break;
            case 9: /* Insert middle name */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->User.m_name = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->User.m_name, s[userField]);
                }
                else newPerson->User.m_name = NULL;
                break;
            case 10: /* Insert modification attributes */
                if(strcmp(s[userField], "*") != 0){
                    newPerson->mod = (char *)malloc(strlen(s[userField])+1);
                    strcpy(newPerson->mod, s[userField]);
                }
                else newPerson->mod = NULL;
                break;
            default: /* not a valid userField value */
                break;
        } /* End of Switch */
    /* Always Do the following after allocating a field*/
    free(s[userField]);
    s[userField] = NULL; /* terminates freed bucket */
    userField++;
}

            /* populate the other fields */
    if (s[INCOLUMNS]) {
        newPerson->manager = (char *)malloc(strlen(s[INCOLUMNS])+1);
        strcpy(newPerson->manager, s[INCOLUMNS]);
    }
    else newPerson->manager = NULL;
    
            /* create the person's initials */
            newPerson->User.initials = (char *)malloc(6*sizeof(char));
            if(!newPerson->User.initials){
                printf("batchImport_error: Cannot create a new Person's initials for %s.\r\n", newPerson->userName);
                fflush(stdout);
                return NULL; /* malloc failed */
            }
            memset(newPerson->User.initials, 0, 6*sizeof(char));
            if(newPerson->User.f_name){
                newPerson->User.initials[0] = newPerson->User.f_name[0];
                strcat(newPerson->User.initials, ". ");
            }
            else if(newPerson->User.m_name){
                newPerson->User.initials[0] = newPerson->User.m_name[0];
                strcat(newPerson->User.initials, ".");
            }
             if (newPerson->User.f_name && newPerson->User.m_name){
                 newPerson->User.initials[3] = newPerson->User.m_name[0];
                 strcat(newPerson->User.initials, ".");
             }

            /* create the Active Directory attributes for this user */
            newPerson->attrib = (ADList)malloc(sizeof(struct ADlist));
            if(!newPerson->attrib){
/*
                printf("batchImport_error: Cannot create a new Person's record for %s.\r\n", newPerson->userName);
                fflush(stdout);
*/
                return NULL; /* malloc failed */
            }

            /* Establish common Script path, home drive, and description */
            newPerson->attrib->scriptPath = MasterADlist->scriptPath;
            newPerson->attrib->homeDrive = MasterADlist->homeDrive;
            newPerson->desc = MasterPart->desc;

            /* Establish unique profile path */
            strcpy(buffer, MasterADlist->profilePath);
            
            if(newPerson->userName){
                strcat(buffer, newPerson->userName);
            }
            newPerson->attrib->profilePath = (char *)malloc(strlen(buffer)+1);
            if(!newPerson->attrib->profilePath){
/*
                printf("batchImport_error: Cannot add profile path to %s.\r\n", newPerson->userName);
                fflush(stdout);
*/
                return NULL; /* malloc failed */
            }
            strcpy(newPerson->attrib->profilePath, buffer);

            /* Establish unique home directory */
            strcpy(buffer, MasterADlist->homeDir);
            if(newPerson->userName){
                strcat(buffer, newPerson->userName);
            }
            newPerson->attrib->homeDir = (char *)malloc(strlen(buffer)+1);
            if(!newPerson->attrib->homeDir){
/*
                printf("batchImport_error: Cannot add home directory to %s.\r\n", newPerson->userName);
                fflush(stdout);
*/
                return NULL; /* malloc failed */
            }
            strcpy(newPerson->attrib->homeDir, buffer);

            /* Establish user principal name */
            if(newPerson->userName){
                strcpy(buffer, newPerson->userName);
            }
            else memset(buffer, 0, MAXLEN);

            strcat(buffer, MasterADlist->UPN);
            newPerson->attrib->UPN = (char *)malloc(strlen(buffer)+1);
            if(!newPerson->attrib->UPN){
/*
                printf("batchImport_error: Cannot add User Principal Name to %s.\r\n", newPerson->userName);
                fflush(stdout);
*/
                return NULL; /* malloc failed */
            }
            strcpy(newPerson->attrib->UPN, buffer);

            /* Append the user information to the Global list */
            if(appendToMasterUsers(newPerson, &MasterUsers) != SUCCESS){
/*
                printf("batchImport_error: Cannot append %s to Master Users List.\r\n",
                        newPerson->userName);
                fflush(stdout);
*/
                return NULL; /* appending the person to the list failed */
            }
            
    return newPerson;
}

/* Read K&R for a better deep freeing algorithm */
int deleteAllUsers(userList users){ /* use a deep freeing algorithm */
    userList tmp;
    
    if (!userCount) return FAIL; /* we're not going to delete what's not there */
    
    while (users){
        /* Free department */
//        if(users->user->dept) {
//            free(users->user->dept);
//            users->user->dept = NULL;
//        }
        
        /* Free email *//*
        if (users->user->email) {
            free(users->user->email);
            users->user->email = NULL;
        }
        */
        
        /* Free manager*//*
        if (users->user->manager) {
            free(users->user->manager);
            users->user->manager = NULL;
        }*/
        
        /* Free modify *//*
        if (users->user->mod) {
            free(users->user->mod); 
            users->user->mod = NULL;
        }*/
        
        /* Free password *//*
        if (users->user->password) {
            free(users->user->password);
            users->user->password = NULL;
        }*/
        
        /* Free title *//*
        if (users->user->title) {
            free(users->user->title);
            users->user->title = NULL;
        }*/
        
        /* Free username *//*
        if (users->user->userName) { 
            free(users->user->userName);
            users->user->userName = NULL;
        }*/
        
        /* Free User information */
//        if (users->user->User.L_name) {
//            free(users->user->User.L_name);
//            users->user->User.L_name = NULL;
//        }
        
//        if (users->user->User.f_name) {
//            free(users->user->User.f_name);
//            users->user->User.f_name = NULL;
            
//        }
//        if (users->user->User.initials) {
//            free(users->user->User.initials);
//            users->user->User.initials = NULL;
//        }
//
//        if (users->user->User.m_name) {
//            free(users->user->User.m_name);
//            users->user->User.m_name = NULL;
//        }
//        if (users->user->User.pref_name) {
//            free(users->user->User.pref_name);
//            users->user->User.pref_name = NULL;
//        }
        /* End User Freeing */
        
        /* Free AD attributes */
//        if (users->user->attrib->scriptPath) {
//            free(users->user->attrib->scriptPath);
//            users->user->attrib->scriptPath = NULL;
//        }
//
//        if (users->user->attrib->profilePath) {
//            free(users->user->attrib->profilePath);
//            users->user->attrib->profilePath = NULL;
//        }
//
//        if (users->user->attrib->UPN) {
//            free(users->user->attrib->UPN);
//            users->user->attrib->UPN = NULL;
//        }
//
//        if (users->user->attrib->homeDir) {
//            free(users->user->attrib->homeDir);
//            users->user->attrib->homeDir = NULL;
//        }
//
//        if (users->user->attrib->homeDrive) {
//            users->user->attrib->homeDrive = NULL;
//        }
        
        /* End AD attributes freeing */
        
        /* Set locations to NULL */
//        if (users->user->loc) {
//            users->user->loc = NULL;
//        }
        
        /* Free user nodes */
        tmp = users;
        users = users->next; /* on to the next user node */
        free(tmp);
        tmp = NULL;
        --userCount; /* Decrement the user count */

    }
    return SUCCESS;
}

userList deleteOneUser(userList user) {
    userList prevUser = NULL;
    userList nextUser = NULL;
    userList tmp = user;
    if (!userCount || !tmp) return NULL; /* we're not going to delete what's not there */
    prevUser = tmp->prev;
    nextUser = tmp->next;

    if (prevUser) prevUser->next = nextUser;
    if (nextUser) nextUser->prev = prevUser;

    free(tmp); /* Free the user being deleted */
    tmp = NULL;
    --userCount; /* Decrement the user count */

    if (prevUser) return prevUser;
    else if (nextUser) return nextUser;
    else return NULL;
}

char * changeUserName(const char * username, User person) {
    char * oldusername = person->userName;
    char * newusername = NULL;
    int strSize = strlen(username)+1;
    int count;

    if (oldusername) free(oldusername);

    newusername = (char *)malloc(strSize); /* Account for the null char */
    if (!newusername) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newusername[count] = 0;

    if (strSize > 1) person->userName = strcpy(newusername, username);
    else person->userName = NULL;

    return newusername;
}

char * changeFirstName(const char * firstname, User person) {
    char * oldfirstname = NULL;
    char * newfirstname = NULL;
    int strSize = strlen(firstname)+1;
    int count;

    oldfirstname = person->User.f_name;
    if (oldfirstname) free(oldfirstname);

    newfirstname = (char *)malloc(strSize); /* Account for the null char */
    if (!newfirstname) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newfirstname[count] = 0;

    if (strSize > 1) person->User.f_name = strcpy(newfirstname, firstname);
    else person->User.f_name = NULL;

    return newfirstname;
}

char * changeLastName(const char * lastname, User person) {
    char * oldlastname = NULL;
    char * newlastname = NULL;
    int strSize = strlen(lastname)+1;
    int count;

    oldlastname = person->User.L_name;
    if (oldlastname) free(oldlastname);

    newlastname = (char *)malloc(strSize); /* Account for the null char */
    if (!newlastname) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newlastname[count] = 0;

    if (strSize > 1) person->User.L_name = strcpy(newlastname, lastname);
    else person->User.L_name = NULL;

    return newlastname;
}

char * changeMiddleName(const char * middlename, User person) {
    char * oldmiddlename = NULL;
    char * newmiddlename = NULL;
    int strSize = strlen(middlename)+1;
    int count;

    oldmiddlename = person->User.m_name;
    if (oldmiddlename) free(oldmiddlename);

    newmiddlename = (char *)malloc(strSize); /* Account for the null char */
    if (!newmiddlename) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newmiddlename[count] = 0;

    if (strSize > 1) person->User.m_name = strcpy(newmiddlename, middlename);
    else person->User.m_name = NULL;

    return newmiddlename;
}

char * changeInitials(const char * initials, User person) {
    char * oldinitials = NULL;
    char * newinitials = NULL;
    int strSize = strlen(initials)+1;
    int count;

    oldinitials = person->User.initials;
    if (oldinitials) free(oldinitials);

    newinitials = (char *)malloc(strSize); /* Account for the null char */
    if (!newinitials) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newinitials[count] = 0;

    if (strSize > 1) person->User.initials = strcpy(newinitials, initials);
    else person->User.initials = NULL;

    return newinitials;
}

char * changeTitle(const char * title, User person) {
    char * oldtitle = NULL;
    char * newtitle = NULL;
    int strSize = strlen(title)+1;
    int count;

    oldtitle = person->title;
    if (oldtitle) free(oldtitle);

    newtitle = (char *)malloc(strSize); /* Account for the null char */
    if (!newtitle) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newtitle[count] = 0;

    if (strSize > 1) person->title = strcpy(newtitle, title);
    else person->title = NULL;

    return newtitle;
}

char * changeDepartment(const char * department, User person) {
    char * olddept = NULL;
    char * newdept = NULL;
    int strSize = strlen(department)+1;
    int count;

    olddept = person->dept;
    if (olddept) free(olddept);

    newdept = (char *)malloc(strSize); /* Account for the null char */
    if (!newdept) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newdept[count] = 0;

    if (strSize > 1) person->dept = strcpy(newdept, department);
    else person->dept = NULL;

    return newdept;
}

char * changePreferredName(const char * prefname, User person) {
    char * oldpref = NULL;
    char * newpref = NULL;
    int strSize = strlen(prefname)+1;
    int count;

    oldpref = person->User.pref_name;
    if (oldpref) free(oldpref);

    newpref = (char *)malloc(strSize); /* Account for the null char */
    if (!newpref) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newpref[count] = 0;

    if (strSize > 1) person->User.pref_name = strcpy(newpref, prefname);
    else person->User.pref_name = NULL;

    return newpref;
}

/* 5/19 - Changed the checking of newLocation before return */
Location changeOfficeName(const char * officename, User person) {
    Location newLocation = NULL; /* The user's new location */
    if(person->loc) {
        free(person->loc); /* Free the user's old location */
        person->loc = NULL;
    }
    newLocation = findLocation(officename, MasterLocs);
    if (newLocation == NULL) return NULL;
    else return person->loc;
}

/* This function hasn't been implemented yet */
char * changeProfilePath(const char * path, User person) {
    return NULL;
}
/* This function hasn't been implemented yet */
char * changeHomeDirectory(const char * homedir, User person) {
    return NULL;
}

char * changeEmail(const char * email, User person) {
    char * oldemail = NULL;
    char * newemail = NULL;
    int strSize = strlen(email)+1;
    int count;

    oldemail = person->email;
    if (oldemail) free(oldemail);

    newemail = (char *)malloc(strSize); /* Account for the null char */
    if (!newemail) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newemail[count] = 0;

    if (strSize > 1) person->email = strcpy(newemail, email);
    else person->email = NULL;

    return newemail;
}

char * changePassword(const char * password, User person) {
    char * oldpassword = NULL;
    char * newpassword = NULL;
    int strSize = strlen(password)+1;
    int count;

    oldpassword = person->email;
    if (oldpassword) free(oldpassword);

    newpassword = (char *)malloc(strSize); /* Account for the null char */
    if (!newpassword) return NULL;

    /* Clear new string */
    for(count = 0; count < strSize; ++count) newpassword[count] = 0;

    if (strSize > 1) person->password = strcpy(newpassword, password);
    else person->password = NULL;

    return newpassword;
}
