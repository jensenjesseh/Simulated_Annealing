#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX_EVENTS 20
#define INITIAL_TEMPERATURE 10000
#define COOLING_RATE 0.9999
#define STOP_THRESHOLD 0.0001

void anneal(int *current);
void copy(int *current, int *next);
void alter(int *next);
int evaluate(int *next);
void accept(int *current_val, int next_val, int *current, int *next, float temperature);
float adjustTemperature();

int main(int argc, char *argv[]){

//TODO: input grid size g, vertices v, and all edges
int vertices[v]; 
for (int i = 0; i < v; i++){
    vertices[i] = i;
}

static int current[v] = vertices; // fill current with all vertices

printf("Initial order:\n");
for (i=0; i<MAX_EVENTS; i++)
{
	printf("%d ", current[i]);
}
	
srand(time(NULL));
anneal(current);
}

