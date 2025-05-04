#include <stdio.h>

#define MAX_MESSAGES 100

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

struct Message chat[MAX_MESSAGES];

int counter = 0;

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

int main() {
    chat[counter++] = (struct Message) {
        "Alice", "", JOIN
    };

    chat[counter++] = (struct Message) {
        "Alice", "Hey Bob!", MESSAGE
    };

    chat[counter++] = (struct Message) {
        "Bob", "", JOIN
    };

    chat[counter++] = (struct Message) {
        "Bob", "Hey Alice!", MESSAGE
    };

    chat[counter++] = (struct Message) {
        "Alice", "", LEAVE
    };


    for(int i = 0; i < counter; i++) {
        printMessage(&chat[i]);
    }
}
