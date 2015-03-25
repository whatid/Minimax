#ifndef WARGAME_H
#define WARGAME_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std; 
#define infinity 1<<10


typedef struct
{
	int x; 
	int y; 
} Pos;

// blue = max; 
// green = min; 
typedef enum square 
{
	empty, blue, green
} square;


int minimax(int ** score, square ** board, bool maxPlayer, Pos prev, int depth); 

	


#endif