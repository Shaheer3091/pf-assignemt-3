#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i;
struct Student {
    int id;
    char name[100];
    char batch[20];
    char memType[10];
    char regDate[20];
    char dob[20];
    char interest[10];
};

struct Student *records = NULL;
int recCount = 0;

void loadDB(const char *file) {
    FILE *f = fopen(file, "rb");
    if (!f) return;
    fseek(f, 0, SEEK_END);
    long size = ftell(f) / sizeof(struct Student);
    rewind(f);
    records = malloc(size * sizeof(struct Student));
    fread(records, sizeof(struct Student), size, f);
    recCount = size;
    fclose(f);
}

void saveDB(const char *file) {
    FILE *f = fopen(file, "wb");
    if (!f) {
        printf("Error: Cannot open file for writing.\n");
        return;
    }
    fwrite(records, sizeof(struct Student), recCount, f);
    fclose(f);
}

int existsID(int id) {
    for ( i = 0; i < recCount; i++)
        if (records[i].id == id) return 1;
    return 0;
}

void addRec(const char *file) {
    struct Student s;
    printf("Enter ID: "); scanf("%d", &s.id);
    if (existsID(s.id)) {
        printf("Error: ID already exists!\n");
        return;
    }
    printf("Enter Name: "); getchar(); fgets(s.name, 100, stdin); s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Batch (CS/SE/Cyber/AI): "); scanf("%s", s.batch);
    printf("Enter Membership (IEEE/ACM): "); scanf("%s", s.memType);
    printf("Enter Registration Date (YYYY-MM-DD): "); scanf("%s", s.regDate);
    printf("Enter DOB (YYYY-MM-DD): "); scanf("%s", s.dob);
    printf("Enter Interest (IEEE/ACM/Both): "); scanf("%s", s.interest);

    records = realloc(records, (recCount + 1) * sizeof(struct Student));
    records[recCount++] = s;
    saveDB(file);
    printf("Student added successfully.\n");
}

void updateRec(const char *file) {
    int id; printf("Enter ID to update: "); scanf("%d", &id);
    for ( i = 0; i < recCount; i++) {
        if (records[i].id == id) {
            printf("New Batch (leave same to keep current): "); scanf("%s", records[i].batch);
            printf("New Membership (leave same to keep current): "); scanf("%s", records[i].memType);
            printf("New Interest (leave same to keep current): "); scanf("%s", records[i].interest);
            saveDB(file);
            printf("Student updated successfully.\n");
            return;
        }
    }
    printf("Error: Student ID not found.\n");
}

void deleteRec(const char *file) {
    int id; printf("Enter ID to delete: "); scanf("%d", &id);
    int found = 0, j = 0;
    struct Student *temp = malloc(recCount * sizeof(struct Student));
    for ( i = 0; i < recCount; i++) {
        if (records[i].id != id) temp[j++] = records[i];
        else found = 1;
    }
    if (!found) {
        free(temp);
        printf("Error: Student ID not found.\n");
        return;
    }
    free(records);
    records = temp;
    recCount = j;
    saveDB(file);
    printf("Student deleted successfully.\n");
}

void showAll() {
    if (recCount == 0) { printf("No records found.\n"); return; }
    for ( i = 0; i < recCount; i++)
        printf("%d %s %s %s %s %s %s\n", records[i].id, records[i].name, records[i].batch, records[i].memType, records[i].regDate, records[i].dob, records[i].interest);
}

void batchReport() {
    char b[20], m[10];
    printf("Enter Batch to filter (CS/SE/Cyber/AI): "); scanf("%s", b);
    printf("Enter Membership to filter (IEEE/ACM/Both/All): "); scanf("%s", m);
    int found = 0;
    for ( i = 0; i < recCount; i++) {
        int batchMatch = strcmp(records[i].batch, b) == 0;
        int memMatch = (strcmp(m, "All") == 0) || (strcmp(records[i].memType, m) == 0) || (strcmp(records[i].interest, m) == 0) || (strcmp(records[i].interest, "Both") == 0);
        if (batchMatch && memMatch) {
            printf("%d %s %s %s\n", records[i].id, records[i].name, records[i].memType, records[i].interest);
            found = 1;
        }
    }
    if (!found) printf("No matching records found.\n");
}

int main() {
    loadDB("members.dat");
    int ch;
    while (1) {
        printf("\n1 Add\n2 Update\n3 Delete\n4 View All\n5 Batch Report\n6 Exit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) addRec("members.dat");
        else if (ch == 2) updateRec("members.dat");
        else if (ch == 3) deleteRec("members.dat");
        else if (ch == 4) showAll();
        else if (ch == 5) batchReport();
        else if (ch == 6) break;
        else printf("Invalid choice.\n");
    }
    free(records);
    return 0;
}
