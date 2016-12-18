#ifndef SNAKE_H
#define SNAKE_H
#include <ncurses.h>
typedef enum state
  {
    goleft,
    goright,
    goup,
    godown
  }state;

typedef struct body
{
  int y;
  int x;
  struct body *prev;
  struct body *next;
}Body ,*Pbody;

typedef struct snake
{
  Pbody vir_head;
  Pbody head;
  Pbody tail;
  int length;
  state movement;

  char uping;
  char downing;
  char lefting;
  char righting;
}Snake, *Psnake;

int FOOD[1000][1000];
int food_num;

/*
** body part
*/
Pbody init_body();
void add_body(Pbody jack, Pbody bd);
Pbody bd(int lines,int cols);

void print_snake(Pbody jack);

void print_bd(Pbody bd);

Pbody get_head(Pbody jack);

Pbody add_head(Pbody oldhead,Pbody newhead);

Pbody del_tail(Pbody jack);

Pbody get_tail(Pbody jack);


/*
** snake part
*/

Psnake init_snake();

int snake_go_right(Psnake snake);

int snake_go_left(Psnake jack);

void show_snake(Psnake jack);

void init_show_snake(Psnake jack);

int snake_go_down(Psnake jack);

int snake_go_up(Psnake jack);

int snake_can_move(Psnake jack, char ch);

int body_in_snake(int row, int col, Psnake jack);

/* food part */

void putfood(Psnake jack);

int count_food();

/* game_over */

void game_over(Psnake jack);
#endif // SNAKE_H
