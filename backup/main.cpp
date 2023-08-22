/****************************
 *
 *
 *
 *
 *
 * *************************/

#include<iostream>
#include"game.h"


using namespace std;

int main(){
   Game game1;
   int turn = 1;

   
   game1.settings();

   cout << "settings done" << endl;

   game1.make_board();
   cout << "make board done" << endl;
   game1.initialize_board();
   cout << "initialize board done" <<  endl;
   game1.print_board();

   while(game1.check_win() == 0 && turn <= game1.get_area()){
      if(turn % 2 == 1)
	 cout << "Player 1:" << endl;
      else
	 cout << "Player 2:" << endl;

      do {
	 game1.get_move();
      } while(game1.check_move() == 0);
   
      game1.update_board(turn);
      game1.print_board();
   
      turn++;
   }
   game1.delete_board();




   return 0;
}
