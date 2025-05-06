#include <stdio.h>
#include <string.h>

#define MAX_CHAT_MESSAGES 100
#define MAX_CHAT_USERS 10

enum message_type { JOIN, LEAVE, MESSAGE };

struct chat_message {
    char sender[32];
    char content[128];
    enum message_type type;
};

struct chat_user {
    char name[32];
    int online;
};

struct chat_message chat_messages[MAX_CHAT_MESSAGES];
struct chat_user chat_users[MAX_CHAT_USERS];

int message_count = 0;
int user_count = 0;

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
                printf("\nchat_users still online:\n");
                found = 1;
            }
            printf("- %s\n", chat_users[i].name);
        }
    }
    if (!found) {
        printf("No chat_users currently online.\n");
    }
}

int main() {
    update_user_status("Alice", 1);
    chat_messages[message_count++] = (struct chat_message){"Alice", "", JOIN};

    update_user_status("Bob", 1);
    chat_messages[message_count++] = (struct chat_message){"Bob", "", JOIN};

    chat_messages[message_count++] = (struct chat_message){"Alice", "Hey Bob!", MESSAGE};

    chat_messages[message_count++] = (struct chat_message){"Bob", "Hey Alice!", MESSAGE};

    update_user_status("Alice", 0);
    chat_messages[message_count++] = (struct chat_message){"Alice", "", LEAVE};

    update_user_status("Bob", 0);
    chat_messages[message_count++] = (struct chat_message){"Bob", "", LEAVE};

    for (int i = 0; i < message_count; i++) {
        print_message(&chat_messages[i]);
    }

    print_online_users();
}
