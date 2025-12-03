#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024
#define INIT_CAP 5
int i;
	typedef struct {
    char **lines;
    int count;
    int capacity;
} EditorBuffer;

void initBuffer(EditorBuffer *buf) {
    buf->lines = malloc(INIT_CAP * sizeof(char*));
    if (!buf->lines) { perror("Memory error");
	 exit(1);
	 	 }
    buf->count = 0;
    buf->capacity = INIT_CAP;
}

void insertLine(EditorBuffer *buf, int pos, const char *text) {
    if (pos < 0 || pos > buf->count) { printf("Invalid index\n"); 
		return;
			 }
  	
	    if (buf->count == buf->capacity) {
        buf->capacity *= 2;
        char **newLines = realloc(buf->lines, buf->capacity * sizeof(char*));
        if (!newLines) { perror("Memory error"); 	
		exit(1);
		 }
  	
	        buf->lines = newLines;
    }
    memmove(&buf->lines[pos + 1], &buf->lines[pos], (buf->count - pos) * sizeof(char*));
    buf->lines[pos] = malloc(strlen(text) + 1);
    if (!buf->lines[pos]) { perror("Memory error");
	 exit(1);
	  }
    strcpy(buf->lines[pos], text);
    buf->count++;
}

void deleteLine(EditorBuffer *buf, int pos) {
    if (pos < 0 || pos >= buf->count) { printf("Invalid index\n"); return; }
    free(buf->lines[pos]);
    memmove(&buf->lines[pos], &buf->lines[pos + 1], (buf->count - pos - 1) * sizeof(char*));
    buf->count--;
}

void printLines(const EditorBuffer *buf) {
   	 for ( i = 0; i < buf->count; i++) printf("%d: %s\n", i, buf->lines[i]);

	}

void shrinkBuffer(EditorBuffer *buf) {
    if (buf->count == 0) { free(buf->lines); buf->lines = NULL; buf->capacity = 0; 
	return; 
	}
    char **newLines = realloc(buf->lines, buf->count * sizeof(char*));
    if (newLines) { buf->lines = newLines; buf->capacity = buf->count; }

	}

void freeBuffer(EditorBuffer *buf) {
    for ( i = 0; i < buf->count; i++) free(buf->lines[i]);
    free(buf->lines);
}

void saveToFile(const EditorBuffer *buf, const char *fname) {
    FILE *f = fopen(fname, "w");
    if (!f) { perror("File error");	
	 return;
	  }
    for ( i = 0; i < buf->count; i++) fprintf(f, "%s\n", buf->lines[i]);
    fclose(f);
}

void loadFromFile(EditorBuffer *buf, const char *fname) {
    FILE *f = fopen(fname, "r");
    if (!f) { perror("File error");
	 return;
	  }
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, f)) {
        line[strcspn(line, "\n")] = 0;
        insertLine(buf, buf->count, line);
    }
    fclose(f);
}

int main() {
    EditorBuffer buf;
    initBuffer(&buf);
    int choice, idx;
    char text[MAX_LEN], fname[100];

    while (1) {
        printf("\n1 Insert\n2 Delete\n3 Print\n4 Shrink\n5 Save\n6 Load\n7 Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Enter index: ");
				 scanf("%d", &idx);
				  getchar();
                printf("Enter line: "); 
				fgets(text, MAX_LEN, stdin);
                text[strcspn(text, "\n")] = 0;
                insertLine(&buf, idx, text);
                break;
            case 2:
                printf("Enter index: ");
					 scanf("%d", &idx);
                deleteLine(&buf, idx);
                break;
            case 3:
                printLines(&buf);
                break;
            case 4:
                shrinkBuffer(&buf);
                break;
            case 5:
                printf("Filename: "); 
				scanf("%s", fname);
                saveToFile(&buf, fname);
                break;
            case 6:
                printf("Filename: ");
				 scanf("%s", fname);
                loadFromFile(&buf, fname);
                break;
            case 7:
                freeBuffer(&buf);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

