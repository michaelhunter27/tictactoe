#include <iostream>
#include <cstdlib>
#include <string>
#include "game.h"

using namespace std;



void Game::set_row(int x){
   rows = x;
}

void Game::set_col(int x){
   cols = x;
}

void Game::set_in_a_row(int x){
   in_a_row = x;
}

void Game::settings(){
   int x;
   cout << "Number of rows (2-5): ";
   set_row(get_int(2, 5));
   cout << "Number of columns (2-5): ";
   set_col(get_int(2, 5));
   cout << "Number in a row to win: ";
   if(rows > cols)
      x = cols;
   else
      x = rows;
   set_in_a_row(get_int(1, x));
   area = rows * cols;
   player_char[0] = 'O';
   player_char[1] = 'X';
}


void Game::make_board(){
   board = new char*[rows];
   for(int i = 0; i < rows; i++)
      board[i] = new char[cols];
}




void Game::initialize_board(){
   for(int i = 0; i < rows; i++)
      for(int j = 0; j < cols; j++)
	 board[i][j] = '*';
}




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


void Game::delete_board(){
   for(int i = 0; i < rows; i++)
      delete [] board[i];
   delete [] board;
}



int Game::get_int(int min, int max){
   string input;
   int num = 0, i = 0;
   do{   
      getline(cin, input);
      for(i = 0; i < input.length(); i++){
	 if(input.at(i) < '0' || input.at(i) > '9')
	    break;
      }
      if(i == input.length())
	 num = atoi(input.c_str());
   } while(i != input.length() || !(num >= min && num <= max));
   
   return num;
}



void Game::get_move(){
   cout << "input row: ";
   move[0] = get_int(1, rows) - 1;
   cout << "input column: ";
   move[1] = get_int(1, cols) - 1;
}



int Game::check_move(){
   if(board[move[0]][move[1]] == '*')
      return 1;
   else
      return 0;
}


void Game::update_board(int turn){
   board[move[0]][move[1]] = player_char[turn%2];
}




//Description: Checks if there is a win vertically
//Preconditions: 
//Postconditions: none
//Output: 1 if there is a win, 0 otherwise
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

int Game::get_area(){
   return area;
}
