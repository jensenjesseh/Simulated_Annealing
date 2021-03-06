#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <time.h>
#include <cstring>
#include <fstream>
#include <deque>

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

void anneal(std::deque<position> current, std::deque<edge> edges, int v);
void copy(std::deque<position> current, std::deque<position> next, int numEvents);
void alter(std::deque<position> next, int v);
int computeScore(std::deque<position> next, std::deque<edge> edges, int v);
void accept(int *currScore, int nextScore, std::deque<position> current, std::deque<position> next, float temperature, int v);
float adjustTemp();

int main(int argc, char *argv[]){

	//open files
	std::ifstream inputfile(argv[1]);
    std::ofstream outputfile(argv[2]);
    //file error checking
    if (!inputfile)
    {
        std::cout << "Error opening input file " << argv[1] << "\n";
    }
    if (!outputfile)
    {
        std::cout << "Error opening output file " << argv[2] << "\n";
    }
	
	//parse input file and store values
	int gx,gy,v, start, end;
	char c = '0';

	inputfile >> c;
	inputfile >> gx;
	inputfile >> gy;
	inputfile >> c;
	inputfile >> v;

	std::deque<edge> edges;

	for (int i = 0; i < v-1; i++)
	{
        edge temp;
		inputfile >> c;
		inputfile >> temp.start;
        inputfile >> temp.end;
        edges.push_back(temp);
		
	}
	
	std::deque<position> current;

	int xPos, yPos, count;
	
	xPos = 0;
	yPos = 0;
    //position current[v]; // fill current with all vertices (initial solution)
    //create initial solution. Just fills in grid in order
	count = 0;
    while(count < v){
		if(xPos == gx){
			xPos = 0;
			yPos = yPos + 1;
		}
            position temp;
            temp.xPos = xPos;
            temp.yPos = yPos;
            current.push_back(temp);
			xPos++;
			count++;
    }
    printf("Initial order:\n");
    for (int i=0; i<v; i++)
    {
        printf("%d", i);
    }
        
    srand(time(NULL));
    anneal(current, edges, v);
}

void anneal(std::deque<position> current,std::deque<edge> edges, int numEvents){
    float T;
    int currScore, nextScore;
    std::deque<position> next; //numEvents will be the number of vertices
    int i;

    i = 0;
    T = INITIAL_TEMPERATURE;
    currScore = computeScore(current, edges, numEvents); //Produces score
    printf("\nInitial score: %d\n", currScore);
    while(T > STOP_THRESHOLD){
        //std::memcpy(next, current, sizeof(next));
        copy(current, next, numEvents);
        alter(next, numEvents);
        nextScore = computeScore(next, edges, numEvents);
        accept(&currScore, nextScore, current, next, T, numEvents);
        T = adjustTemp();
        i++;
    }
    printf("\nExplored %d solutions\n", i);
	
	for (int i = 0; i < numEvents; i++){
		printf("Node %d placed at (%d, %d)\n", i, current[i].xPos, current[i].yPos); 
	}
	
	for (int i = 0; i < numEvents -1; i++){
		printf("Edge from %d to %d has length %d\n", edges[i].start, edges[i].end, edges[i].length);
	}
	
    printf("Final score: %d\n", currScore);
}

int computeScore(std::deque<position> next, std::deque<edge> edges, int numEvents){
    
    //const int x_pos[numEvents] = {}; //What values do I initialize these to?
    //const int y_pos[numEvents] = {}; 
    int distance;

    distance = 0;
	for (int i = 0; i < numEvents; i++){
		edges[i].length = abs(next[edges[i].end].xPos - next[edges[i].start].xPos) + abs(next[edges[i].end].yPos - next[edges[i].start].yPos);
	}
    for(int i = 0; i<numEvents - 1; i++){
        distance += pow(edges[i].length, 2);
    }
    return distance;
}

void alter(std::deque<position> next,int numEvents){
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

void accept(int *currScore, int nextScore, std::deque<position> current, std::deque<position> next, float T, int numEvents){
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

void copy(std::deque<position> current, std::deque<position> next, int numEvents)
{
    for (int i = 0; i < numEvents; i++)
    {
        next[i] = current[i];
    }
}