#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "game.h"

using namespace std;


//PRIVATE FUNCTIONS


//Sets the value of rows
//Private function
void Game::set_rows(int x){
   rows = x;
}


//Sets the value of cols
//Private function
void Game::set_cols(int x){
   cols = x;
}


//Sets the value of in_a_row
//Private function
void Game::set_in_a_row(int x){
   in_a_row = x;
}


//GAME SETTINGS


//Gets dimensions of board and number in
//   a row to win from user
void Game::settings(){
   int x;
   cout << "Number of rows (2-5): ";
   set_rows(get_int(2, 5));
   cout << "Number of columns (2-5): ";
   set_cols(get_int(2, 5));
   cout << "Number in a row to win: ";
   if(rows > cols)
      x = rows;
   else
      x = cols;
   set_in_a_row(get_int(2, x));
   player_char[0] = 'O';
   player_char[1] = 'X';
}


//Gets game mode from user
//Returns 2 for a 2-player game
//Returns 1 if computer is X's
//Retruns 0 if computer is O's
int Game::game_mode(){
   string input;
   cout << "Play against the computer (1) or 2-player game (2)? ";
   do{
      getline(cin, input);
   }while(input != "1" && input != "2");

   if(input == "2")
      return 2;

   cout << "Do you want X or O? ";
   do {
      getline(cin, input);
   }while(input != "x" && input != "o" && input != "X" && input != "O");
   if(input == "X" || input == "x" )
      return 0;
   else
      return 1;
}


//BOARD FUNCTIONS


//Allocates memory for the dynamic array
//rows and cols should be set prior to function call
void Game::make_board(){
   board = new char*[rows];
   for(int i = 0; i < rows; i++)
      board[i] = new char[cols];
}



//Initializezs the board to all *'s
//Dyanmaic array should be made prior to call
void Game::initialize_board(){
   for(int i = 0; i < rows; i++)
      for(int j = 0; j < cols; j++)
	 board[i][j] = '*';
}


//Prints the game board to the screen
void Game::print_board(){
   system("clear");
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
	 cout << board[i][j];
	 if(j < cols - 1)
	    cout << "|";
      }
      cout << endl;
      if(i < rows - 1){
	 for(int j = 0; j < cols - 1; j++)
	    cout << "-+";
	 cout << "-" << endl;
      }
   }
}


//Frees dynamic memory of the game board
void Game::delete_board(){
   for(int i = 0; i < rows; i++)
      delete [] board[i];
   delete [] board;
}


//TURN FUNCTIONS


//Gets an int between min and max inclusive
//Returns the integer
int Game::get_int(int min, int max){
   string input;
   int num = 0, i = 0;
   do{   
      getline(cin, input);
      for(i = 0; i < input.length(); i++){
	 if(input.at(i) < '0' || input.at(i) > '9'){
	    break;
	    cout << "invalid input, try again." << endl;
	 }
      }
      if(i == input.length()){
	 num = atoi(input.c_str());
         if(num < min || num > max)
	    cout << "integer out of range, try again." << endl;
      }
   } while(i != input.length() || !(num >= min && num <= max));
   
   return num;
}


//Gets a valid move from the user
//Checks that the move is in bounds and not full
void Game::get_move(){
   do {
   cout << "input row: ";
   move[0] = get_int(1, rows) - 1;
   cout << "input column: ";
   move[1] = get_int(1, cols) - 1;
   if(check_move() == 0)
      cout << "space is full, try again." << endl;
   }while(check_move() == 0);
}


//Checks if the space at move is full
//Returns 1 if empty, 0 if full
int Game::check_move(){
   if(board[move[0]][move[1]] == '*')
      return 1;
   else
      return 0;
}


//Updates the board with an X or O at move
//places an X if turn is odd, places an O if turn is even
void Game::update_board(int turn){
   board[move[0]][move[1]] = player_char[turn%2];
}


//Chooses a move for the computer and stores it in move
//Move is chosen randomly and checked to make sure
//   it is not full
void Game::ai_move(){
   srand(time(NULL));
   do{
      move[0] = rand() % rows;
      move[1] = rand() % cols;
   }while(check_move() == 0);
}


//WIN CHECKING


//Checks if there is a win vertically
//Returns 1 if there is a win, 0 otherwise
bool Game::check_win_vert(){
   int x;
   for( int i = 0; i <= rows-in_a_row; i++){
      for( int j = 0; j < cols; j++){
	 if(board[i][j] != '*'){
	    for (x = 1 ; x < in_a_row; x++)
	       if (board[i][j] != board[i+x][j])
		  break;
	    if (x == in_a_row)
	       return 1;
	 }
      }
   }
   return 0;
}


//Checks if there is a win horizontally
//Returns 1 if there is a win, 0 otherwise
bool Game::check_win_horiz(){
   int x;
   for( int i = 0; i < rows; i++){
      for( int j = 0; j <= cols - in_a_row; j++){
	 if(board[i][j] != '*'){
	    for (x = 1 ; x < in_a_row; x++)
	       if (board[i][j] != board[i][j+x])
		  break;
	    if (x == in_a_row)
	       return 1;
	 }
      }
   }
   return 0;
}


//Checks if there is a win diagonally \
//Returns 1 if there is a win, 0 otherwise
bool Game::check_win_diag1(){
   int x;
   for( int i = 0; i <= rows - in_a_row; i++){
      for( int j = 0; j <= cols - in_a_row; j++){
	 if(board[i][j] != '*'){
	    for (x = 1 ; x < in_a_row; x++)
	       if (board[i][j] != board[i+x][j+x])
		  break;
	    if (x == in_a_row)
	       return 1;
	 }
      }
   }
   return 0;
}


//Checks if there is a win diagonally /
//Returns 1 if there is a win, 0 otherwise
bool Game::check_win_diag2(){
   int x;
   for( int i = rows - 1; i >= in_a_row - 1; i--){
      for( int j = 0; j <= cols - in_a_row; j++){
	 if(board[i][j] != '*'){
	    for (x = 1 ; x < in_a_row; x++)
	       if (board[i][j] != board[i-x][j+x])
		  break;
	    if (x == in_a_row)
	       return 1;
	 }
      }
   }
   return 0;
}


//Checks if there is any win
//Returns 1 if there is a win, 0 otherwise
bool Game::check_win(){
   if(check_win_vert())
      return 1;
   if(check_win_horiz())
      return 1;
   if(check_win_diag1())
      return 1;
   if(check_win_diag2())
      return 1;
   return 0;
}


//POST GAME FUNCTIONS


//Prints the result of the game
//Turn should be the last turn played
void Game::print_winner(int turn, int mode){
   int temp;
   temp = check_win();
   if(temp == 0)
      cout << "It's a tie!" << endl;
   else if(turn % 2 == mode)
      cout << "I win!! " << endl << "gg, mate" << endl;
   else if(turn % 2 == 0)
      cout << "Player 2 wins!" << endl;
   else
      cout << "Player 1 wins!" << endl;
}


//Determines if the user wants to play again
//Returns 1 if the user wants to play again
//Returns 0 if the user wants to quit
bool Game::play_again(){
   string input;   
   cout << endl << "Play again? (yes-1 no-0): ";
      do{
	 getline(cin, input);
	 if(input != "0" && input != "1")
	    cout << "enter 1 or 0, try again." << endl;
      }while(input != "0" && input != "1");
      return atoi(input.c_str());
}


//OTHER


//Returns the area of the board rows*cols
int Game::get_area(){
   return rows*cols;
}
