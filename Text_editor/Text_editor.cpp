#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_LINES 100

int current_line = 0;

void append_text(char** lines, const char* to_append) {
    if (current_line == 0) {
        printf("No lines to append text to.\n");
        return;
    }

    size_t original_length = strlen(lines[current_line - 1]);
    size_t to_append_length = strlen(to_append);
    lines[current_line - 1] = (char*)realloc(lines[current_line - 1], original_length + to_append_length + 1);
    if (lines[current_line - 1] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcat_s(lines[current_line - 1], original_length + to_append_length + 1, to_append);
}

void start_new_line(char*** lines) {
    *lines = (char**)realloc(*lines, (current_line + 1) * sizeof(char*));
    if (*lines == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    (*lines)[current_line] = (char*)malloc(MAX_LENGTH * sizeof(char));
    if ((*lines)[current_line] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    (*lines)[current_line][0] = '\0';
    current_line++;
    printf("New line is started\n");
}

void save_to_file(const char* filename, char** lines, int current_line) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < current_line; i++) {
        if (lines[i] != NULL) { // Check if the line is not NULL
            fprintf(file, "%s\n", lines[i]);
        }
    }

    fclose(file);
    printf("Text has been saved successfully to %s\n", filename);
}

void load_from_file(const char* filename, char** original, char*** lines) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }

    *lines = NULL;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (*lines == NULL) {
            *lines = (char**)malloc(sizeof(char*));
        }
        else {
            *lines = (char**)realloc(*lines, (current_line + 1) * sizeof(char*));
        }
        if (*lines == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            free(*original);
            return;
        }
        (*lines)[current_line] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*lines)[current_line] == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            free(*original);
            for (int i = 0; i < current_line; i++) {
                free((*lines)[i]);
            }
            free(*lines);
            return;
        }
        strcpy_s((*lines)[current_line], strlen(buffer) + 1, buffer);
        current_line++;
    }
    fclose(file);
    printf("Text has been loaded successfully from %s\n", filename);
}

void show_menu() {
    printf("Choose the command:\n");
    printf("1. Append text symbols to the end \n");
    printf("2. Start new line\n");
    printf("3. Use files to saving the information\n");
    printf("4. Use files to loading the information\n");
    printf("5. Print the current text to console \n");
    printf("6. Insert the text by line and symbol index  \n");
    printf("7. Search\n");
    printf("8. Clearing the console \n");
    printf("9. Exit \n");
}

int main() {
    char** lines = NULL;

    int command;

    while (1) {
        show_menu();
        printf("Enter the command: ");
        scanf_s("%d", &command);

        switch (command) {
        case 1:
            printf("Enter text to append: ");
            char to_append[MAX_LENGTH];
            scanf_s("%99s", to_append, (unsigned)sizeof(to_append));  // Зчитуємо вираз
            getchar();
            append_text(lines, to_append);
            break;
        case 2:
            start_new_line(&lines);
            break;
        case 3:
            printf("Enter the file name for saving: ");
            char filename[MAX_LENGTH];
            scanf_s("%99s", filename, (unsigned)sizeof(filename));
            save_to_file(filename, lines, current_line);
            break;
        case 4:
            printf("Enter the file name for loading: ");
            char load_filename[MAX_LENGTH];
            scanf_s("%99s", load_filename, (unsigned)sizeof(load_filename));
            load_from_file(load_filename, NULL, &lines);
            break;
        case 5:
            printf("Current text:\n");
            //printf("%s\n", lines[current_line-1]);
            for (int i = 0; i < current_line; i++) {
                printf("%s\n", lines[i]);
            }
            break;
        case 9:
            printf("Exiting...\n");
            // Звільнення пам'яті, виділеної для кожного рядка
            if (lines != NULL) {
                for (int i = 0; i < current_line; i++) {
                    free(lines[i]);
                }
                // Звільнення пам'яті, виділеної для масиву вказівників
                free(lines);
            }
            return 0;
        default:
            printf("The command is not implemented.\n");
        }
        fflush(stdin);
    }


    return 0;
}