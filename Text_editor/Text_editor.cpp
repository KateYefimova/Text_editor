#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_LINES 100
int current_line = 0;
void append_text(char* original, const char* to_append) {
    if (strlen(original) + strlen(to_append) < MAX_LENGTH) {
        snprintf(original, MAX_LENGTH, "%s %s", original, to_append);
    }
    else {
        printf("Overflow");
    }
}

void start_new_line(const char* to_append, char lines[MAX_LINES][MAX_LENGTH]) {
    if (current_line < MAX_LINES) {
        lines[current_line][0] = '\0';
        current_line++;
        printf("New line is started");
    }
    else {
        printf("Error: Maximum number of lines reached\n");
    }
}

void save_to_file(const char* filename, char lines[MAX_LINES][MAX_LENGTH], int current_line) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < current_line; i++) {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
    printf("Text has been saved successfully to %s\n", filename);
}

void load_to_file() {
    FILE* file;
    file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Error");
    }
    else {
        if (fgets(mystring, MAX_LENGTH, file) != NULL) {
            printf("%s", mys)
        }
    }
}


int main() {
    char original[MAX_LENGTH] = "Hello";
    char to_append[MAX_LENGTH];
    char text_to_append[MAX_LENGTH];
    char filename[MAX_LENGTH];



    char lines[MAX_LINES][MAX_LENGTH];
    int current_line = 0;
    scanf_s("%s", to_append, sizeof(to_append));
    append_text(original, to_append);
    printf(" %s\n", original);
    scanf_s("%s", text_to_append, sizeof(text_to_append));
    start_new_line(text_to_append, lines);

    printf("Enter the file name for saving: ");
    scanf_s("%99s", filename, (unsigned)sizeof(filename));
    save_to_file(filename, lines, current_line);


    printf("Lines:\n");
    for (int i = 0; i < current_line; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}