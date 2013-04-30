#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<iostream.h>
#include<graphics.h>

int name=0;
static int ax = 40,ay = 130;
static char *butt_name[] = {{" 1"},{" 4"},{" 7"},{" 2"},{" 5"},
			   {" 8"},{" 3"},{" 6"},{" 9"},{" E"}};

class button
{
   protected:
       int r, l, t, b, b_name;           // Member Variables

   public:
       button(int w,int x,int y,int z)
	{ l=w;t=x;r=y;b=z; }

       void draw()
	{
	    setcolor(WHITE);
	    settextstyle(0,0,2);
	    rectangle(l,t,r,b-2);
	    setfillstyle(1,RED);
	    floodfill(l+5,t+5,15);
	    button_effect();
	    setcolor(BLACK);
	    b_name = name;
	    outtextxy(l-7,t+6,butt_name[name]);
	    name++;
	    setcolor(WHITE);
	}

       void button_effect()
	{                          // For Button Release Effect
	   setcolor(BLUE);
	   line(l,b-2,r,b-2);line(r,t,r,b-2);
	   setcolor(WHITE);
	   line(l,t,l,b-2);line(l,t,r,t);
	}

       void button_effect1()
	{                         // For Button Press Effect
	   setcolor(WHITE);
	   line(l,b-2,r,b-2);line(r,t,r,b-2);
	   setcolor(BLUE);
	   line(l,t,l,b-2);line(l,t,r,t);
	   delay(150);
	   button_effect();
	}

       void button :: higlt(int prev);
       void button :: highlight(int prev);
};
//---------------------------------------------------------------
void button :: higlt(int prev)
  {
      int yp = ay;
      switch(prev)
      {
	case  1: prev = 0; yp = 130; break;
	case  2: prev = 3; yp = 160; break;
	case  3: prev = 6; yp = 190; break;
	case  4: prev = 1; yp = 220; break;
	case  5: prev = 4; yp = 250; break;
	case  6: prev = 7; yp = 280; break;
	case  7: prev = 2; yp = 310; break;
	case  8: prev = 5; yp = 340; break;
	case  9: prev = 8; yp = 370; break;
	case 10: prev = 9; yp = 400; break;
      }

      settextstyle(0,0,2);
      setcolor(WHITE);
      outtextxy(ax-7,yp+6,butt_name[prev]);
      settextstyle(11,0,1);
 }
//---------------------------------------------------------------
void button :: highlight(int prev)
  {
      int yp;
      switch(prev)
      {
	case  1: prev = 0; yp = 130; break;
	case  2: prev = 3; yp = 160; break;
	case  3: prev = 6; yp = 190; break;
	case  4: prev = 1; yp = 220; break;
	case  5: prev = 4; yp = 250; break;
	case  6: prev = 7; yp = 280; break;
	case  7: prev = 2; yp = 310; break;
	case  8: prev = 5; yp = 340; break;
	case  9: prev = 8; yp = 370; break;
	case 10: prev = 9; yp = 400; break;
      }

      settextstyle(0,0,2);
      setcolor(BLACK);
      outtextxy(ax-7,yp+6,butt_name[prev]);
      setcolor(WHITE);
      outtextxy(l-7,t+6,butt_name[b_name]);
      settextstyle(11,0,1);
 }
//---------------------------------------------------------------
 button _1( 40, 130, 70, 160);    // creation of the buttons
 button _2( 40, 160, 70, 190);    // of the num-pad
 button _3( 40, 190, 70, 220);
 button _4( 40, 220, 70, 250);
 button _5( 40, 250, 70, 280);
 button _6( 40, 280, 70, 310);
 button _7( 40, 310, 70, 340);
 button _8( 40, 340, 70, 370);
 button _9( 40, 370, 70, 400);
 button _ER(40, 400, 70, 430);
//---------------------------------------------------------------
