#include <stdio.h>

struct Book {
    int id;
    int popularity;
    int lastAccessTime;
};

int main() {
    int capacity;
    int numberOfOperations;
    scanf("%d %d", &capacity, &numberOfOperations);

    struct Book shelf[1000];
    int shelfSize = 0;
    int currentTime = 1;

    for (int i = 0; i < numberOfOperations; i++) {
        char command[10];
        scanf("%s", command);

        if (command[0] == 'A' && command[1] == 'D') {
            int id;
            int popularity;
            scanf("%d %d", &id, &popularity);

            int found = -1;
            for (int j = 0; j < shelfSize; j++) {
                if (shelf[j].id == id) {
                    found = j;
                    break;
                }
            }

            if (found != -1) {
                shelf[found].popularity = popularity;
                shelf[found].lastAccessTime = currentTime;
                currentTime++;
            } else {
                if (shelfSize == capacity) {
                    int leastIndex = 0;
                    for (int j = 1; j < shelfSize; j++) {
                        if (shelf[j].lastAccessTime < shelf[leastIndex].lastAccessTime) {
                            leastIndex = j;
                        }
                    }
                    for (int j = leastIndex; j < shelfSize - 1; j++) {
                        shelf[j] = shelf[j + 1];
                    }
                    shelfSize--;
                }
                shelf[shelfSize].id = id;
                shelf[shelfSize].popularity = popularity;
                shelf[shelfSize].lastAccessTime = currentTime;
                shelfSize++;
                currentTime++;
            }
        }

        else if (command[0] == 'A' && command[1] == 'C') {
            int id;
            scanf("%d", &id);

            int found = -1;
            for (int j = 0; j < shelfSize; j++) {
                if (shelf[j].id == id) {
                    found = j;
                    break;
                }
            }

            if (found == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", shelf[found].popularity);
                shelf[found].lastAccessTime = currentTime;
                currentTime++;
            }
        }
    }

    return 0;
}
