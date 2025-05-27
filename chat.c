
#include "chat.h"

#include <stdio.h>
#include <string.h>

// Arrays of chat messages and users, using types defined in chat.h
struct chat_message chat_messages[MAX_CHAT_MESSAGES];
struct chat_user chat_users[MAX_CHAT_USERS];

// Track the current number of users and messages
int user_count = 0;
int message_count = 0;

// Prints a formatted chat event based on the message type (JOIN, LEAVE, MESSAGE)
void print_message(struct chat_message *msg) {
    switch (msg->type) {
        case JOIN:
            printf("[%s] joined the chat\n", msg->sender);
            break;
        case LEAVE:
            printf("[%s] left the chat\n", msg->sender);
            break;
        case MESSAGE:
            printf("[%s]: %s\n", msg->sender, msg->content);
            break;
        default:
            printf("Invalid msg\n");
            break;
    }
}

// Updates a user's online status, or adds a new user if not found
void update_user_status(const char *name, int online) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(name, chat_users[i].name) == 0) {
            chat_users[i].online = online;
            return;
        }
    }
    if (online == 1) {
        strcpy(chat_users[user_count].name, name);
        chat_users[user_count++].online = 1;
    }
}

// Prints list of users currently online
void print_online_users(void) {
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (chat_users[i].online == 1) {
            if (!found) {
                printf("Users currently online:\n");
                found = 1;
            }
            printf("- %s\n", chat_users[i].name);
        }
    }
    if (!found) {
        printf("No users currently online.\n");
    }
}

// Logs a chat event from a sender, with content and message type
void log_chat_event(char *sender, char *content, enum message_type type) {
    strcpy(chat_messages[message_count].sender, sender);
    strcpy(chat_messages[message_count].content, content);
    chat_messages[message_count].type = type;
    message_count++;
    print_message(&chat_messages[message_count - 1]);
}
