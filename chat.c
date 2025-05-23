#include "chat.h"

#include <stdio.h>
#include <string.h>

struct chat_message chat_messages[MAX_CHAT_MESSAGES];
struct chat_user chat_users[MAX_CHAT_USERS];

int user_count = 0;
int message_count = 0;

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

void log_chat_event(char *sender, char *content, enum message_type type) {
    strcpy(chat_messages[message_count].sender, sender);
    strcpy(chat_messages[message_count].content, content);
    chat_messages[message_count].type = type;
    message_count++;
    print_message(&chat_messages[message_count - 1]);
}
