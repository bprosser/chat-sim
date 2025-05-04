#include <stdio.h>

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
    struct Message msg = {"alice", "", JOIN};
    printMessage(&msg);
    struct Message msg2 = {"bob", "", LEAVE};
    printMessage(&msg2);
    struct Message msg3 = {"charlie", "Hello world!", MESSAGE};
    printMessage(&msg3);
}
