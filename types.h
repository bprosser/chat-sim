#ifndef TYPES_H
#define TYPES_H

enum message_type {
    JOIN,
    LEAVE,
    MESSAGE
};

struct chat_user {
    char name[32];
    int online;
};

struct chat_message {
    char sender[32];
    char content[128];
    enum message_type type;
};

#endif

