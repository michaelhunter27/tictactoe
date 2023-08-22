#ifndef GAME_H
#define GAME_H

class Game
{ 
   private:
      char **board;
      int rows;
      int cols;
      int in_a_row;
      int move[2];
      char player_char[2];
      
      void set_rows(int);
      void set_cols(int);
      void set_in_a_row(int);
   
   public:
      //GAME SETTINGS
      void settings();
      int game_mode();

      //BOARD FUNCTIONS
      void make_board();
      void initialize_board();
      void print_board();
      void delete_board();

      //TURN FUNCTIONS
      int get_int(int min, int max);
      void get_move();
      int check_move();
      void update_board(int turn);
      void ai_move();

      //WIN CHECKING
      bool check_win_vert();
      bool check_win_horiz();
      bool check_win_diag1();
      bool check_win_diag2();
      bool check_win();

      //POST GAME FUNCTIONS
      void print_winner(int turn, int mode);
      bool play_again();

      //OTHER
      int get_area();
};

#endif
