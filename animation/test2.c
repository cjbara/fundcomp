// a simple animation program
// ( demonstrates the need for gfx_event_waiting() )
#include <stdio.h>
#include "gfx.h"

int main()
{
  int wd=500;  // window width
  int ht=400;  // window height
  char c=1;
  int dx=1;   // basic increment for animation

  gfx_open(wd, ht, "My window");  // Open a new window for drawing.

  gfx_color(0,255,0);      // Set the current drawing color.

  while(c != 'q') { 
    gfx_clear();
    gfx_line(100+dx,100,150+dx,150);
    gfx_flush;
    dx++;
    usleep(2000);      // pause for 2 millisecons
    if(gfx_event_waiting()) { 
      c = gfx_wait();
    }
  }
}

