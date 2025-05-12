#include <stdio.h>
#include <string.h>

#include "chat.h"
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
            log_chat_event(args, "", JOIN);
            update_user_status(args, 1);
        } else if (strcmp(command, "send") == 0) {
            char *send_name = strtok(args, " ");
            char *send_msg = strtok(NULL, "");
            log_chat_event(send_name, send_msg, MESSAGE);
        } else if (strcmp(command, "list") == 0) {
            print_online_users();
        } else if (strcmp(command, "leave") == 0) {
            log_chat_event(args, "", LEAVE);
            update_user_status(args, 0);
            print_online_users();
        } else if (strcmp(command, "exit") == 0) {
            save_users_to_file();
            return 0;
        }
    } while (result != NULL);
    return 0;
}
