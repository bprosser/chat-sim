#include "persistence.h"

#include <stdio.h>
#include <string.h>

#include "chat.h"

#define USER_DATA_FILE "users.txt"

void load_users_from_file(void) {
    FILE *file = fopen(USER_DATA_FILE, "r");
    if (file == NULL) {
        printf("Warning: %s not found, starting with no users.\n", USER_DATA_FILE);
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Use the string tokenizer (strtok) function to split the string into tokens
        // First call: pass the full string
        // Subsequent calls: pass NULL to continue from the previous position
        char *username = strtok(buffer, ",");
        char *status = strtok(NULL, ",");

        if (username == NULL || status == NULL) {
            fprintf(stderr, "Malformed line: %s", buffer);
            continue;
        }

        // Use the string complement span (strcspn) function to find the index of the first newline
        // or carriage return, and replace with '\0' to clean the string

        username[strcspn(username, "\r\n")] = '\0';
        status[strcspn(status, "\r\n")] = '\0';

        int online = -1;
        if (strcmp(status, "online") == 0)
            online = 1;
        else if (strcmp(status, "offline") == 0)
            online = 0;
        else {
            fprintf(stderr, "Warning: unknown status '%s' for user '%s'\n", status, username);
            continue;
        }

        if (user_count < MAX_CHAT_USERS) {
            strcpy(chat_users[user_count].name, username);
            chat_users[user_count].online = online;
            user_count++;
        } else {
            fprintf(stderr, "User limit reached - skipping '%s'\n", username);
        }
    }
    fclose(file);
}

void save_users_to_file(void) {
    FILE *file = fopen(USER_DATA_FILE, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        if (chat_users[i].name[0] != '\0') {
            const char *status_str = (chat_users[i].online) ? "online" : "offline";
            fprintf(file, "%s,%s\r\n", chat_users[i].name, status_str);
        }
    }
    fclose(file);
}
