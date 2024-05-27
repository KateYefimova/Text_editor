#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

#define INITIAL_BUFFER_SIZE 100

int current_line = 0;

void clear_console() {
    system(CLEAR_COMMAND);
}

void append_text(char** lines, const char* to_append) {
    if (current_line == 0) {
        printf("No lines to append text to.\n");
        return;
    }

    size_t original_length = strlen(lines[current_line - 1]);
    size_t to_append_length = strlen(to_append);
    lines[current_line - 1] = (char*)realloc(lines[current_line - 1], original_length + to_append_length + 2);
    if (lines[current_line - 1] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    if (original_length > 0) {
        strcat_s(lines[current_line - 1], original_length + to_append_length + 2, " ");
    }
    strcat_s(lines[current_line - 1], original_length + to_append_length + 2, to_append);
}

void start_new_line(char*** lines) {
    *lines = (char**)realloc(*lines, (current_line + 1) * sizeof(char*));
    if (*lines == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    (*lines)[current_line] = (char*)malloc(INITIAL_BUFFER_SIZE * sizeof(char));
    if ((*lines)[current_line] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    (*lines)[current_line][0] = '\0';
    current_line++;
}

void save_to_file(const char* filename, char** lines) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < current_line; i++) {
        if (lines[i] != NULL) {
            fputs(lines[i], file);
            fputc('\n', file);
        }
    }

    fclose(file);
    printf("Text has been saved successfully to %s\n", filename);
}

void load_from_file(const char* filename, char*** lines) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }
    if (*lines != NULL) {
        for (int i = 0; i < current_line; i++) {
            free((*lines)[i]);
        }
        free(*lines);
        *lines = NULL;
    }
    int current_line1 = 0;

    size_t buffer_size = INITIAL_BUFFER_SIZE;
    char* buffer = (char*)malloc(buffer_size);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    *lines = (char**)malloc(sizeof(char*));
    if (*lines == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        free(buffer);
        return;
    }

    while (fgets(buffer, buffer_size, file)) {
        size_t len = strlen(buffer);
        while (len > 0 && buffer[len - 1] != '\n') {

            buffer_size *= 2;
            buffer = (char*)realloc(buffer, buffer_size);
            if (buffer == NULL) {
                printf("Memory allocation failed\n");
                fclose(file);
                for (int i = 0; i < current_line1; i++) {
                    free((*lines)[i]);
                }
                free(*lines);
                return;
            }
            if (fgets(buffer + len, buffer_size - len, file) == NULL) {
                break;
            }
            len = strlen(buffer);
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        (*lines)[current_line1] = _strdup(buffer);
        if ((*lines)[current_line1] == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            free(buffer);
            for (int i = 0; i < current_line1; i++) {
                free((*lines)[i]);
            }
            free(*lines);
            return;
        }
        current_line1++;

        // Resize the lines array if needed
        char** temp = (char**)realloc(*lines, (current_line1 + 1) * sizeof(char*));
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            free(buffer);
            for (int i = 0; i < current_line1; i++) {
                free((*lines)[i]);
            }
            free(*lines);
            return;
        }
        *lines = temp;
    }

    free(buffer);
    fclose(file);

    current_line = current_line1;

    printf("Text loaded successfully from %s:\n", filename);
    for (int i = 0; i < current_line; i++) {
        printf("%s\n", (*lines)[i]);
    }
}



void insert_text(char** lines, int line, int index, const char* text) {
    if (line >= current_line || line < 0) {
        printf("Invalid line number.\n");
        return;
    }
    size_t line_length = strlen(lines[line]);
    size_t text_length = strlen(text);

    if (index > line_length || index < 0) {
        printf("Invalid index.\n");
        return;
    }

    lines[line] = (char*)realloc(lines[line], line_length + text_length + 1);
    if (lines[line] == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    memmove(&lines[line][index + text_length], &lines[line][index], line_length - index + 1);
    memcpy(&lines[line][index], text, text_length);
}

void search_text(char** lines, const char* text_to_search) {
    int found = 0;
    size_t search_len = strlen(text_to_search);
    for (int i = 0; i < current_line; i++) {
        char* pos = lines[i];
        while ((pos = strstr(pos, text_to_search)) != NULL) {
            int index = pos - lines[i];
            printf("Line %d, Index %d\n", i, index);
            pos += search_len;
            found = 1;
        }
    }
    if (!found) {
        printf("Text not found.\n");
    }
}

void show_menu() {
    printf("Choose the command:\n");
    printf("1. Append text symbols to the end\n");
    printf("2. Start new line\n");
    printf("3. Use files to save the information\n");
    printf("4. Use files to load the information\n");
    printf("5. Print the current text to console\n");
    printf("6. Insert the text by line and symbol index\n");
    printf("7. Search\n");
    printf("8. Clear console\n");
    printf("9. Exit\n");
}

char* read_line() {
    size_t size = INITIAL_BUFFER_SIZE;
    size_t len = 0;
    char* buffer = (char*)malloc(size);
    if (!buffer) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        buffer[len++] = ch;
        if (len == size) {
            size *= 2;
            buffer = (char*)realloc(buffer, size);
            if (!buffer) {
                printf("Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    buffer[len] = '\0';
    return buffer;
}

int main() {
    char** lines = NULL;

    int command;
    show_menu();
    while (1) {
        printf("Enter the command: ");
        if (scanf_s("%d", &command) != 1) {
            printf("Invalid command. Please enter a number between 1 and 9.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar(); 

        switch (command) {
        case 1: {
            printf("Enter text to append: ");
            char* to_append = read_line();

            if (current_line == 0) {
                start_new_line(&lines);
            }

            append_text(lines, to_append);
            free(to_append);
            break;
        }
        case 2:
            start_new_line(&lines);
            printf("New line started\n");
            break;
        case 3: {
            printf("Enter the file name for saving: ");
            char* filename = read_line();

            save_to_file(filename, lines);
            free(filename);
            break;
        }
        case 4: {
            printf("Enter the file name for loading: ");

            char* load_filename = read_line();

            load_from_file(load_filename, &lines);
            free(load_filename);
            break;
        }
        case 5:
            printf("Current text:\n");
            for (int i = 0; i < current_line; i++) {
                printf("%s\n", lines[i]);
            }
            break;
        case 6: {
            printf("Choose line and index:\n");
            int line, index;
            if (scanf_s("%d %d", &line, &index) != 2) {
                printf("Invalid input. Please enter two numbers.\n");
                while (getchar() != '\n');
                break;
            }
            getchar(); 
            printf("Enter text to insert:\n");
            char* text = read_line();
            insert_text(lines, line, index, text);
            free(text);
            break;
        }
        case 7: {
            printf("Enter text to search:\n");
            char* text_to_search = read_line();
            printf("Text found at these positions:\n");
            search_text(lines, text_to_search);
            free(text_to_search);
            break;
        }
        case 8:
            clear_console();
            show_menu();
            break;
        case 9:
            printf("Exiting...\n");
            if (lines != NULL) {
                for (int i = 0; i < current_line; i++) {
                    free(lines[i]);
                }
                free(lines);
            }
            return 0;
        default:
            printf("The command is not implemented.\n");
        }
    }

    return 0;
}