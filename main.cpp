#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <time.h>

#define INITIAL_TEMPERATURE 10000
#define COOLING_RATE 0.9999
#define STOP_THRESHOLD 0.0001

struct position
{
    int xPos;
    int yPos;
}

void anneal(int *current);
void copy(int *current, int *next);
void alter(int *next);
int evaluate(int *next);
void accept(int *currScore, int nextXcore, int *current, int *next, float temperature);
float adjustTemperature();

int main(int argc, char *argv[]){

    //TODO: input grid size g, vertices v, and all edges from file;
    int vertices[v];
    int gx, gy; 
    //for (int i = 0; i < v; i++){
    //    vertices[i] = i;
    //}

    static position current[v]; // fill current with all vertices (initial solution)
    //std::memcpy(current, vertices, sizeof(current));
    for (int i = 0; i<gy; i++){     //create initial solution. Just fills in grid in order
        for(int j = 0; j < gx; j++){
            current[i].xPos = i;
            current[i].yPos = j;
        }
    }

    printf("Initial order:\n");
    for (i=0; i<MAX_EVENTS; i++)
    {
        printf("%d ", current[i]);
    }

    //Loop
        //TODO:generate new solution
        //TODO:score new solution
        //TODO:If new better than old replace old solution with new
            //TODO:Else
                //TODO:ompute ΔE (ΔE = |scoreold− scorenew|)
                //TODO:compute acceptance probability (p = e-ΔE/T)
                //TODO:generate random probability (r)
                //TODO:If (r ≤ p)replace old solution with new
        //TODO: Lower T
        // TODO:End Loop when T is below threshold
        
    srand(time(NULL));
    anneal(current);
}

void anneal(position *current, int numEvents){
    float T;
    int currScore, nextScore;
    position next[numEvents]; //numEvents will be the number of vertices
    int i;

    i = 0;
    T = INITIAL_TEMPERATURE;
    currScore = computeScore(current); //Produces score
    printf("\nInitial score: %d\n", currScore);
    while(T > STOP_THRESHOLD){
        std::memcpy(next, current, sizeof(next));
        alter(next);
        nextScore = computeScore(next);
        accept(&currScore, nextScore, current, next, T);
        T = adjustTemperature();
        i++;
    }
    printf("\nExplored %d solutions\n", i);
    printf("Final score: %d\n", currScore);
}

int computeScore(int *next, numEvents){
    
    //const int x_pos[numEvents] = {}; //What values do I initialize these to?
    //const int y_pos[numEvents] = {}; 
    int distance;

    distance = 0;
    for(int i = 0; i<numEvents - 1; i++){
        distance += pow(abs(next[i].xPos - next[i+1].xPos) + abs(next[i].yPos - next[i + 1].yPos), 2);
    }
    return distance;
}

void alter(int *next, numEvents){
    int a,b,temp;
    a = rand() % numEvents;
    b = rand() % numEvents;
    temp = next[a];
    next[a] = next[b];
    next[b] = temp;
}

float adjustTemp(){
    static float T = INITIAL_TEMPERATURE;

    T =T*COOLING_RATE;
    return T;
}

void accept(int *currScore, int nextScore, position* current, int* next, float T, int numEvents){
    int delta_e, i;
    float p, r;

    delta_e = nextScore - *currScore;

    if(delta_e <= 0)
    {
        for (int i = 0; i <numEvents; i++){
            current[i] = next[i];
        }
        *currScore = nextScore
    }

    else
    {
        p = exp(-((float)delta_e)/T);
        r = (float) rand()/(float) RAND_MAX;
        if (r < p){
            for (int i = 0; i < numEvents; i++){
                current[i] = next[i];
            }
            *currScore = nextScore;
        }
    }
}
