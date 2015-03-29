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

	// test 
//	for (int moves = 0; moves < 36; moves++){
//		if (moves % 2 == 0) {
			// max moves
			minimax(matrix, playerboard, true, 0, 3, 3);
			playerboard[maxOptimalX][maxOptimalY] = blue; 
			// print out the state of the board. 
//		}
//		else {
			// min moves
	//		minimax(matrix, playerboard, false, 0, 3, 3); 
//			cout<<minOptimalX<<minOptimalY; 
//			playerboard[minOptimalX][minOptimalY] = green; 
//		}
//	}

	

	cout << "no segfault in minimax" << endl; 


	// print out the state of the board. 
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 6; y++) {
			if (playerboard[x][y] == blue)
				cout << "blue  "; 
			else if (playerboard[x][y] == green) 
				cout << "green ";
			else 
				cout<<"empty ";
		}
		cout << "\n";
	}
	

}

int minimax(int ** score, square ** board, bool maxPlayer, int leaf_node, int maxDepth, int depth) {

	// declare variables 
	int result, x, y, bx, by; 
	bool finished = true; 
	bool left = false, right = false, top = false, bottom = false; 
	int maxScore = -infinity, minScore = infinity; 
	



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
	//cout << "depth after recursion" << depth; 
	//cout<<__LINE__<<endl; 
	if (finished) {
		return leaf_node;
	}
	else {
		// evaluation counts the total number of squares conquered by either max or min
		// and the resulting score and compares that with the other player. 
		// percentage likelihood of winning. 
		// return result of eval function 
		if (depth == 0) {
			int curMax = 0, curMin = 0; 
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					if (board[i][j] == blue)
						curMax += score[i][j]; 
					if (board[i][j] == green)
						curMin += score[i][j]; 	
				}
			}
			// should be the opposite 
			//cout << "depth is 0"; 
			if (!maxPlayer) {
				return (curMax-curMin);
			}
			else 
				return (curMin-curMax); 
		}
	}
	//cout << "pass"; 
	for (x = 0; x < 6; x++) {
		for (y = 0; y < 6; y++) {
		// all possible moves for max
			if (board[x][y] == empty) {

				cout << "x: " << x << "y: " << y << "\n"; 
				//cout << "empty if";
				// pick a square that is empty and conquer it
				if(maxPlayer) {
					//cout << "maxPlayer if";
					board[x][y] = blue; 	
					cout << "blue";		
					// check neighboring squares for possible death blitz move
					// check left/right
					if (x > 0) {
						if(board[x-1][y] == blue) {
							 if (x < 5) {
							 	if (board[x+1][y] == green) {
							 		board[x+1][y] = blue; 
							 		right = true; 
							 	}
							 }
							 if (y > 0) {
							 	if (board[x][y-1] == green) {
							 		board[x][y-1] = blue; 
							 		bottom = true; 
							 	}
							 }
							 if (y < 5) {
							 	if (board[x][y+1] == green){
							 		board[x][y+1] = blue; 
							 		top = true; 
							 	}
							 }
						}
					}
					else if (x < 5) {
						if(board[x+1][y] == blue) {
							 if (x > 0) {	
							 	if (board[x-1][y] == green) {
							 		board[x-1][y] = blue; 
							 		left = true; 
							 	}
							 }
							 if (y > 0) {
							 	if (board[x][y-1] == green) {
							 		board[x][y-1] = blue; 
							 		bottom = true; 
							 	}
							 }
							 if (y < 5) {
							 	if (board[x][y+1] == green){
							 		board[x][y+1] = blue; 
							 		top = true; 
							 	}
							 }
						}
					}		
			
					// do this recursively
					//cout << "depth before recursion" << depth; 
					result = minimax(score, board, false, score[x][y], depth, depth-1);		

					// undo move
					board[x][y] = empty; 
					if (left) board[x-1][y] = green; 
					if (right) board[x+1][y] = green; 
					if (top) board[x][y+1] = green; 
					if (bottom) board[x][y-1] = green; 

					// check if my value is greater than any of the bestValues found so far. 
					if (result > maxScore) {
						maxScore = result;  
						if (depth == maxDepth) {
							// place my move on the board. 
							//cout << "max move";
							maxOptimalX = x; 
							maxOptimalY = y; 
						}	
					}	
				}
				else {

					// pick a square that is empty and conquer it
					board[x][y] = green; 
					cout << "green";
					// check neighboring squares for possible death blitz move
					// check left/right
					if (x > 0) {
						if(board[x-1][y] == green) {
							 if (x < 5) {
							 	if (board[x+1][y] == blue) {
							 		board[x+1][y] = green; 
							 		right = true; 
							 	}
							 }
							 if (y > 0) {
							 	if (board[x][y-1] == blue) {
							 		board[x][y-1] = green; 
							 		bottom = true; 
							 	}
							 }
							 if (y < 5) {
							 	if (board[x][y+1] == blue){
							 		board[x][y+1] = green; 
							 		top = true; 
							 	}
							 }
						}
					}
					else if (x < 5) {
						if(board[x+1][y] == green) {
							 if (x > 0) {
							 	if (board[x-1][y] == blue) {
							 		board[x-1][y] = green; 
							 		left = true; 
							 	}
							 }
							 if (y > 0) {
							 	if (board[x][y-1] == blue) {
							 		board[x][y-1] = green; 
							 		bottom = true; 
							 	}
							 }
							 if (y < 5) {
							 	if (board[x][y+1] == blue){
							 		board[x][y+1] = green; 
							 		top = true; 
							 	}
							 }
						}
					}		
				
					// recursion!!!!!
					result = minimax(score, board, true, score[x][y], depth, depth-1);

					//undo moves
					board[x][y] = empty; 
					if (left) board[x-1][y] = blue; 
					if (right) board[x+1][y] = blue; 
					if (top) board[x][y+1] = blue; 
					if (bottom) board[x][y-1] = blue; 

					if (result < minScore) {
						minScore = result;  
						if (depth == maxDepth) {
							// place move on the board
							//cout << "min move";
							minOptimalX = x; 
							minOptimalY = y;  
							//cout<<minOptimalX<<minOptimalY; 
						}
					}
				}
			}
		}
	}
	if (maxPlayer) {
		//board[maxOptimalX][maxOptimalY] = blue; 
		//cout << maxScore; 
		return maxScore; 
	}
	else {
		//board[minOptimalX][minOptimalY] = green; 
		//cout << minScore; 
		return minScore; 
	}
}
