#include <ncurses.h>


void print_char_s(WINDOW *win, int y, int x)
{
  mvwprintw(win,y+0,x," #####  ");
  mvwprintw(win,y+1,x,"#     # ");
  mvwprintw(win,y+2,x,"#       ");
  mvwprintw(win,y+3,x," #####  ");
  mvwprintw(win,y+4,x,"      # ");
  mvwprintw(win,y+5,x,"#     # ");
  mvwprintw(win,y+6,x," #####  ");   
}

void print_char_n(WINDOW *win, int y, int x)
{
  mvwprintw(win,y+0,x,"#     # ");
  mvwprintw(win,y+1,x,"##    # ");
  mvwprintw(win,y+2,x,"# #   # ");
  mvwprintw(win,y+3,x,"#  #  # ");
  mvwprintw(win,y+4,x,"#   # # ");
  mvwprintw(win,y+5,x,"#    ## ");
  mvwprintw(win,y+6,x,"#     # ");   
}

void print_char_a(WINDOW *win, int y, int x)
{
  mvwprintw(win,y+0,x,"   #    ");
  mvwprintw(win,y+1,x,"  # #   ");
  mvwprintw(win,y+2,x," #   #  ");
  mvwprintw(win,y+3,x,"#     # ");
  mvwprintw(win,y+4,x,"####### ");
  mvwprintw(win,y+5,x,"#     # ");
  mvwprintw(win,y+6,x,"#     # ");
}

void print_char_k(WINDOW *win, int y, int x)
{
  mvwprintw(win,y+0,x,"#   ### ");
  mvwprintw(win,y+1,x,"#  #    ");
  mvwprintw(win,y+2,x,"# #     ");
  mvwprintw(win,y+3,x,"##      ");
  mvwprintw(win,y+4,x,"# #     ");
  mvwprintw(win,y+5,x,"#  ##   ");
  mvwprintw(win,y+6,x,"#    ## ");
}

void print_char_e(WINDOW *win, int y, int x)
{
  mvwprintw(win,y+0,x,"####### ");
  mvwprintw(win,y+1,x,"#       ");
  mvwprintw(win,y+2,x,"#       ");
  mvwprintw(win,y+3,x,"####### ");
  mvwprintw(win,y+4,x,"#       ");
  mvwprintw(win,y+5,x,"#       ");
  mvwprintw(win,y+6,x,"####### ");   
}

void print_snake_logo(WINDOW *win)
{
  int y,x;
  getmaxyx(win,y,x);
  y = (y-7)/2;
  x = (x-48)/2;

  print_char_s(stdscr, y, x += 0);
  print_char_n(stdscr, y, x += 9);
  print_char_a(stdscr, y, x += 9);
  print_char_k(stdscr, y, x += 9);
  print_char_e(stdscr, y, x += 9);

}

