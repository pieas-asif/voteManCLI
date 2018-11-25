#include<stdio.h>
#include<stdlib.h>

void login();

void insertVoter();
int idCheck(int id);
void removeVoter(int id);
void listVoter();

int main() {
    while(1) {
        int i;
        system("clear");
        puts("Welcome");
        puts("------------------");
        puts("Enter 1 to LOGIN");
        printf("~~> ");
        scanf("%d", &i);
        if(i == 1) {
            login();
        }
    }
}

void login() {
    int id, pass, i;
    printf("Enter Id: ");
    scanf("%d", &id);
    printf("Enter Password: ");
    scanf("%d", &pass);
    if(id == 9898 && pass == 7878) {
        int uid;
        puts("Welcome Admin");
        puts("-------------------");
        puts("Enter 1 to Insert Voter");
        puts("Enter 2 to Remove Voter");
        puts("Enter 3 to List Voter");
        puts("Enter 9 to End Vote");
        scanf("%d", &i);
        switch(i) {
            case 1:
                insertVoter();
                break;
            case 2:
                printf("Enter ID to Delete: ");
                scanf("%d", &uid);
                removeVoter(uid);
                break;
            case 3:
                listVoter();
                break;
            case 9:
                // endVote();
                break;
            default:
                puts("Invalid Input");
        }
    }
}

void insertVoter() {
    system("clear"); // system("cls") in windows
    int id, pin, choice;
    FILE* file = fopen("database.txt", "a");

    printf("Enter Id (Must be in range 1001 to 9999): ");
    scanf("%d", &id);
    printf("Enter Pin (Must Contain 4 DIGIT): ");
    scanf("%d", &pin);

    if(idCheck(id) && id > 1000 && id < 10000 && pin > 999 && pin < 10000) {
        fprintf(file, "%d \t%d\n", id, pin);
        printf("Successfully Created Voter\n");
        fclose(file);
        printf("Enter 1 to add anoter, else to continue: ");
        scanf("%d", &choice);
        if(choice == 1) insertVoter();
    } else {
        printf("Something Went Wrong. \nEnter 1 to try again: ");
        scanf("%d", &choice);
        fclose(file);
        if(choice == 1) insertVoter();
    }
}

int idCheck(int id) {
    int dbid, dbpn;
    FILE* file = fopen("database.txt", "r");
    char line[256];

    while(fgets(line, sizeof(line), file)) {
        sscanf(line,"%d %d", &dbid, &dbpn);
        if(id == dbid) {
            puts("Error: Duplicate ID Detected");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void removeVoter(int id) {
    FILE* file = fopen("database.txt", "r");
    FILE* fp = fopen("d.ata", "w");
    char line[256];
    int dbid, dbpn, choice;
    int status = 0;

    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d", &dbid, &dbpn);

        if(id == dbid) {
            status = 1;
            continue;
        }
        else fprintf(fp, "%s", line);
    }
    fclose(file);
    fclose(fp);

    file = fopen("database.txt", "w");
    fp = fopen("d.ata", "r");

    while(fgets(line, sizeof(line), fp)) {
        fprintf(file, "%s", line);
    }

    fclose(file);
    fclose(fp);

    (status == 1) ? printf("Successfully Deleted ID#%d\n", id) : printf("ID#%d Not Found\n", id);
    printf("Enter 1 to Delete Another, else to continue: ");
    scanf("%d", &choice);
    if(choice == 1) {
        int uid;
        system("clear");
        printf("Enter ID to Delete: ");
        scanf("%d", &uid);
        removeVoter(uid);
    }
}

void listVoter() {
    FILE* file = fopen("database.txt", "r");
    int i;
    char line[256];

    while(fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);

    printf("\n\nEOF: Enter 1 to continue: ");
    scanf("%d", &i);
}