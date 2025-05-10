#include <stdio.h>
#include <string.h>

#define MAX_CHAT_MESSAGES 100
#define MAX_CHAT_USERS 10
#define USER_DATA_FILE "users.txt"

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
                printf("chat_users still online:\n");
                found = 1;
            }
            printf("- %s\n", chat_users[i].name);
        }
    }
    if (!found) {
        printf("No chat_users currently online.\n");
    }
}

void load_users_from_file(void) {
    FILE *file = fopen(USER_DATA_FILE, "r");
    if (file == NULL) {
        printf("Warning: %s not found, starting with no users.\n", USER_DATA_FILE);
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Use the string tokenizer (strtok) function to split the string into tokens
        // First call: pass the full string
        // Subsequent calls: pass NULL to continue from the previous position
        char *username = strtok(buffer, ",");
        char *status = strtok(NULL, ",");

        if (username == NULL || status == NULL) {
            fprintf(stderr, "Malformed line: %s", buffer);
            continue;
        }

        // Use the string complement span (strcspn) function to find the index of the first newline
        // or carriage return, and replace with '\0' to clean the string

        username[strcspn(username, "\r\n")] = '\0';
        status[strcspn(status, "\r\n")] = '\0';

        int online = -1;
        if (strcmp(status, "online") == 0)
            online = 1;
        else if (strcmp(status, "offline") == 0)
            online = 0;
        else {
            fprintf(stderr, "Warning: unknown status '%s' for user '%s'\n", status, username);
            continue;
        }

        if (user_count < MAX_CHAT_USERS) {
            strcpy(chat_users[user_count].name, username);
            chat_users[user_count].online = online;
            user_count++;
        } else {
            fprintf(stderr, "User limit reached - skipping '%s'\n", username);
        }
    }
    fclose(file);
}

void save_users_to_file(void) {
    FILE *file = fopen(USER_DATA_FILE, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        if (chat_users[i].name[0] != '\0') {
            const char *status_str = (chat_users[i].online) ? "online" : "offline";
            fprintf(file, "%s,%s\r\n", chat_users[i].name, status_str);
        }
    }
    fclose(file);
}

void log_chat_event(char *sender, char *content, enum message_type type) {
    strcpy(chat_messages[message_count].sender, sender);
    strcpy(chat_messages[message_count].content, content);
    chat_messages[message_count].type = type;
    message_count++;
    print_message(&chat_messages[message_count - 1]);
}

int main() {
    load_users_from_file();
    print_online_users();
    char buffer[128];
    char *result;
    do {
        printf("> ");
        result = fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        char *command = strtok(buffer, " ");
        char *args = strtok(NULL, "");
        if (strcmp(command, "join") == 0) {
            log_chat_event(args, "", JOIN);
            update_user_status(args, 1);
        } else if (strcmp(command, "send") == 0) {
            char *send_name = strtok(args, " ");
            char *send_msg = strtok(NULL, "");
            log_chat_event(send_name, send_msg, MESSAGE);
        } else if (strcmp(command, "list") == 0) {
            print_online_users();
        } else if (strcmp(command, "leave") == 0) {
            log_chat_event(args, "", LEAVE);
            update_user_status(args, 0);
            print_online_users();
        } else if (strcmp(command, "exit") == 0) {
            save_users_to_file();
            return 0;
        }
    } while (result != NULL);
    return 0;
}
