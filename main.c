#include <unistd.h>
#include <stdlib.h>
#include "snake.h"
#include <ncurses.h>
#include "wellcome.h"
#include <pthread.h>


int ch;
int GAMEOVER;
/*
void get_command(void *i)
{
  ch = getch();
}
*/
int main()
{
  initscr();
  start_color();
  keypad(stdscr,TRUE);
  curs_set(0);
  noecho();
  halfdelay(4);
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  init_pair(2,COLOR_BLACK,COLOR_WHITE);

  print_snake_logo(stdscr);
  mvprintw(LINES-1,COLS-20,"Producted by Jack");



  mvprintw(LINES-4,(COLS-21)/2,"|-> START");
  printw(" (? for help)");


  refresh();
  int choice;
  char goout = 0;
  while (!goout){

  switch (choice = getch() ){
  case 'q':
    endwin();
    return 0;
  case 'e':
    goout = 1;
    break;
  }

  }
  /*
  pthread_t id;
  pthread_create(&id,NULL,get_command,NULL);
  */
  
  Psnake jack = init_snake();
  init_show_snake(jack);
  ch = mvgetch(LINES-1,0);
  srand((unsigned)time(0));
  
  for (int i = 0; i<10; i++)
    putfood(jack);
  refresh();
  int noout = 1;
  int c = 0;
  while(noout){
	ch = getch();
  switch (ch){

  case KEY_RIGHT:
    c = snake_go_right(jack);
    if ( c == -1){
	noout = 0;
	GAMEOVER = 1;
	break;
    }
      continue;

  case KEY_DOWN :
       c = snake_go_down(jack);
      if ( c == -1){
	noout = 0;
	GAMEOVER = 1;
	break;
      }
      continue;

  case KEY_LEFT:
    c = snake_go_left(jack);
      if ( c == -1){
	noout = 0;
	GAMEOVER = 1;
	break;
      }
      continue;

  case KEY_UP:
    c = snake_go_up(jack);
      if ( c == -1){
	noout = 0;
	GAMEOVER = 1;
	break;
      }
      continue;
  case 'q':
    game_over(jack);
    endwin();
    return 0;
  }

  if (jack->righting){
    c = snake_go_right(jack);
    if (c == -1){
      GAMEOVER = 1;
      break;
    }
  }
  else if (jack->lefting){
    c = snake_go_left(jack);
    if (c == -1){
      GAMEOVER = 1;
      break;
    }

  }
  else if(jack->uping){
    c = snake_go_up(jack);
    if (c == -1){
      GAMEOVER = 1;
      break;
    }

  }
  else if(jack->downing){
    c = snake_go_down(jack);
    if (c == -1){
      GAMEOVER = 1;
      break;
    }

  }

  if (food_num < 30)
    putfood(jack);
  mvprintw(LINES-1,2,"-- socre %d --",jack->length);
  refresh();
  }

  if(GAMEOVER)
    game_over(jack);
    
  refresh();
  
  endwin();
  return 0;
}
