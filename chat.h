#ifndef CHAT_H
#define CHAT_H

#include "config.h"
#include "types.h"

extern int user_count;
extern int message_count;

extern struct chat_message chat_messages[MAX_CHAT_MESSAGES];
extern struct chat_user chat_users[MAX_CHAT_USERS];

void update_user_status(const char *name, int online);

void print_online_users(void);

void log_chat_event(char *sender, char *content, enum message_type type);

#endif
