#ifndef GAME_H
#define GAME_H

class Game
{
   
   private:
      //MOVE VARIABLES HERE
   public:
      char **board;
      int rows;
      int cols;
      int in_a_row;
      int area;

      int move[2];

      char player_char[2];

      void set_row(int);
      void set_col(int);
      void set_in_a_row(int);
      void settings();
      
      void make_board();
      void initialize_board();
      void print_board();
      void delete_board();

      int get_int(int, int);
      void get_move();
      int check_move();
      void update_board(int);

      bool check_win_vert();
      bool check_win_horiz();
      bool check_win_diag1();
      bool check_win_diag2();
      bool check_win();

      int get_area();

};

#endif
