#include "commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chat.h"
#include "persistence.h"

void handle_join(char *args) {
    if (args == NULL) {
        fprintf(stderr, "Usage: join <username>\n");
        return;
    }
    log_chat_event(args, "", JOIN);
    update_user_status(args, 1);
}

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

void handle_list(char *args) {
    (void)args;
    print_online_users();
}

void handle_leave(char *args) {
    if (args == NULL) {
        fprintf(stderr, "Usage: leave <username>\n");
        return;
    }
    log_chat_event(args, "", LEAVE);
    update_user_status(args, 0);
}
void handle_exit(char *args) {
    (void)args;
    save_users_to_file();
    exit(0);
}
