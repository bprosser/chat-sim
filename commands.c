
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chat.h"
#include "persistence.h"

// Handles the 'join' command: logs a join event and marks user online
void handle_join(char *args) {
    if (args == NULL) {
        fprintf(stderr, "Usage: join <username>\n");
        return;
    }
    log_chat_event(args, "", JOIN);
    update_user_status(args, 1);
}

// Handles the 'send' command: parses message and logs it
void handle_message(char *args) {
    if (args == NULL) {
        fprintf(stderr, "Usage: send <username> <message>\n");
        return;
    }

    char *send_name = strtok(args, " ");
    char *send_msg = strtok(NULL, "");

    if (send_name == NULL || send_msg == NULL) {
        fprintf(stderr, "Usage: send <username> <message>\n");
        return;
    }

    log_chat_event(send_name, send_msg, MESSAGE);
}

// Handles the 'list' command: prints online users
void handle_list(char *args) {
    // Unused parameter
    (void)args;
    print_online_users();
}

// Handles the 'leave' command: logs leave event and marks user offline
void handle_leave(char *args) {
    if (args == NULL) {
        fprintf(stderr, "Usage: leave <username>\n");
        return;
    }
    log_chat_event(args, "", LEAVE);
    update_user_status(args, 0);
}

// Handles the 'exit' command: saves users and exits
void handle_exit(char *args) {
    // Unused parameter
    (void)args;
    save_users_to_file();
    exit(0);
}
