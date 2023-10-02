#pragma once

#include <stdlib.h>

#include <arpa/inet.h>

#define BUFSZ 1024
#define ROWS 4
#define COLS 4

enum ActionType {
    START,
    REVEAL,
    FLAG_ACTION,
    STATE,
    REMOVE_FLAG,
    RESET,
    WIN,
    EXIT,
    GAME_OVER
};

typedef struct Message {
    int type;
    int coordinates[2];
    int board[ROWS][COLS];
} Message;

void logexit(const char *msg);

int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage);

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init(const char *proto, const char *portstr,
                         struct sockaddr_storage *storage);
