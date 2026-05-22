#ifndef COMMON_H
#define COMMON_H

typedef struct {
    char firstName[30];
    char secondName[30];
    int points;
} Player;

typedef struct {
    char teamName[50];
    int nrPlayer;
    Player *players;
    float score;
} Team;

typedef struct node {
    Team team;
    struct node *next;
} Node;

#endif