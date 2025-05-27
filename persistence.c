
#include "persistence.h"

#include <stdio.h>
#include <string.h>

#include "chat.h"

#define USER_DATA_FILE "users.txt"

void load_users_from_file(void) {
    // Open the user data file in read mode
    FILE *file = fopen(USER_DATA_FILE, "r");

    // If the file doesn't exist, warn and continue with no users
    if (file == NULL) {
        printf("Warning: %s not found, starting with no users.\n", USER_DATA_FILE);
        return;
    }

    // Buffer to hold each line read from the file
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Use the string tokenizer (strtok) function to split the string into tokens
        // First call: pass the full string
        // Subsequent calls: pass NULL to continue from the previous position
        char *username = strtok(buffer, ",");
        char *status = strtok(NULL, ",");

        // If line is malformed (missing either part), skip it
        if (username == NULL || status == NULL) {
            fprintf(stderr, "Malformed line: %s", buffer);
            continue;
        }

        // Use the string complement span (strcspn) function to find the index of the first newline
        // or carriage return, and replace with '\0' to clean the string

        username[strcspn(username, "\r\n")] = '\0';
        status[strcspn(status, "\r\n")] = '\0';

        // Use sentinel value to check status validity
        int online = -1;

        // Set online flag based on text string
        if (strcmp(status, "online") == 0)
            online = 1;
        else if (strcmp(status, "offline") == 0)
            online = 0;
        else {
            // Handle unrecognized status string
            fprintf(stderr, "Warning: unknown status '%s' for user '%s'\n", status, username);
            continue;
        }

        // Add user to array if under the maximum limit
        if (user_count < MAX_CHAT_USERS) {
            strcpy(chat_users[user_count].name, username);
            chat_users[user_count].online = online;
            user_count++;
        } else {
            fprintf(stderr, "User limit reached - skipping '%s'\n", username);
        }
    }

    // Close file after reading
    fclose(file);
}

void save_users_to_file(void) {
    // Open file in write mode to overwrite user data
    FILE *file = fopen(USER_DATA_FILE, "w");

    // Check file opened successfully
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Loop through users and write their name and status to file
    for (int i = 0; i < user_count; i++) {
        if (chat_users[i].name[0] != '\0') {
            const char *status_str = (chat_users[i].online) ? "online" : "offline";
            fprintf(file, "%s,%s\r\n", chat_users[i].name, status_str);
        }
    }

    // Close file after writing
    fclose(file);
}
