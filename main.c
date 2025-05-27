
#include <stdio.h>
#include <string.h>

#include "chat.h"
#include "commands.h"
#include "persistence.h"
#include "util.h"

int main() {
    // Load any previously saved user data
    load_users_from_file();

    // Display currently online users at startup
    print_online_users();

    // Buffer for user input
    char buffer[128];
    char *result;

    // Start REPL loop
    do {
        printf("> ");
        // Read user input from stdin
        result = fgets(buffer, sizeof(buffer), stdin);

        // Trim newline if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Skip if input is a blank line
        if (buffer[0] == '\0') {
            continue;
        }

        // Use strtok to separate command and args
        char *command = strtok(buffer, " ");
        char *args = strtok(NULL, "");

        // Normalize args by trimming leading whitespace
        args = normalize_args(args);

        // Branch based on command
        if (strcmp(command, "join") == 0) {
            handle_join(args);
        } else if (strcmp(command, "send") == 0) {
            handle_message(args);
        } else if (strcmp(command, "list") == 0) {
            handle_list(args);
        } else if (strcmp(command, "leave") == 0) {
            handle_leave(args);
        } else if (strcmp(command, "exit") == 0) {
            handle_exit(args);
        }
        // Loop until EOF
    } while (result != NULL);
    return 0;
}
