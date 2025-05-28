
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

typedef struct {
    const char *cmd;
    const char *desc;
} HelpEntry;

void handle_help(char *args) {
    (void)args;

    HelpEntry help_entries[] = {
        {"join <user>", "Join the chat"},   {"send <user> <msg>", "Send a message to a user"},
        {"list", "List all online users"},  {"leave <user>", "Leave the chat"},
        {"help", "Show this help message"}, {"exit", "Save users and exit"}};

    printf("Available commands:\n");
    for (int i = 0; i < (int)(sizeof(help_entries) / sizeof(help_entries[0])); i++) {
        print_help_entry(help_entries[i].cmd, help_entries[i].desc);
    }
}
