#include "game.h"
//Benoit Ortalo-Magne
/*

This program takes as input the number of rows and columns and outputs a game of 2048 in that dimension the user can play
Funtions move_w, move_s, move_a, move_d perform moves and additions
make_game, remake_game, destroy_game build and modify the board
get_cell finds a pointer to the cell value

*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
	
    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	//Initialize cells[], score, rows, and cols
	for (int i = 0; i < (rows*cols); i++) {		//Create game board and initialize to blank
	mygame -> cells[i] = -1;
	}
	mygame -> score = 0;		//Initialize values
	mygame -> rows = rows;
	mygame -> cols = cols;
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
	
	//Initialize current game's rows, cols, cells, and score
	(*_cur_game_ptr) -> rows = new_rows;			//Set rows, reset board, reset score
	(*_cur_game_ptr) -> cols = new_cols;
	for (int i = 0; i < (new_rows*new_cols); i++) {
	(*_cur_game_ptr) -> cells[i] = -1;
	}
	(*_cur_game_ptr) -> score = 0;

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{					//Find pointer to value at given column and row
	if (((row >= 0) && (row < (cur_game -> rows))) || ((col < (cur_game -> cols)) && (col >= 0))) {
	int* point = &(cur_game -> cells[0]) + (row*(cur_game -> cols) + col);
	return  point;
	}
	else

    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
int n, m, i, t = -1, val, init, swap, emptycell = -1;	//Initialize
for (m = 0; m < (cur_game -> cols); m++) {	//column loop
  int last_combined_row = -1;			//check if already combined with this row
  for (n = 0; n < (cur_game -> rows); n++) {	//row loop
    init = *get_cell(cur_game, n, m);		//Find value at position n, m
    if (init != -1) {				//If its a number
      for (i = 0; i <= n; i++) {		//Check each row starting from row 0 to find a -1
	t = i;
	val = *get_cell(cur_game, i, m);	//Find value at each row
	if (val == -1) {			//if value is -1
	  *get_cell(cur_game, i, m) = *get_cell(cur_game, n, m);	//Swap value and -1
	  *get_cell(cur_game, n, m) = -1;
	}
	swap = *get_cell(cur_game, (t - 1), m);				//Find value at previous row
	if ((t - 1) != last_combined_row) {				//If value at previous row is a value and is same as current value
	  if ((swap == (*get_cell(cur_game, t, m))) && (swap != -1)) {
	    *get_cell(cur_game, (t - 1), m) = 2 * (swap);		//Double value at previous row
	    cur_game->score = cur_game->score + (2 * swap);		//Update score
	    *get_cell(cur_game, t, m) = emptycell;			//Place -1 in place of current value
	    last_combined_row = (t - 1);				//Set LCR
	  }
	}
      }
    }
  }
}


if (t == -1)
    return 0;		//If nothing happens, return 0
else
    return 1;		//If nothing happens, return 1
};

int move_s(game * cur_game) //slide down
{

int n, m, i, t = -1, val, init, swap, emptycell = -1;	//Initialize
for (m = 0; m < (cur_game -> cols); m++) {		//Column loop
  int last_combined_row = -1;				//Initialze
  for (n = (cur_game -> rows) - 1; n >= 0; n--) {	//Row loop
    init = *get_cell(cur_game, n, m);			//Value at given row and column
    if (init != -1) {					//If is value
      for (i = (cur_game -> rows) - 1; i >= n; i--) {	//Look for -1 or same value
	t = i;
	val = *get_cell(cur_game, i, m);
	if (val == -1) {				//If find -1, move to there
	  *get_cell(cur_game, i, m) = *get_cell(cur_game, n, m);	//Swap -1 and value
	  *get_cell(cur_game, n, m) = -1;
	}
	swap = *get_cell(cur_game, (t + 1), m);		//Value one further than current
	if ((t + 1) != last_combined_row) {		//If havent just combined this row
	  if ((swap == (*get_cell(cur_game, t, m))) && (swap != -1)) {	//if values the same
	    *get_cell(cur_game, (t + 1), m) = 2 * (swap);
							//Add and move to further values place. -1 in original values place
	    *get_cell(cur_game, t, m) = emptycell;
	    last_combined_row = (t + 1);
	    cur_game->score = cur_game->score + (2 * swap);
	  }
	}
      }
    }
  }
}


if (t == -1)		//If nothing happens, return 0, otherwise return 1
    return 0;
else
    return 1;
};

int move_a(game * cur_game) //slide left
{

int n, m, i, t, val, init, swap, emptycell = -1, endr = -1;		//Initialize
for (m = 0; m < (cur_game -> rows); m++) {		//Row and Column loops
  int last_combined_row = -1;
  for (n = 0; n < (cur_game -> cols); n++) {
    init = *get_cell(cur_game, m, n);			//Value at given row and column
    if (init != -1) {
      for (i = 0; i <= n; i++) {			//Look at previous values
	t = i;
	val = *get_cell(cur_game, m, i);
	if (val == -1) {				//If previous value -1, switch positions with it
	  *get_cell(cur_game, m, i) = *get_cell(cur_game, m, n);
	  *get_cell(cur_game, m, n) = -1;
	endr = 2;
	}
	swap = *get_cell(cur_game, m, (t - 1));
	if ((t - 1) != last_combined_row) {		//If havent already combined with this column, add and replace current value with -1
	  if ((swap == (*get_cell(cur_game, m, t))) && (swap != -1)) {
	    *get_cell(cur_game, m, (t - 1)) = 2 * (swap);
	    cur_game->score = cur_game->score + (2 * swap);
	    *get_cell(cur_game, m, t) = emptycell;
	    last_combined_row = (t - 1);
		endr = 2;
	  }
	}
      }
    }
  }
}
if (endr == -1)		//If nothing happens, return 0, else, return 1
    return 0;
else
    return 1;
};
int move_d(game * cur_game){ //slide to the right

int n, m, i, t, val, init, swap, emptycell = -1, endr = -1;		//Initialize
for (m = 0; m < (cur_game -> rows); m++) {			//Row and Column loops
  int last_combined_row = -1;
  for (n = (cur_game -> cols) - 1; n >= 0; n--) {
    init = *get_cell(cur_game, m, n);
    if (init != -1) {						//Find value
      for (i = (cur_game -> cols) - 1; i >= n; i--) {		//look at previous values
	t = i;
	val = *get_cell(cur_game, m, i);			
	if (val == -1) {					//If previous value is -1, swap with found value
	  *get_cell(cur_game, m, i) = *get_cell(cur_game, m, n);
	  *get_cell(cur_game, m, n) = -1;
		endr = 2;
	}
	swap = *get_cell(cur_game, m, (t + 1));
	if ((t + 1) != last_combined_row) {			//if previous value is same as found value, add them and replace found value with -1
	  if ((swap == (*get_cell(cur_game, m, t))) && (swap != -1)) {
	    *get_cell(cur_game, m, (t + 1)) = 2 * (swap);
	    cur_game->score = cur_game->score + (2 * swap);
	    *get_cell(cur_game, m, t) = emptycell;
	    last_combined_row = (t + 2);
		endr = 2;
	  }
	}
      }
    }
  }
}
if (endr == -1)	//If nothing happened, return 0, else return 1
    return 0;
else

    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
int m, n;
for (m = (cur_game -> rows) - 1; m >= 0; m--) {		//For rows and columns
  for (n = 0; n < (cur_game -> cols); n++) {	
    if (*get_cell(cur_game, m, n) == -1)		//if there is a -1 value on the board, return 1
	return 1;
    if ((*get_cell(cur_game, m, n) == *get_cell(cur_game, m + 1, n) && (m < (cur_game -> cols))) || ((*get_cell(cur_game, m, n) == *get_cell(cur_game, m - 1, n)) && (m > 0)) || ((*get_cell(cur_game, m, n) == *get_cell(cur_game, m, n + 1)) && (n < (cur_game -> rows))) || ((*get_cell(cur_game, m, n) == *get_cell(cur_game, m, n - 1)) && (n > 0)))
        return 1;	//If there are two adjacent numbers, return 1
    }
  }
  return 0;		//Else return 0
}
/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
