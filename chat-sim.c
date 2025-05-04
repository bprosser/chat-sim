#include <stdio.h>
#include <string.h>

#define MAX_MESSAGES 100
#define MAX_USERS 10

enum messageType {
    JOIN,
    LEAVE,
    MESSAGE
};

struct Message {
    char sender[32];
    char content[128];
    enum messageType type;
};

struct User {
    char name[32];
    int online;
};

struct Message chat[MAX_MESSAGES];
struct User users[MAX_USERS];

int message_count = 0;
int user_count = 0;

void printMessage(struct Message *msg) {
    switch(msg->type) {
    case JOIN:
        printf("[%s] joined the chat\n",msg->sender);
        break;
    case LEAVE:
        printf("[%s] left the chat\n",msg->sender);
        break;
    case MESSAGE:
        printf("[%s]: %s\n",msg->sender,msg->content);
        break;
    default:
        printf("Invalid msg\n");
        break;
    }
}

void updateUserStatus(const char *name, int online) {
    for(int i = 0; i < user_count; i++) {
        if(strcmp(name,users[i].name) == 0) {
            users[i].online = online;
            return;
        }
    }
    if(online==1) {
        strcpy(users[user_count].name,name);
        users[user_count++].online = 1;
    }
}

void printOnlineUsers(void) {
    int found = 0;
    for(int i = 0; i < user_count; i++) {
        if(users[i].online == 1) {
            if(!found) {
                printf("\nUsers still online:\n");
                found = 1;
            }
            printf("- %s\n",users[i].name);
        }
    }
    if(!found)
    {
        printf("No users currently online.\n");
    }
}

int main() {
    updateUserStatus("Alice",1);
    chat[message_count++] = (struct Message) {
        "Alice", "", JOIN
    };

    updateUserStatus("Bob",1);
    chat[message_count++] = (struct Message) {
        "Bob", "", JOIN
    };

    chat[message_count++] = (struct Message) {
        "Alice", "Hey Bob!", MESSAGE
    };

    chat[message_count++] = (struct Message) {
        "Bob", "Hey Alice!", MESSAGE
    };

    updateUserStatus("Alice",0);
    chat[message_count++] = (struct Message) {
        "Alice", "", LEAVE
    };

    updateUserStatus("Bob",0);
    chat[message_count++] = (struct Message) {
        "Bob", "", LEAVE
    };

    for(int i = 0; i < message_count; i++) {
        printMessage(&chat[i]);
    }

    printOnlineUsers();
}
