#ifndef WARGAME_H
#define WARGAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std; 
#define infinity 1<<10
#define BLACK "\0x33[0;30m"
#define BLUE  "\033[0;34m"
#define GREEN "\033[0;32m"

// blue = max; 
// green = min; 
typedef enum square 
{
	empty, blue, green
} square;

// minimax bot 
int minimax(int ** score, square ** board, bool maxPlayer, int leaf_node, int maxDepth, int depth, int &nodes_expanded); 

// alphabeta bot 
int alphabeta(int ** score, square ** board, bool maxPlayer, int &alpha, int &beta, int leaf_node, int maxDepth, int depth, int &nodes_expanded);

int maxOptimalX, maxOptimalY, minOptimalX, minOptimalY; 


#endif