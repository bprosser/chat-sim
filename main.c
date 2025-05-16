#include <stdio.h>
#include <string.h>

#include "chat.h"
#include "commands.h"
#include "persistence.h"

int main() {
    load_users_from_file();
    print_online_users();
    char buffer[128];
    char *result;
    do {
        printf("> ");
        result = fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        char *command = strtok(buffer, " ");
        char *args = strtok(NULL, "");
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
    } while (result != NULL);
    return 0;
}
