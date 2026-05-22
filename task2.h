#ifndef TASK2_H
#define TASK2_H

#include <stdlib.h>
#include "common.h"

//meci intre 2 echipe
typedef struct {
    Team team1;
    Team team2;
} Match;

//nod pentru coada de meciuri
typedef struct matchNode {
    Match match;
    struct matchNode *next;
} MatchNode;

//nod pentru stiva de castigatoare
typedef struct stackNode {
    Team team;
    struct stackNode *next;
} StackNode;

void addMatch(MatchNode **queue, Match m) {
    MatchNode *newNode = (MatchNode*)malloc(sizeof(MatchNode));

    newNode->match = m;
    newNode->next = NULL;

    if(*queue == NULL) {
        *queue = newNode;
        return;
    }

    MatchNode *current = *queue;
    while(current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

Match removeMatch(MatchNode **queue) {
    Match m = (*queue)->match;
    MatchNode *toDelete = *queue;
    *queue = (*queue)->next;
    free(toDelete);
    return m;
}

void push(StackNode **stack, Team t) {
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));

    newNode->team = t;
    newNode->next = *stack;
    *stack = newNode;
}

Team pop(StackNode **stack) {
    Team t = (*stack)->team;
    StackNode *toDelete = *stack;
    *stack = (*stack)->next;
    free(toDelete);
    return t;
}

int stackLength(StackNode *stack) {
    int count = 0;
    while(stack != NULL) {
        count++;
        stack = stack->next;
    }
    return count;
}

#endif