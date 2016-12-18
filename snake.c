#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "snake.h"

extern int food_num;
/* init the virtual head of a snake */
Pbody init_body()
{
  Pbody jack = (Pbody) malloc (sizeof(Body));
  jack->y = 5;    // its value is meaningless
  jack->x = 5;    // the same
  jack->next = NULL;
  jack->prev = NULL;
  return jack;
}

/* add a body at the snake's tail */
/* the first node is the snake's real tail
   the last node is the snake's real head */
void add_body(Pbody jack, Pbody bd)
{
  if (jack->next == NULL)
    {
      bd->next = NULL;

    }
  else{
    bd->next = jack->next;
    bd->next->prev = bd;

  }
  bd->prev = jack;
  jack->next = bd;
}

/* constructor of the Body structure */
Pbody bd(int lines, int cols)
{
  Pbody temp = (Pbody)malloc(sizeof(Body));
  temp->y = lines;
  temp->x = cols;
  temp->next = NULL;
  temp->prev = NULL;

  return temp;
}

int body_in_snake(int row, int col, Psnake jack)
{
  int flag = 0;
  Pbody p = jack->tail;
  while (p != NULL)
    if(p->y == row && p->x == col){
      flag = 1;
      break;
    }
    else
      p = p->next;
  
  return flag;
}


/* show the snake */
void print_snake(Pbody jack)
{
  Pbody p = jack;
  int i = 0;
  while (p != NULL)
    {
      printf("No.%i  ",i++);
      printf("rows: %d  ",p->y);
      printf("cols: %d  ",p->x);
      printf("prev: %p  ",p->prev);
      printf("curt: %p  ",p);
      printf("next: %p  ",p->next);

      printf("\n");
      p = p->next;
    }
}

/* get the head */
Pbody get_head(Pbody jack)
{
  while(jack->next != NULL)
    jack = jack->next;
  return jack;
}

/* print a body */
void print_bd(Pbody bd)
{
  Pbody p = bd;
  printf("\n");
  printf("rows: %d  ",p->y);
  printf("cols: %d  ",p->x);
  printf("prev: %p  ",p->prev);
  printf("curt: %p  ",p);
  printf("next: %p  ",p->next);
  printf("\n");
}

/* this func returns new head */
Pbody add_head(Pbody oldhead,Pbody newhead)
{
  newhead->next = NULL;
  newhead->prev = oldhead;
  oldhead->next = newhead;
  return newhead;
}

/* this func returns new tail */
Pbody del_tail(Pbody jack)
{
  Pbody temp = jack->next;
  temp->next->prev = jack;
  jack->next = temp->next;
  free(temp);

  return jack->next;
}

Pbody get_tail(Pbody jack)
{
  return jack->next;
}

int snake_go_right(Psnake jack)
{
  if (jack->head->x < COLS-1 && snake_can_move(jack,'r') ){
  /*judge if she can go right */
  int nodel = 0;

  if (FOOD[jack->head->y][jack->head->x] == 1){
    nodel =1;
    food_num--;
    FOOD[jack->head->y][jack->head->x] = 0;
    jack->length++;
  }
  /* get the right pos */

  jack->lefting = 0;
  jack->righting = 1;
  jack->uping = 0;
  jack->downing = 0;

  Pbody pos = bd(jack->head->y, jack->head->x + 1) ;

  if (body_in_snake(pos->y,pos->x,jack)){
    return -1;
  }

  mvaddch(pos->y,pos->x,'#');

  jack->head = add_head(jack->head, pos);



  if(!nodel){
  mvaddch(jack->tail->y,jack->tail->x,' ');
  jack->tail = del_tail(jack->vir_head);
  }
  refresh();
  }
  if(jack->head->x == COLS-1)
      return -1;
  else
    return 0;
}

int snake_go_down(Psnake jack)
{
  if (jack->head->y + 2 < LINES && snake_can_move(jack, 'd') ){
  int nodel = 0;
  if (FOOD[jack->head->y][jack->head->x] == 1){
    nodel = 1;
    food_num--;
    FOOD[jack->head->y][jack->head->x] = 0;
  }
  
  /* 1 means the snake is doing that thing. */
  jack->lefting = 0;
  jack->righting = 0;
  jack->uping = 0;
  jack->downing = 1;

  /* pos is a body which is the next postion of the snake's head */
  Pbody pos = bd(jack->head->y+1, jack->head->x);

  /* it means the snake kills itself */
  if (body_in_snake(pos->y, pos->x,jack))
    return -1;


  mvaddch(pos->y,pos->x,'#');
  jack->head = add_head(jack->head, pos);

  if (!nodel){
    mvaddch(jack->tail->y,jack->tail->x,' ');
    jack->tail = del_tail(jack->vir_head);
  }

  refresh();
  }
  if (jack->head->y +2 == LINES)
    return -1;
  else
    return 0;
}

