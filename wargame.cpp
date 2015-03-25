#include "wargame.h"

int main(int argc, char *argv[]) {

	// open file 
	ifstream file (argv[1]);

	if (!file) {
		cout<<"Error: invalid file"<<endl; 
		return 0; 
	}

	// declare empty 1d array 
	int ** matrix = new int * [6];
	for (int i = 0; i < 6; i++) {
		matrix[i] = new int[6]; 
	} 
	int idx = 0; 
	// parse txt file 
	for (int num = 0; num < 6; num++) {
		int temp = 0; 
		string line; 
		int input;  
		getline(file, line);
		istringstream in (line); 
		while (in >> input){
			matrix[idx][temp++] = input; 
		}
		idx++; 
	}	

	// setup square array 
	square ** playerboard = new square * [6]; 
	for (int i = 0; i < 6; i++) {
		playerboard[i] = new square[6]; 
	} 
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 6; y++) {
			playerboard[x][y] = empty; 	 
		}
	}

	// initial call 
	// max = blue 
	// blue moves first 

	Pos none; 
	minimax(matrix, playerboard, true, none, 3);

	cout << "no segfault in minimax";

	// print out the final state of the board. 
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 6; y++) {
			if (playerboard[x][y] == blue)
				cout<<"blue "; 
			else 
				cout<<"green ";
		}
		cout << "\n";
	}

}

int minimax(int ** score, square ** board, bool maxPlayer, Pos prev, int depth) {

	// declare variables 
	int result, bestValue, x, y, maxOptimal, bx, by; 
	bool finished = true; 
	Pos latest; 

	// base case
	// board is full 
	for (bx = 0; bx < 6; bx++) {
		for (by = 0; by < 6; by++) {
			if (board[bx][by] == empty) {
				finished = false; 
				break;
			}
		}
	}
	if (finished || depth == 0)
		return score[prev.x][prev.y];


	if(maxPlayer) {
		bestValue = -infinity; 
		
		// all possible moves for max
		for (x = 0; x < 6; x++) {
			for (y = 0; y < 6; y++) {
				// pick a square that is empty and conquer it
				if (board[x][y] == empty) {
					board[x][y] = blue; 
					latest.x = x; 
					latest.y = y; 
				} 
				// check neighboring squares for possible death blitz move
				if(board[x-1][y] == blue || board[x+1][y] == blue || board[x][y-1] == blue || board[x][y+1] == blue) {

					if (board[x-1][y] == green) board[x-1][y] = blue; 
					if (board[x+1][y] == green) board[x+1][y] = blue; 
					if (board[x][y-1] == green) board[x][y-1] = blue; 
					if (board[x][y+1] == green) board[x][y+1] = blue; 
				}

				// do this recursively
				result = minimax(score, board, false, latest, depth-1);

				// check if my value is greater than any of the bestValues found so far. 
				if (result > bestValue) {
					bestValue = result;  
				}
			}
		}

		return bestValue; 
	}

	else {
		bestValue = infinity; 

		// all possible moves for min
		for (x = 0; x < 6; x++) {
			for (y = 0; y < 6; y++) {
				// pick a square that is empty and conquer it
				if (board[x][y] == empty) {
					board[x][y] = green; 
					latest.x = x; 
					latest.y = y; 

				} 
				// check neighboring squares for possible death blitz move
				if(board[x-1][y] == green || board[x+1][y] == green || board[x][y-1] == green || board[x][y+1] == green) {

					if (board[x-1][y] == blue) board[x-1][y] = green; 
					if (board[x+1][y] == blue) board[x+1][y] = green; 
					if (board[x][y-1] == blue) board[x][y-1] = green; 
					if (board[x][y+1] == blue) board[x][y+1] = green; 
				}

				result = minimax(score, board, true, latest, depth-1);

				if (result < bestValue) {
					bestValue = result;  
				}
			}
		}
		return bestValue; 
	}
	
}

