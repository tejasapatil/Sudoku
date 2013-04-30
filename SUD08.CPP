#include<dos.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream.h>
#include<graphics.h>
//#define path "c:\\tcc"

int LOAD = 1;
union REGS i,o;
char File_name[20];

int
 nam_siz,      // file name size
 curr=10,      // for the buttons of the Num-pad
 men_stat = 0, // for checking status of menu
 code = -1,
 puz_typ = 0,  // for puzzle type
 cnt = 0,      // counts the total filled positions
 arr[9][9],    // user input    =0,vacant  else filled
 puzz[9][9],   // puzzle     complete solution
 stat[9][9],   // staus : = 1,pre-filled or 0,user-filled
 hnt[9][9],    // hints   = 1,yes  or =0,no
 mat[9][9];


#include "s_algoth.cpp"
#include "s_button.cpp"
#include "s_dsgn.cpp"
#include "s_file.cpp"

/*
#include "c:\tc\bin\s_algoth.cpp"
#include "c:\tc\bin\s_button.cpp"
#include "c:\tc\bin\s_dsgn.cpp"
#include "c:\tc\bin\s_file.cpp"
*/

void wait_mouse();
void Control(void);
void Usr_Submit(void);

//---------------------------------------------------------------
void wait_mouse()
{
   // quit via menu
   if(code==44)
   {
      if(o.x.cx>=215 && o.x.dx>=260 && o.x.cx<=285 && o.x.dx<=280)
      {
	frame(215,260,285,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(240,265,"YES");delay(200);
	closegraph();exit(0);
      }

      if(o.x.cx>=328 && o.x.dx>=260 && o.x.cx<=403 && o.x.dx<=280)
      {
	frame(328,260,403,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(357,265,"NO");delay(200);
	code = 0;
	Message_Box();
      }
      return;
   }

   // quit via corner button
   if(o.x.cx>=613 && o.x.dx>=7 && o.x.cx<=638 && o.x.dx<=27)
   {
      code = 44; // quit
      fill_maze();
      frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
      frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
      frame(196,186,424,200,BLUE,BLUE,BLUE);
      settextstyle(0,0,1);
      setcolor(WHITE);
      outtextxy(280,190,"MESSAGE");
      setcolor(BLACK);
      outtextxy(203,216,"DO YOU REALLY WANT TO ");
      outtextxy(203,231,"EXIT ?");

      frame(215,260,285,280,LIGHTGRAY,DARKGRAY,WHITE);
      frame(328,260,403,280,LIGHTGRAY,DARKGRAY,WHITE);
      outtextxy(240,265,"YES");
      outtextxy(357,265,"NO");
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      menubar();
      return;
   }
   ///////////////////////////////////////////
   if(code == 47) // load a game from file
   {
      if(o.x.cx>=215 && o.x.dx>=260 && o.x.cx<=285 && o.x.dx<=280)
      {
	frame(215,260,285,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(235,265,"OPEN");
	delay(200);
	load();
	Message_Box();
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	code = 0;
	fill_maze();

	while(o.x.cx>=45 && o.x.dx>=31 && o.x.cx<=105 && o.x.dx<=70)
	{
	 frame(45,31,105,70,BLUE,BLUE,BLUE);
	 showmouse();getmousepos();
	}
	menubar();
      }
      //--------------------------------------------------------
      if(o.x.cx>=328 && o.x.dx>=260 && o.x.cx<=403 && o.x.dx<=280)
      {
	frame(328,260,403,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(343,265,"CANCEL");delay(200);
	code = 0;
	Message_Box();
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	menubar();
      }
      return;
   }
  ///////////////////////////////////////////
   if(code == 48) // save a game to file
   {
      if(o.x.cx>=215 && o.x.dx>=260 && o.x.cx<=285 && o.x.dx<=280)
      {
	frame(215,260,285,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(245,265,"OK");
	delay(200);
	save();
	code = 0;
	Message_Box();
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	menubar();
	fill_maze();

	while(o.x.cx>=45 && o.x.dx>=31 && o.x.cx<=105 && o.x.dx<=70)
	{
	 frame(45,31,105,70,BLUE,BLUE,BLUE);
	 showmouse();getmousepos();
	}
	menubar();

      }
     //--------------------------------------------------------
      if(o.x.cx>=328 && o.x.dx>=260 && o.x.cx<=403 && o.x.dx<=280)
      {
	frame(328,260,403,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(343,265,"CANCEL");
	delay(200);
	code = 0;
	Message_Box();
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	menubar();
      }
      return;
   }
   ///////////////////////////////////////////
   //////////////////////////////////////////
   if(code == 42) // resign
   {
      if(o.x.cx>=215 && o.x.dx>=260 && o.x.cx<=285 && o.x.dx<=280)
      {
	frame(215,260,285,280,DARKGRAY,LIGHTGRAY,WHITE);
	outtextxy(240,265,"YES");
	delay(200);
	Message_Box();
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	menubar();

	for(int i=0;i<9;i++)
	  for(int j=0;j<9;j++)
	   {
	      arr[i][j] = puzz[i][j];
	   }

	Message_Box();

	for( i=0;i<9;i++)
	  for( j=0;j<9;j++)
	   {
	     arr[i][j] = stat[i][j] = puzz[i][j] = hnt[i][j] = 0;
	   }

	code = 0;
	puz_typ = 0;
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	frame(45,31,105,70,BLUE,BLUE,BLUE);
	menubar();
	return;
      }
    //-------------------------------------------------------------
      if(o.x.cx>=328 && o.x.dx>=260 && o.x.cx<=403 && o.x.dx<=280)
      {
       frame(328,260,403,280,DARKGRAY,LIGHTGRAY,WHITE);
       outtextxy(357,265,"NO");
       delay(200);
       code = 0;
       Message_Box();
       frame(5,31,260,90,BLUE,BLUE,BLUE);
       menubar();
      }
      return;
   }

   if(menu_bar_effect())
   { return; }

   if( o.x.cx>=127 && o.x.dx>=27 && o.x.cx<=191 && o.x.dx<=85
      && men_stat == 4 && puz_typ != 0)
     {
	men_stat = 0;

	if( o.x.dx<=42   )
	{
	    if(code != 41)  // pause
	    { code = 41;fill_maze(); }

	    else if(code == 41)    // resume
	    {
	       code = 0; fill_maze();
	       while(o.x.cx>=127 && o.x.dx>=27 && o.x.cx<=191 && o.x.dx<=72)
	       {
		  frame(5,31,260,90,BLUE,BLUE,BLUE);
		  showmouse();
		  getmousepos();
	       }
	       menubar();
	       return;
	     }
	}

	else if( o.x.dx<=55 )   //   Resign();
	{
	    if(code != 41)  // not pause
	    {
	       code = 42;
	       fill_maze();
	       frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	       frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	       frame(196,186,424,200,BLUE,BLUE,BLUE);
	       setcolor(WHITE);
	       settextstyle(0,0,1);
	       outtextxy(280,190,"MESSAGE");
	       setcolor(BLACK);
	       outtextxy(203,216,"DO YOU REALLY WANT TO ");
	       outtextxy(203,231,"RESIGN ?");

	       frame(215,260,285,280,LIGHTGRAY,DARKGRAY,WHITE);
	       frame(328,260,403,280,LIGHTGRAY,DARKGRAY,WHITE);
	       outtextxy(240,265,"YES");
	       outtextxy(357,265,"NO");
	    }
	}

	else if( o.x.dx<=72 )  //   Hint
	{
	  if(code != 41)
	  {
	  char *an;
	  int i,j,curr,flag=1;
	  settextstyle(6,0,4);

	  for(i=0;i<9;i++)
	    for(j=0;j<9;j++)
	      if(arr[i][j] != puzz[i][j])
		 { flag = 0; break; }

	  if(flag == 0 && cnt != 81)
	  {
	   while(1)
	   {
	    i =  abs(rand() % 9),j =  abs(rand() % 9);
	    if(stat[i][j]==0 && (arr[i][j]==0 || arr[i][j]!=puzz[i][j] ))
	       break;
	   }

	   curr = puzz[i][j];
	   stat[i][j] = arr[i][j] = hnt[i][j] = curr;
	   cnt++;

	   switch(curr)
	   {
	     case 1:   an="1";  break;
	     case 2:   an="2";  break;
	     case 3:   an="3";  break;
	     case 4:   an="4";  break;
	     case 5:   an="5";  break;
	     case 6:   an="6";  break;
	     case 7:   an="7";  break;
	     case 8:   an="8";  break;
	     case 9:   an="9";  break;
	     case 10:  an=" ";  break;
	   }

	  int l=((i*40)+150);
	  int t=((j*40)+100);

	  setcolor(BLACK);
	  for(int k=l+4;k<l+40-4;k++)
	     line(k,t+4,k,t+40-4);

	  setcolor(YELLOW);
	  outtextxy((i*40)+165 ,(j*40)+95 ,an);
	}}}

	else if( o.x.dx<=85 )  //   Submit
	{
	  Usr_Submit();
	}

	while(o.x.cx>=127 && o.x.dx>=27 && o.x.cx<=191 && o.x.dx<=72)
	{   frame(5,31,260,90,BLUE,BLUE,BLUE);
	    showmouse();  getmousepos();    }

	menubar();
	return;
     }
///////////////////////////////////////////////////////////////////////////
   if( o.x.cx>=86 && o.x.dx>=27 && o.x.cx<=130 && o.x.dx<=60
      && men_stat == 3 && puz_typ != 0)                     // reset
     {
	men_stat = 0;

	if(o.x.dx<=42)    // reset
	{
	  for(int i=0; i<9 ; i++)
	    for(int j=0; j<9 ; j++)
	    {
	       if( stat[i][j] == 0 && arr[i][j] != 0 )
	       {
		   arr[i][j] = 0;
	       }
	    }
	    code = 41;fill_maze();
	    code = 0;fill_maze();
	}

	else if( o.x.dx<=55 )   //   Timer
	{

	}

	while(o.x.cx>=86 && o.x.dx>=27 && o.x.cx<=130 && o.x.dx<=72)
	{   frame(5,31,260,90,BLUE,BLUE,BLUE);
	    showmouse();  getmousepos();    }

	menubar();
	return;
     }
//////////////////////////////////////////////////////////////////////////
   else if( o.x.cx>=5 && o.x.dx>=27 && o.x.cx<=66 && o.x.dx<=70 && men_stat == 1)
   {
      men_stat = 0;
      if( o.x.dx<=42 )  // save game to a file
       {
	  if( puz_typ <= 0)
	  {
	  fill_maze();
	  frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	  frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	  frame(196,186,424,200,BLUE,BLUE,BLUE);
	  setcolor(WHITE);
	  settextstyle(0,0,1);
	  outtextxy(270,190,"SAVE GAME");
	  setcolor(BLACK);
	  outtextxy(230,231," NO GAME TO SAVE");
	  delay(900);
	  Message_Box();
	  }

	  else
	  {
	  code = 48;
	  File_name[0] = '\0';
	  nam_siz = 0;
	  fill_maze();
	  frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	  frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	  frame(196,186,424,200,BLUE,BLUE,BLUE);
	  setcolor(WHITE);
	  settextstyle(0,0,1);
	  outtextxy(270,190,"SAVE GAME");
	  setcolor(BLACK);
	  outtextxy(203,211,"ENTER THE FILE NAME :  ");
	  frame(207,225,410,245,LIGHTGRAY,LIGHTGRAY,BLACK);
	  frame(215,260,285,280,LIGHTGRAY,DARKGRAY,WHITE);
	  frame(328,260,403,280,LIGHTGRAY,DARKGRAY,WHITE);
	  outtextxy(245,265,"OK");
	  outtextxy(343,265,"CANCEL");
	  }
       }

      else if( o.x.dx>=42 && o.x.dx<=55 )    // load
       {
	  code = 47; // load
	  File_name[0] = '\0';
	  nam_siz = 0;
	  fill_maze();
	  frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	  frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	  frame(196,186,424,200,BLUE,BLUE,BLUE);
	  setcolor(WHITE);
	  settextstyle(0,0,1);
	  outtextxy(260,190,"OPEN A FILE");
	  setcolor(BLACK);
	  outtextxy(203,211,"ENTER THE FILE NAME :  ");
	  frame(207,225,410,245,LIGHTGRAY,LIGHTGRAY,BLACK);
	  frame(215,260,285,280,LIGHTGRAY,DARKGRAY,WHITE);
	  frame(328,260,403,280,LIGHTGRAY,DARKGRAY,WHITE);
	  outtextxy(235,265,"OPEN");
	  outtextxy(343,265,"CANCEL");
      }

      else if( o.x.dx<=72 )
       {
	   code = 44; // quit
	   fill_maze();
	   frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	   frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	   frame(196,186,424,200,BLUE,BLUE,BLUE);
	   setcolor(WHITE);
	   settextstyle(0,0,1);
	   outtextxy(280,190,"MESSAGE");
	   setcolor(BLACK);
	   outtextxy(203,216,"DO YOU REALLY WANT TO ");
	   outtextxy(203,231,"EXIT ?");

	   frame(215,260,285,280,LIGHTGRAY,DARKGRAY,WHITE);
	   frame(328,260,403,280,LIGHTGRAY,DARKGRAY,WHITE);
	   outtextxy(240,265,"YES");
	   outtextxy(357,265,"NO");
       }
   }

   // new puzzle :-
   else if( o.x.cx>=45 && o.x.dx>=31 && o.x.cx<=105 && o.x.dx<=70 && men_stat == 2)
   {
      men_stat = 0;

      for(int i=0;i<9;i++)
	for(int j=0;j<9;j++)
	     arr[i][j] = stat[i][j] = puzz[i][j] = hnt[i][j] = 0;

      cnt = 0;
      Message_Box();    // clears the board
      if( o.x.dx<=42 )	   puz_typ = 1;    // EASY
      else if(o.x.dx<=55)  puz_typ = 2;    // MEDIUM
      else if(o.x.dx<=72)  puz_typ = 3;    // HARD

      generate_puzzle(puz_typ);
      fill_maze();

      while(o.x.cx>=45 && o.x.dx>=31 && o.x.cx<=105 && o.x.dx<=70)
      {
	 frame(45,31,105,70,BLUE,BLUE,BLUE);
	 showmouse();getmousepos();
      }
      menubar();
      return;
   }

      // help
   else if( o.x.cx>=175 && o.x.dx>=31 && o.x.cx<=250 && o.x.dx<=60 && men_stat == 5)
     {
      men_stat = 0;
      if( o.x.dx<=42 )  // about
       {
	 fill_maze();
	 frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	 frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	 frame(196,186,424,200,BLUE,BLUE,BLUE);
	 setcolor(WHITE);
	 settextstyle(0,0,1);
	 outtextxy(280,190,"ABOUT");
	 setcolor(BLACK);
	 outtextxy(203,211,"Puzzle Sudoku ver. 1.3");
	 outtextxy(203,235,"For more details contact");
	 outtextxy(203,256," tejas_itstudent@yahoo.com ");
	 delay(3000);
       }

      else if( o.x.dx<=55 )  // credit
       {
	 fill_maze();
	 frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	 frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	 frame(196,186,424,200,BLUE,BLUE,BLUE);
	 setcolor(WHITE);
	 settextstyle(0,0,1);
	 outtextxy(270,190,"CREDITS");
	 setcolor(BLACK);
	 outtextxy(203,211," Made by :  ");
	 outtextxy(203,225,"   Tejas. A. Patil  ");
	 outtextxy(203,236,"   SE I.T MIT , Pune  ");
	 outtextxy(203,249,"I am thankful to my   ");
	 outtextxy(203,260,"Parents , Teachers and");
	 outtextxy(203,271,"Friends for their support");
	 outtextxy(203,282," and help.");
	 delay(3000);
       }
	 Message_Box();
	frame(5,31,260,90,BLUE,BLUE,BLUE);
	frame(45,31,105,70,BLUE,BLUE,BLUE);
	menubar();
   }

      // board
   if(o.x.cx>=150 && o.x.dx>=100 && o.x.cx<=510 && o.x.dx<=460)
   {
     int  xr = (o.x.cx-150)/40,
	  yr = (o.x.dx-100)/40;

     if(code > 40 ) return;
     if(puz_typ == 0 ) return;
     if(curr != 10 && arr[xr][yr] != 0)
	     Number_Pad(arr[xr][yr]-1);

     if(stat[xr][yr] != 0 ) return;
     if(cnt == 81 && curr != 10)    return;

     else
     {
	char *an;
	settextstyle(6,0,4);
	setcolor(LIGHTCYAN);
	switch(curr)
	{
	   case 1:   an="1"; break;
	   case 2:   an="2"; break;
	   case 3:   an="3"; break;
	   case 4:   an="4"; break;
	   case 5:   an="5"; break;
	   case 6:   an="6"; break;
	   case 7:   an="7"; break;
	   case 8:   an="8"; break;
	   case 9:   an="9"; break;
	   case 10:  an=" "; break;
       }

    do
    {
       if(curr != 10  &&  arr[xr][yr] == 0 && cnt != 81)
       { outtextxy((xr*40)+165, (yr*40)+95, an); }

       else if (curr == 10)
       {
	   int l=((xr*40)+150);
	   int t=((yr*40)+100);

	   setcolor(BLACK);
	   for(int k=l+4;k<l+40-4;k++)
	      line(k,t+4,k,t+40-4);

	   setcolor(WHITE);
       }
	   restrictmouse();
	   showmouse();
	   getmousepos();
    }
	while(o.x.cx>=((xr*40)+150) &&  o.x.dx>=((yr*40)+100) &&
	      o.x.cx<=((xr*40)+190) &&  o.x.dx<=((yr*40)+140)  );

       if(curr != 10  &&  arr[xr][yr] == 0 && cnt != 81)
	  cnt++;

       else if(curr == 10 && arr[xr][yr] != 0)  cnt--;

       arr[xr][yr] = (curr%10);
    }
  }

   if(o.x.cx>=40 && o.x.dx>=130 && o.x.cx<=70 && o.x.dx<=430 && code < 40
      && puz_typ != 0)
   {
      int p = (o.x.dx-130)/30;
      Number_Pad(p);
   }


   if(men_stat != 0)
   {
      men_stat = 0;
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      menubar();
   }
}
//---------------------------------------------------------------
void main()
{
   int i,j;
   clrscr();

   for(i=0;i<9;i++)     // flush all the arrays
      for(j=0;j<9;j++)
	 cnt = arr[i][j] = stat[i][j] = puzz[i][j] = hnt[i][j] = 0;

   int gd=DETECT,gm;
   initgraph(&gd, &gm,path);

   if(LOAD)  loading();

   clrscr();
   initgraph(&gd, &gm,path);

   setbkcolor(BLACK);
   rectangle(0,27,637,477);
   setfillstyle(1,BLUE);
   floodfill(25,30,15);
   frame(20,100,90,460,LIGHTRED,RED,GREEN);

   _1.draw();   _4.draw();   _7.draw();
   _2.draw();   _5.draw();   _8.draw();
   _3.draw();   _6.draw();   _9.draw();
   _ER.draw();

   ext_button();
   menubar();
   maze();
   fill_maze();
   Control();
}
//------------------------------------------------------------
void Control()
{
   do
    {
      _1.button_effect();_2.button_effect();_3.button_effect();
      _4.button_effect();_5.button_effect();_6.button_effect();
      _7.button_effect();_8.button_effect();_9.button_effect();
      _ER.button_effect();_1.higlt(curr);

      restrictmouse();     showmouse();
      get_mouse();         getmousepos();
      wait_mouse();        hide_mouse();
    }
    while(1);
}
//---------------------------------------------------------------
void Usr_Submit(void)
{
   if(cnt < 81)  // fill all positions and then try
   {
	frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(196,186,424,200,BLUE,BLUE,BLUE);
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(280,190,"MESSAGE");
	setcolor(BLACK);
	outtextxy(203,216,"FILL ALL POSITIONS AND");
	outtextxy(203,231,"THEN TRY !");
	delay(1000);
	Message_Box();
   }

   else //if(cnt == 81)
   {
      int flag = 0;

      for(int i=0;i<9;i++)
	for(int j=0;j<9;j++)
	{
	  if(arr[i][j] != puzz[i][j])
	  {   flag = 1;
	      break;
	  }
	}

       if(flag == 1)
       {
	frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(196,186,424,200,BLUE,BLUE,BLUE);
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(280,190,"MESSAGE");
	setcolor(BLACK);
	outtextxy(203,230,"YOUR SOLUTION IS WRONG.");
	outtextxy(203,246,"DO TRY !");
	delay(1000);
	Message_Box();
	cnt = 81;
       }

       else
       {
	frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(196,186,424,200,BLUE,BLUE,BLUE);
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(280,190,"MESSAGE");
	setcolor(BLACK);
	outtextxy(203,230,"CONGRATULATIONS !! ");
	outtextxy(203,246,"YOU HAVE CRACKED THIS ONE.");
	delay(1000);
	Message_Box();
	for(i=0;i<9;i++)     // flush all the arrays
	  for(j=0;j<9;j++)
	    cnt = arr[i][j] = stat[i][j] = puzz[i][j] = hnt[i][j] = 0;

	maze();
	fill_maze();
	men_stat = 0;
	code = -1;
	puz_typ = 0;
	Number_Pad(9);
	curr=10;
       }
   }
}
