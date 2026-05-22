#ifndef TASK3_H
#define TASK3_H

#include "common.h"

typedef struct bstNode {
    Team team;
    struct bstNode *left;
    struct bstNode *right;
} BSTNode;

BSTNode* insertBST(BSTNode *root, Team t) {
    if(root == NULL) {
        BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->team = t;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if(t.score > root->team.score) {
        root->right = insertBST(root->right, t);
    } else if(t.score < root->team.score) {
        root->left = insertBST(root->left, t);
    } else {
        // scoruri egale - comparam dupa nume descrescator
        if(strcmp(t.teamName, root->team.teamName) > 0) {
            root->right = insertBST(root->right, t);
        } else {
            root->left = insertBST(root->left, t);
        }
    }
    return root;
}

void inorderReverse(BSTNode *root, FILE *out) {
    if(root == NULL) return;
    inorderReverse(root->right, out);
    fprintf(out, "%-33s -  %.2f\n", root->team.teamName, root->team.score);
    inorderReverse(root->left, out);
}

#endif