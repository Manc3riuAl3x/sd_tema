#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "task2.h"
#include "task3.h"

Node* createTeam(Team t) {
    Node* newTeam = (Node*)malloc(sizeof(Node));

    newTeam->team = t;
    newTeam->next = NULL;
    return newTeam;
}

//Adaug echipele din fisierul d.in in lista
void insertTeam(Node **head, Team t) {
    Node* newTeam = createTeam(t);
    newTeam->next = *head;
    *head = newTeam;
}

int listLength(Node *head) {
    int count = 0;
    Node* current = head;

    while(current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

int powerOfTwo(int nrTeams) {
    int result = 1;

    while(result * 2 <= nrTeams) {
        result *= 2;
    }
    
    return result;
}

void eraseMin(Node **head) {
    float minScore = (*head)->team.score;

    Node *current = (*head)->next;
    while(current != NULL) {
        if(current->team.score < minScore) {
            minScore = current->team.score;
        }
        current = current->next;
    }

    //daca head-ul e minim:
    if((*head)->team.score == minScore) {
        Node *delete = *head;
        *head = (*head)->next;
        free(delete->team.players);
        free(delete);
        return;
    }

    //daca minimul este undeva prin lista:
    current = *head;
    while(current->next != NULL) {
        if(current->next->team.score == minScore) {
            Node *delete = current->next;
            current->next = delete->next;
            free(delete->team.players);
            free(delete);
        return;
        }
        current = current->next;
    }
}

Node* taskk1(FILE *d, FILE *out) {
    int nrTeams; //numar de echipe
    fscanf(d, "%d", &nrTeams);
    fgetc(d);

    Node *head = NULL;

    for(int i = 0; i < nrTeams; i++) {
        Team t;
        fscanf(d, "%d", &t.nrPlayer); //citesc numarul de jucatori
        fgetc(d);
        fgets(t.teamName, 50, d); //citesc numele echipei
        t.teamName[strcspn(t.teamName, "\n")] = 0; //sterg newline-ul de la sfarsit
        int len = strlen(t.teamName);
        while(len > 0 && t.teamName[len-1] == ' ') {
            t.teamName[len-1] = 0;
            len--;
        }
        
        t.players = malloc(t.nrPlayer * sizeof(Player));
        for(int j = 0; j < t.nrPlayer; j++) {
            fscanf(d, "%s %s %d", t.players[j].firstName,
                                t.players[j].secondName,
                                &t.players[j].points);
        }
        int total = 0;
        for(int j = 0; j < t.nrPlayer; j++) {
            total += t.players[j].points;
        }
        t.score = (float)total / t.nrPlayer;
        insertTeam(&head, t);
    }

    //elimin echipele pana raman la o putere a lui 2
    int hit = powerOfTwo(nrTeams);
    while(listLength(head) > hit) {
        eraseMin(&head);
    }
    Node *current = head;
    while(current != NULL) {
        fprintf(out, "%s\n", current->team.teamName);
        current = current->next;
    }

    return head;
}

Node* task2(Node *list, FILE *out) {
    MatchNode *queue = NULL;
    StackNode *stack = NULL;
    Node *top8 = NULL;

    Node *current = list;
    while(current != NULL && current->next != NULL) {
        Match m;
        m.team1 = current->team;
        m.team2 = current->next->team;
        addMatch(&queue, m);
        current = current->next->next;
    }

    int round = 1;
    while(queue != NULL) {
        fprintf(out, "\n--- ROUND NO:%d\n", round);
        MatchNode *temp = queue;
        while(temp != NULL) {
            fprintf(out, "%-33s-%33s\n", temp->match.team1.teamName, temp->match.team2.teamName);
            temp = temp->next;
        }

        fprintf(out, "\nWINNERS OF ROUND NO:%d\n", round);
        while(queue != NULL) {
            Match m = removeMatch(&queue);
            Team winner;
            if(m.team1.score > m.team2.score) {
                winner = m.team1;
            } else {
                winner = m.team2;
            }
            for(int i = 0; i < winner.nrPlayer; i++) {
                winner.players[i].points++;
            }
            int total = 0;
            for(int i = 0; i < winner.nrPlayer; i++) {
                total += winner.players[i].points;
            }
            winner.score = (float)total / winner.nrPlayer;
            push(&stack, winner);
        }

        StackNode *s = stack;
        while(s != NULL) {
            fprintf(out, "%-33s -  %.2f\n", s->team.teamName, s->team.score);
            s = s->next;
        }

        // salveaza top8 cand stiva are exact 8 echipe
        if(stackLength(stack) == 8 && top8 == NULL) {
            StackNode *s2 = stack;
            while(s2 != NULL) {
                insertTeam(&top8, s2->team);
                s2 = s2->next;
            }
        }

        while(stack != NULL && stack->next != NULL) {
            Team t2 = pop(&stack);
            Team t1 = pop(&stack);
            Match m;
            m.team1 = t2;
            m.team2 = t1;
            addMatch(&queue, m);
        }

        round++;
    }

    return top8;
}

void task3(Node *top8, FILE *out) {
    BSTNode *root = NULL;
    Node *current = top8;
    while(current != NULL) {
        root = insertBST(root, current->team);
        current = current->next;
    }
    fprintf(out, "\nTOP 8 TEAMS:\n");
    inorderReverse(root, out);
}

int main(int argc, char *argv[]) {
    if(argc < 4) {
        printf("./lanParty foloseste: c.in, d.in, out.out\n");
        return 1;
    }

    FILE *c = fopen(argv[1], "r"); //datele din c.in
    FILE *d = fopen(argv[2], "r"); //datele din d.in
    FILE *out = fopen(argv[3], "w"); //output-ul

    int task1, t2, tk3, task4;
    fscanf(c, "%d %d %d %d", &task1, &t2, &tk3, &task4);

    Node *list = NULL;
    if(task1 == 1) {
        list = taskk1(d, out);
    }

    Node *top8 = NULL;
    if(t2 == 1) {
        top8 = task2(list, out);
    }
    if(tk3 == 1) {
        task3(top8, out);
    }

    fclose(c);
    fclose(d);
    fclose(out);
    return 0;
}