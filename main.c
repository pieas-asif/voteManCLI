#include<stdio.h>
#include<stdlib.h>

void login();

void insertVoter();
int idCheck(int id);
int removeVoter(int id);
void listVoter();

void checkLogin(int id, int pin);
void vote();

void endVote();
void clearDatabase();
void clearVote();
void clearData();

int main() {
    while(1) {
        int i;
        system("cls");
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
    int id, pass, i, status;
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
                system("pause");
                break;
            case 2:
                printf("Enter ID to Delete: ");
                scanf("%d", &uid);
                status = removeVoter(uid);
                (status == 1) ? printf("Successfully Deleted ID#%d\n", uid) : printf("ID#%d Not Found\n", uid);
                system("pause");
                break;
            case 3:
                listVoter();
                break;
            case 9:
                endVote();
                break;
            default:
                puts("Invalid Input");
                system("pause");
        }
    } else {
        checkLogin(id, pass);
    }
}

void checkLogin(int id, int pin) {
    int dbid, dbpn, loginStatus = 0, rs;
    FILE* file = fopen("database.txt", "r");
    char line[256];

    while(fgets(line, sizeof(line), file)) {
        sscanf(line,"%d %d", &dbid, &dbpn);
        if(id == dbid && pin == dbpn) {
            printf("Login Successful\n");
            fclose(file);
            loginStatus = 1;
            rs = removeVoter(id);
        }
    }

    if(!loginStatus) {
        printf("Unauthorised access\n");
        fclose(file);
        login();
    } else {
        vote();
    }
}


void insertVoter() {
    system("cls"); // system("cls") in windows
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

int removeVoter(int id) {
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

    return status;
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

void vote() {
    int vote_choice;
    puts("Enter 1 to vote for perticipate A");
    puts("Enter 2 to vote for perticipate B");
    scanf("%d", &vote_choice);

    FILE* file = fopen("v.ote", "r");
    FILE* fp = fopen("d.ata", "w");
    char line[256];
    int id, vote;

    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d", &id, &vote);

        if(vote_choice == id) {
            vote += 1;
            fprintf(fp, "%d \t%d\n", id, vote);
        }
        else
            fprintf(fp, "%s", line);
    }
    fclose(file);
    fclose(fp);

    file = fopen("v.ote", "w");
    fp = fopen("d.ata", "r");

    while(fgets(line, sizeof(line), fp)) {
        fprintf(file, "%s", line);
    }
    fclose(file);
    fclose(fp);
    system("cls");

    login();
}

void endVote() {
    FILE * fp = fopen("v.ote", "r");
    char line[20];
    int A[2] = {0};
    int B[2] = {0};
    int i = 0;
    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d %d", &A[i], &B[i]);
        i++;
    }
    fclose(fp);
    system("cls");
    if(B[0] > B[1]) printf("Participant A won\n\n");
    else if(B[0] < B[1]) printf("Participant B won\n\n");
    else printf("Draw\n\n");
    system("pause");
    clearDatabase();
    clearVote();
    clearData();
}

void clearDatabase() {
    FILE * fp = fopen("database.txt", "w");
    fclose(fp);
}

void clearVote() {
    FILE * fp = fopen("v.ote", "w");
    fprintf(fp, "1\t 0\n");
    fprintf(fp, "2\t 0\n");
    fclose(fp);
}

void clearData() {
    FILE * fp = fopen("d.ata", "w");
    fprintf(fp, "1\t 0\n");
    fprintf(fp, "2\t 0\n");
    fclose(fp);
}