/* snake's movement to left */
int snake_go_left(Psnake jack)
{
  if (jack->head->x  > 0 && snake_can_move(jack,'l') ){
  /* judge if she can go left */
  /* get the right pos */
  int nodel = 0;
  if (FOOD[jack->head->y][jack->head->x] == 1){

    nodel = 1;
    food_num = food_num -1;
    FOOD[jack->head->y][jack->head->x] = 0;
    jack->length++;
  }

  jack->lefting = 1;
  jack->righting = 0;
  jack->uping = 0;
  jack->downing = 0;

  Pbody pos = bd(jack->head->y, jack->head->x-1) ;
  if (body_in_snake(pos->y,pos->x,jack))
    return -1;



  mvaddch(pos->y,pos->x,'#');
  
  /* there should be some code */

  jack->head = add_head(jack->head, pos);
  /* there should be some code */
  if(!nodel){
  mvaddch(jack->tail->y,jack->tail->x,' ');
  jack->tail = del_tail(jack->vir_head);
  }
  refresh();
  }
  if (jack->head->x == 0)
      return -1;
  else 
    return 0;
}

int snake_go_up(Psnake jack)
{
  if (jack->head->y  >0 && snake_can_move(jack,'u') ){
  int nodel = 0;
  if( FOOD[jack->head->y][jack->head->x] == 1){
    nodel = 1;
    food_num = food_num - 1;
    FOOD[jack->head->y][jack->head->x] = 0;
    jack->length++;
  }
  
  jack->lefting = 0;
  jack->righting = 0;
  jack->uping = 1;
  jack->downing = 0;

  Pbody pos = bd(jack->head->y -1, jack->head->x);
  if (body_in_snake(pos->y,pos->x,jack))
    return -1;


  mvaddch(pos->y,pos->x,'#');
  jack->head = add_head(jack->head, pos);
  if (!nodel){
    mvaddch(jack->tail->y,jack->tail->x,' ');
    jack->tail = del_tail(jack->vir_head);
  } 
  refresh();
  }
    if (jack->head->y == 0)
      return -1;
    else
      return 0;
}

/* init a snake whose length is 3 */
Psnake init_snake()
{
  Psnake jack = (Psnake)malloc(sizeof(Snake));
  Pbody b1, b2, b3;
  b1 = bd(3,3);
  b2 = bd(3,4);
  b3 = bd(3,5);

  jack->vir_head = init_body();
  add_body(jack->vir_head,b3);
  add_body(jack->vir_head, b2);
  add_body(jack->vir_head, b1);   // so now 3,5(b3)is the head

  jack->head = b3;
  jack->tail = b1;
  jack->length = 3;

  jack->lefting = 0;
  jack->righting = 1;
  jack->uping = 0;
  jack->downing = 0;

  return jack;
}

void show_snake(Psnake jack)
{
  Pbody p = jack->head;
  int i=0;
  //  printf("\nthe snake\n");
  while(p != jack->vir_head)
    {

      //  printf("No.%d y:%d x:s%d\n",++i,p->y,p->x);
      p = p->prev;
    }
}

void init_show_snake(Psnake jack)
{
  clear();
  Pbody p = jack->head;

  while (p != jack->vir_head){
    mvaddch(p->y,p->x,'#');
    p = p->prev;
  };

}

void putfood(Psnake jack)
{
  int x,y;
  while(1){

     y = rand()%LINES;
     x = rand()%COLS;
    if (!body_in_snake(y,x,jack)){
      break;
    }
  }
  FOOD[y][x] = 1;
  food_num++;
  mvaddch(y,x,'*');
  refresh();
}

int count_food()
{
  int count = 0;
  int j,k;
  for(j = 0; j <LINES; j++)
    for(k = 0; k<COLS; k++)
      if (FOOD[j][k] == 1)
	count++;

  return count;
}

int snake_can_move(Psnake jack, char ch)
{
  switch (ch){
  case 'u':
    return !jack->downing;
  case 'd':
    return !jack->uping;
  case 'l':
    return !jack->righting;
  case 'r':
    return !jack->lefting;
  }
}

void game_over(Psnake jack){

  WINDOW *result = subwin(stdscr,7,40,(LINES-7)/2,(COLS-40)/2);
  wbkgd(result,COLOR_PAIR(2));

  wclear(result);
  move(LINES-1,0);
  hline(' ',20);
  mvwprintw(result,2,15,"GAME OVER");
  mvwprintw(result,4,15," score:%d",jack->length);
  wrefresh(result);

  int ch = 0;
  
  while (ch = getch() != ' ');
  delwin(result);
}
  
