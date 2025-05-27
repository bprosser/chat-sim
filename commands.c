
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

void print_help_entry(const char *cmd, const char *desc) {
    const int indent = 2;
    const int padding = 20;
    printf("%*s%s%*s - %s\n", indent, "", cmd, padding - (int)strlen(cmd) - 3, "", desc);
}

void handle_help(char *args) {
    (void)args;
    const char *join = "join <user>";
    const char *send = "send <user> <msg>";
    const char *list = "list";
    const char *leave = "leave <user>";
    const char *help = "help";
    const char *exit = "exit";
    printf("Available commands:\n");
    print_help_entry(join, "Join the chat");
    print_help_entry(send, "Send a message to a user");
    print_help_entry(list, "List all online users");
    print_help_entry(leave, "Leave the chat");
    print_help_entry(help, "Show this help message");
    print_help_entry(exit, "Save users and exit");
}
