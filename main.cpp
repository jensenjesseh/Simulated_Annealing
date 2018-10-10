#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <time.h>
#include <cstring>

#define INITIAL_TEMPERATURE 10000
#define COOLING_RATE 0.9999
#define STOP_THRESHOLD 0.0001

struct position
{
    int xPos;
    int yPos;
};

struct edge
{
	int start;
	int end;
	int length;
};

void anneal(position *current);
void copy(position *current, position *next);
void alter(position *next);
int computeScore(position *next, edge* edges, int v);
void accept(int *currScore, int nextXcore, position *current, position *next, float temperature);
float adjustTemperature();

int main(int argc, char *argv[]){

    //TODO: input grid size g, vertices v, and all edges e from file;
    int vertices[v];
	position current[v];
	edge edges[v-1];
    int gx, gy; 
	int xPos, yPos, count;
	
	xPos = 0;
	yPos = 0;
    position current[v]; // fill current with all vertices (initial solution)
    //create initial solution. Just fills in grid in order
	count = 0;
    while(count < v){
		if(xPos == gx){
			xPos = 0;
			yPos = yPos + 1;
		}
            current[count].xPos = xPos;
			current[count].yPos = yPos;
			xPos++;
			count++;
    }
    printf("Initial order:\n");
    for (int i=0; i<v; i++)
    {
        printf("%d ", current[i]);
    }
        
    srand(time(NULL));
    anneal(current);
}

void anneal(position *current,edge* edges, int numEvents){
    float T;
    int currScore, nextScore;
    position next[numEvents]; //numEvents will be the number of vertices
    int i;

    i = 0;
    T = INITIAL_TEMPERATURE;
    currScore = computeScore(current, edges, v); //Produces score
    printf("\nInitial score: %d\n", currScore);
    while(T > STOP_THRESHOLD){
        std::memcpy(next, current, sizeof(next));
        alter(next, v);
        nextScore = computeScore(next, edges, v);
        accept(&currScore, nextScore, current, next, T);
        T = adjustTemperature();
        i++;
    }
    printf("\nExplored %d solutions\n", i);
    printf("Final score: %d\n", currScore);
}

int computeScore(position *next, edge* edges, int numEvents){
    
    //const int x_pos[numEvents] = {}; //What values do I initialize these to?
    //const int y_pos[numEvents] = {}; 
    int distance;

    distance = 0;
	for (int i = 0; i < numEvents; i++){
		edges[i].length = abs(next[edges[i].end].xPos - next[edges[i].end].xPos) + abs(next[edges[i].end].yPos - next[edges[i].start].yPos);
	}
    for(int i = 0; i<numEvents - 1; i++){
        distance += pow(edges[i].length, 2);
    }
    return distance;
}

void alter(position *next,int numEvents){
    int a,b;
	position temp;
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

void accept(int *currScore, int nextScore, position* current, position* next, float T, int numEvents){
    int delta_e, i;
    float p, r;

    delta_e = nextScore - *currScore;

    if(delta_e <= 0)
    {
        for (int i = 0; i <numEvents; i++){
            current[i] = next[i];
        }
        *currScore = nextScore;
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
