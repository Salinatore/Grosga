/**
 * @file 6_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 05/11/23
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/** Table **/
#define NA 4 //Actions number
#define NR 5 //Rows numberzz
#define NC 6 //Cols number
#define Q_LENGTH (NC * NR)  // Q-table's length

/** Game rules **/
#define VOID (-1)
#define MINE (-100)
#define POWER 1
#define END 100

/** Training Settings **/
#define MAX_TRAINING_STEP (-1)
#define MAX_TRAINING_EXPERIMENT 10000000
#define LEARNING_RATE 0.1
#define DISCOUNT_RATE 0.99

void initializeQTable(float q_table[Q_LENGTH][NA]); //
void printTable(float q_table[Q_LENGTH][NA]);

int main() {
    srand(time(NULL));
    int map[NR][NC] = {
            {VOID,  VOID,   POWER,  VOID,   VOID,   VOID},
            {VOID,  MINE,   VOID,   VOID,   MINE,   VOID},
            {VOID,  VOID,   POWER,  VOID,   VOID,   POWER},
            {MINE,  VOID,   VOID,    MINE,   VOID,   VOID},
            {VOID,  POWER,  VOID,    VOID,   END,    VOID},
    };

    int moveDirection[NA][2] = {
            {-1, 0}, //up
            {0, 1},  //right
            {1, 0},  //down
            {0, -1}, //left
    };

    float q_table[Q_LENGTH][NA];
    initializeQTable(q_table);

    int start_row = 0, start_col = 0; //Initial position of the robot = top-left
    int current_row = start_row, current_col = start_col;
    int next_row, next_col;
    float eps = 100, immediate_reward = 0;
    int trainingSteps = 0, trainingExperiment = 0; //number of training loop

    int i, first;
    int current_state = start_row * NC + start_col;
    float maxReward, nextState;

    /** Training **/
    while(trainingExperiment < MAX_TRAINING_EXPERIMENT) {
        trainingSteps++; //count
        int action = 0; //reset

        /** Epsilon greedy */
        int r = rand() % 100 + 1; //eps = 100
        if(r <= eps) {
            first = 1;
            for(i = 0; i < NA; i++) {
                next_row = current_row + moveDirection[i][0];
                next_col = current_col + moveDirection[i][1];

                if((next_row >= 0 && next_row < NR) && (next_col >= 0 && next_col < NC))
                    if(first || q_table[current_state][i] > maxReward) {
                        maxReward = q_table[current_state][i];
                        action = i;
                        first = 0;
                    }
            }
        } else {
            int check = 0; // find the right way
            int actionRandomCheck[] = {0, 0, 0, 0}; //check if the action is already used

            while(!check) {
                do {
                    action = rand() % 4;
                } while(actionRandomCheck[action] == 1);

                actionRandomCheck[action] = 1; // -> checked
                next_row = current_row + moveDirection[action][0];
                next_col = current_col + moveDirection[action][1];

                if((next_row >= 0 && next_row < NR) && (next_col >= 0 && next_col < NC))
                    check = 1;
            }
        }

        current_row += moveDirection[action][0];
        current_col += moveDirection[action][1];
        immediate_reward = map[current_row][current_col];
        int new_state = current_row * NC + current_col;
        nextState = 0;
        first = 1;

        for(i = 0; i < NA; i++) {
            next_row = current_row + moveDirection[i][0];
            next_col = current_col + moveDirection[i][1];
            if((next_row >= 0 && next_row < NR) && (next_col >= 0 && next_col < NC))
                if(first || q_table[new_state][i] > nextState) {
                    nextState = q_table[new_state][i];
                    first = 0;
                }
        }

        /** Q_table update **/
        q_table[current_state][action] = q_table[current_state][action] + LEARNING_RATE * (immediate_reward + DISCOUNT_RATE * nextState - q_table[current_state][action]);

        if(map[current_row][current_col] == MINE || map[current_row][current_col] == END || (MAX_TRAINING_STEP > 0 && trainingSteps > MAX_TRAINING_STEP)) {
            trainingSteps = 0;
            current_state = start_row * NC + start_col;
            current_row = start_row;
            current_col = start_col;
            trainingExperiment++;
            eps -= 100.0 / MAX_TRAINING_EXPERIMENT;
        } else
            current_state = new_state;
    }

    printf("\nUpdated Q-Table:\n");
    printTable(q_table);

    return 0;
}

void initializeQTable(float q_table[Q_LENGTH][NA]) {
    for(int row = 0; row < Q_LENGTH; row++)
        for(int col = 0; col < NA; col++)
            q_table[row][col] = 0;
}

void printTable(float q_table[Q_LENGTH][NA]) {
    for(int row = 0; row < Q_LENGTH; row++) {
        for(int col = 0; col < NA; col++)
            printf("%3.2f ", q_table[row][col]);
        printf("\n");
    }
}