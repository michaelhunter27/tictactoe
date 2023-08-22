/************************************************
 * Program: Tic-tac-toe (main.cpp)
 * Name: Michael Hunter
 * Date: Jan. 15, 2016
 * Description: A game of tic-tac-toe including,
 *    1-player and 2-player modes, variable game
 *    size, and multiple plays in one run.
 * Note: requires game.h and game.cpp files
 * **********************************************/

#include <iostream>
#include "game.h"


using namespace std;

int game_mode();


int main(){
   Game game1;
   int turn;
   int mode;
   bool cont = true;


   /* Multi-game Loop */
   while(cont == true){


      /* Set up */
      turn = 1;
      mode = game1.game_mode();
      game1.settings();
      game1.make_board();
      game1.initialize_board();
      

      game1.print_board();


      /* Game Loop */
      while(game1.check_win() == 0 && turn <= game1.get_area()){
	 

	 /* Human move */
	 if(mode == 2 || (turn % 2 != mode)){
	    if(turn % 2 == 1)
	       cout << "Player 1:" << endl;
	    else
	       cout << "Player 2:" << endl;

	    game1.get_move();
	 }


	 /* AI move */
	 if(turn % 2 == mode ){
	    game1.ai_move();
	 }


	 /* Game updates */
	 game1.update_board(turn);
	 game1.print_board();
	 turn++;
      
      }
      /* End of game */


      /* Game result */
      game1.print_winner(turn-1, mode);

 
      /* Clean up */
      game1.delete_board();
      

      /* play again  prompt */
      cont = game1.play_again();
   }
   /* End of multi-game loop */


   return 0;
}
