// Design section

void getmousepos();
void initmouse();
void showmouse();
void get_mouse();
void restrictmouse();
void hide_mouse();
void fill_maze();
void maze();
void ext_button();
void loading(void);
void check_MENU_file();
void check_MENU_new();
void check_MENU_mode();
void check_MENU_game();
void check_MENU_help();
void menubar();
void frame(int,int,int,int,int,int,int);
int menu_bar_effect();
void Message_Box();
void Number_Pad(int);
//--------------------------------------------------------
void getmousepos()
{
  i.x.ax=3;
  int86(0x33,&i,&o);

//  int x = wherex(),
//      y = wherey();

//   int x1,y1;
//   gotoxy(72,4);
//   x1 = o.x.cx , y1 = o.x.dx;
//   printf("%3d,%3d",x1,y1);
//   gotoxy(x,y);

   if(code == 47 || code == 48) // load or save
   {
     while(kbhit())
     {
       if(nam_siz < 20)
       {
	 char ad;
	 ad = getch();
	 File_name[nam_siz] = ad;
	 File_name[nam_siz + 1] = '\0';
	 gotoxy(27, 15);
	 nam_siz++;
	 cout<<File_name;
       }
     }
   }

   if(o.x.dx>=27)
   {
     if( o.x.cx>=1 && o.x.cx<=66 && men_stat == 1)
       check_MENU_file();

     else if( o.x.cx>=40 && o.x.cx<=108 && men_stat == 2)
       check_MENU_new();

     else if( o.x.cx>=82 && o.x.cx<=138 && men_stat == 3)
       check_MENU_mode();

     else if( o.x.cx>=127 && o.x.cx<=191 && men_stat == 4)
       check_MENU_game();

     else if( o.x.cx>=172 && o.x.cx<=254 && men_stat == 5)
       check_MENU_help();
   }
}
//--------------------------------------------------------
void initmouse()                 // Initilise Mouse pointer
{   i.x.ax=0;  int86(0X33,&i,&o);  }
//--------------------------------------------------------
void showmouse()          	// Display Mouse pointer
{   i.x.ax=1;  int86(0X33,&i,&o);  }
//--------------------------------------------------------
void get_mouse()           // Get Mouse Click
{
  i.x.ax=3; i.x.bx=0;
  while(o.x.bx == 0)
  {
      getmousepos();
      int86(0x33,&i,&o);
  }
}
//--------------------------------------------------------
void restrictmouse()
{
    i.x.ax=7;
    i.x.cx=getmaxx();
    i.x.dx=0;
    int86(0X33,&i,&o);

    i.x.ax=8;                 // Restrict The Mouse
    i.x.cx=0;
    i.x.dx=getmaxy();
    int86(0X33,&i,&o);
}
//--------------------------------------------------------
void hide_mouse()	 // To Hide Mouse !! DISCARDED !!
{ /* i.x.ax=2;  int86(0x33,&i,&o); */ }
//--------------------------------------------------------
void fill_maze()
{
   char *an;

   if(!(code > 40 && code != 42))
	cnt = 0;

   settextstyle(6,0,4);
   for(int i=0;i<9;i++)
   {
     for(int j=0;j<9;j++)
     {
	if(code > 40 && code != 42)
	 {
	   int l=((i*40)+150);
	   int t=((j*40)+100);

	   setcolor(BLACK);
	    for(int j=l+4;j<l+40-4;j++)
	       line(j,t+4,j,t+40-4);
	 }

	else
	 {
	   if( hnt[i][j] != 0)
	      setcolor(YELLOW);

	   else if( stat[i][j] != 0)
	      setcolor(WHITE);

	   else if( stat[i][j] == 0 && arr[i][j] != 0)
	      setcolor(LIGHTCYAN);

	   else
	     continue;

	   switch(arr[i][j])
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
	   }
	   outtextxy((i*40)+165 ,(j*40)+95 ,an);
	   cnt++;
	 }
     }
   }
}
//--------------------------------------------------------
void maze()      // generates the 9 * 9 sudoku board
{
   int x,x1,y,y1,z,k;
   x=150;  y=100;   x1=510;  y1=460;  z=40;

   frame(150,100-1,512,462,WHITE,WHITE,BLACK);
   setcolor(LIGHTGRAY);
   setlinestyle( 0, 0, THICK_WIDTH );

   for(k=0 ; k<10 ; k++)
      line(x , y+(z*k) , x1 , y+(z*k));

   for(k=0 ; k<10 ; k++)
      line(x+(z*k) , y , x+(z*k) , y1);

   setcolor(15);

   for(k=0 ; k<10 ; k++)
   {
     if(! (k%3))
	{
	    line(x+(z*k)-1 , y-1 , x+(z*k)-1 , y1+1);
	    line(x+(z*k)+1 , y-1 , x+(z*k)+1 , y1+1);
	}
   }

   for(k=0 ; k<10 ; k++)
    {
      if(! (k%3))
	{
	   line(x-1 , y+(z*k)-1 , x1+1 , y+(z*k)-1);
	   line(x-1 , y+(z*k)+1 , x1+1 , y+(z*k)+1);
	}
    }
    setlinestyle( 0, 0, NORM_WIDTH );
}
//--------------------------------------------------------
void ext_button()
{
   int x=610, y=4, x1=640 ,y1=29;

   rectangle(x+2,y+2,x1-2,y1-2);
   setfillstyle(1,DARKGRAY);
   floodfill(x+5,y+5,15);

   setlinestyle( 0, 0, THICK_WIDTH );
   line( x+7,  y+7, x1-7 , y1-7);
   line( x1-7 ,y+7, x+7  , y1-7);
   setlinestyle( 0, 0, NORM_WIDTH );
}
//--------------------------------------------------------
void loading(void)
{
   char *string;
   double value;
   int dec, sign;

   setbkcolor(BLACK);
   setfillstyle(1,LIGHTBLUE);
   frame(67,62,573,398,BLUE,BLUE,LIGHTBLUE);
   frame(70,65,570,395,BLUE,BLUE,LIGHTBLUE);
   frame(71,66,569,394,BLUE,BLUE,LIGHTBLUE);

   settextstyle(0,0,4);
   setcolor(BLUE);
   outtextxy(110,120,"PUZZLE SUDOKU");
   settextstyle(0,0,1);
//   outtextxy(365,200,"Made by :");
//   outtextxy(395,220,"TEJAS. A. PATIL");
//   outtextxy(395,235,"SE I.T, MIT, Pune");
   frame(105,160,535,161, WHITE, WHITE, WHITE);

   line (320-150,320-3,320+150,320-3);
   line (320-150,320+12,320+150,320+12);
   line (320-150,320-3,320-150,320+12);
   line (320+150,320+12,320+150,320-3);
   int s=30,w;
   settextstyle(0,0,1);
   setcolor(BLACK);
   outtextxy(170,290,"LOADING ......");
   for (int x1=171,x2=171,y1=318,y2=331,y=1,S=0;
	x1<470;
	x1++,x2++,y++,S++)
	 {
	   setcolor(BLUE);
	   line (x1,y1,x2,y2);
	   w = (x1-169)/3;
	   for (int i=34; i<=78; i++)
	     {
	       settextstyle(0,0,1);
	       outtextxy(130+i,180," ");
	     }

	   frame(290,283,310,300,LIGHTBLUE,LIGHTBLUE,LIGHTBLUE);
	   settextstyle(0,0,1);

	   if(w < 10)
	   {
	     value = (double)w;
	     string = ecvt(value,1, &dec, &sign);
	     setcolor(BLACK);
	     outtextxy(295,288,string);
	     outtextxy(303,288,"%");
	   }

	   else
	   {
	     value = (double)w;
	     string = ecvt(value,2, &dec, &sign);
	     setcolor(BLACK);
	     outtextxy(295,288,string);
	     outtextxy(315,288,"%");
	   }

	   if (x2>270) s=45;
	   if (x2>370) s=10;
	   if (x2==320) delay(700);
	   else delay(s);
	 }

    frame(160,230,355,300,LIGHTBLUE,LIGHTBLUE,LIGHTBLUE);
    setcolor(BLACK);
    outtextxy(170,290,"          CLICK TO CONTINUE ");
    restrictmouse();
    showmouse();
    get_mouse();
}
//--------------------------------------------------------
void check_MENU_file()
{
  settextstyle(11,0,1);
  setcolor(4);
  outtextxy(7,11,"FILE");    // save, load, quit
  if( o.x.dx>=27 && o.x.dx<=42 )
   {outtextxy(7,32,"SAVE");setcolor(0);
    outtextxy(7,45,"LOAD");outtextxy(7,58,"QUIT"); }

  if( o.x.dx>=42 && o.x.dx<=55 )
   {outtextxy(7,45,"LOAD");setcolor(0);
    outtextxy(7,32,"SAVE");outtextxy(7,58,"QUIT"); }

  if( o.x.dx>=55 && o.x.dx<=72 )
   {outtextxy(7,58,"QUIT");setcolor(0);
    outtextxy(7,32,"SAVE");outtextxy(7,45,"LOAD"); }
}
//--------------------------------------------------------
void check_MENU_new()
{
  settextstyle(11,0,1);
  setcolor(4);
  outtextxy(55,11,"NEW");    // easy, medium, hard
  if( o.x.dx>=27 && o.x.dx<=42 )
   {outtextxy(50,32,"EASY");setcolor(0);
    outtextxy(50,45,"MEDIUM");outtextxy(50,58,"HARD"); }

  if( o.x.dx>=42 && o.x.dx<=55 )
   {outtextxy(50,45,"MEDIUM");setcolor(0);
    outtextxy(50,32,"EASY");outtextxy(50,58,"HARD"); }

  if( o.x.dx>=55 && o.x.dx<=72 )
   {outtextxy(50,58,"HARD");setcolor(0);
    outtextxy(50,32,"EASY");outtextxy(50,45,"MEDIUM");  }
}
//--------------------------------------------------------
void  check_MENU_mode()
{
   settextstyle(11,0,1);
  setcolor(4);
  outtextxy(94,11,"MODE");
  if( o.x.dx>=27 && o.x.dx<=42 )
   {outtextxy(90,32,"RESET");setcolor(0);outtextxy(90,45,"TIMER");}

  if( o.x.dx>=42 && o.x.dx<=55 )
   {outtextxy(90,45,"TIMER");setcolor(0);outtextxy(90,32,"RESET");}
}
//--------------------------------------------------------
void check_MENU_game()
{
  settextstyle(11,0,1);
  setcolor(4);outtextxy(140,11,"GAME");   // pause, resign, hint
  if( o.x.dx>=27 && o.x.dx<=42 )
   {  if(code != 41)  outtextxy(135,32,"PAUSE");
      else            outtextxy(135,32,"RESUME");
      setcolor(0);outtextxy(135,45,"RESIGN");
      outtextxy(135,58,"HINT");outtextxy(135,71,"SUBMIT"); }

  else if( o.x.dx>=42 && o.x.dx<=55 )
   {  outtextxy(135,45,"RESIGN"); setcolor(0);
      if(code != 41)  outtextxy(135,32,"PAUSE");
      else            outtextxy(135,32,"RESUME");
      outtextxy(135,58,"HINT");outtextxy(135,71,"SUBMIT");}

  else if( o.x.dx>=55 && o.x.dx<=70 )
   {   outtextxy(135,58,"HINT"); setcolor(0);
       if(code != 41)  outtextxy(135,32,"PAUSE");
       else            outtextxy(135,32,"RESUME");
       outtextxy(135,45,"RESIGN");outtextxy(135,71,"SUBMIT");}

  else if( o.x.dx>=71 && o.x.dx<=87 )
   {   outtextxy(135,71,"SUBMIT"); setcolor(0);
       if(code != 41)  outtextxy(135,32,"PAUSE");
       else            outtextxy(135,32,"RESUME");
       outtextxy(135,58,"HINT");outtextxy(135,45,"RESIGN");}
}
//--------------------------------------------------------
void check_MENU_help()
{
   settextstyle(11,0,1);
  setcolor(4); outtextxy(187,11,"HELP");
  if( o.x.dx>=27 && o.x.dx<=42 )
   {outtextxy(182,32,"ABOUT");setcolor(0);outtextxy(182,45,"CREDITS");}

  else if( o.x.dx>42 && o.x.dx<=55 )
   {outtextxy(182,45,"CREDITS");setcolor(0);outtextxy(182,32,"ABOUT"); }
}
//--------------------------------------------------------
void menubar()
{
   frame(3,9,607,23,LIGHTGRAY,DARKGRAY,LIGHTGRAY);
   settextstyle(11,0,1);
   setcolor(BLACK);
   outtextxy(7,11,"FILE");    // save, load, quit
   outtextxy(55,11,"NEW");    // easy, medium, hard
   outtextxy(94,11,"MODE");   // practice, match
   outtextxy(140,11,"GAME");  // pause, resign, hint
   outtextxy(187,11,"HELP");  // about,credit
}
//--------------------------------------------------------
void frame(int ax,int ay,int bx,int by,int co1,int co2,int co3)
{
// col1 = upper border, col2 = lower border, col3 = inner portion

 setfillstyle(1,co3);
 bar(ax,ay,bx,by);

 setcolor(co1);
 rectangle(ax-1,ay-1,bx+1,by+1);
 rectangle(ax-2,ay-2,bx+2,by+2);
 rectangle(ax-3,ay-3,bx+3,by+3);

 setcolor(co2);
 line(bx+1,ay-1,bx+1,by+3);
 line(bx+2,ay-2,bx+2,by+3);
 line(bx+3,ay-3,bx+3,by+3);
 setcolor(co2);
 line(ax-1,by+1,bx+3,by+1);
 line(ax-2,by+2,bx+3,by+2);
 line(ax-3,by+3,bx+3,by+3);
}
//--------------------------------------------------------
int menu_bar_effect()
{
   if(o.x.cx>=1 && o.x.dx>=6 && o.x.cx<=45 && o.x.dx<=25 && code < 40)
   {
      menubar();
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      frame(5,31,65,70,LIGHTGRAY,DARKGRAY,LIGHTGRAY);
      setcolor(4);
      outtextxy(7,11,"FILE");    // save, load, quit
      setcolor(0);
      settextstyle(11,0,1);
      outtextxy(7,32,"SAVE");
      outtextxy(7,45,"LOAD");
      outtextxy(7,58,"QUIT");
      men_stat = 1;
      return(1);
   }

   if(o.x.cx>=45 && o.x.dx>=6 && o.x.cx<=85 && o.x.dx<=25 &&code <40)
   {
      menubar();
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      frame(45,31,105,70,LIGHTGRAY,DARKGRAY,LIGHTGRAY);
      setcolor(4);
      outtextxy(55,11,"NEW");    // easy, medium, hard
      setcolor(0);
      settextstyle(11,0,1);
      outtextxy(50,32,"EASY");
      outtextxy(50,45,"MEDIUM");
      outtextxy(50,58,"HARD");
      men_stat = 2;
      return(1);
   }

   if(o.x.cx>=85 && o.x.dx>=6 && o.x.cx<=131 && o.x.dx<=25 &&code <40)
   {
      menubar();
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      frame(85,31,135,58,LIGHTGRAY,DARKGRAY,LIGHTGRAY);
      setcolor(4);
      outtextxy(94,11,"MODE");   // practice, match
      setcolor(0);
      settextstyle(11,0,1);
      outtextxy(90,32,"RESET");
      outtextxy(90,45,"TIMER");
      men_stat = 3;
      return(1);
   }

   if(o.x.cx>=131 && o.x.dx>=6 && o.x.cx<=177 && o.x.dx<=25 )
   {
      menubar();
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      frame(131,31,188,83,LIGHTGRAY,DARKGRAY,LIGHTGRAY);
      setcolor(4);
      outtextxy(140,11,"GAME");   // pause, resign, hint
      setcolor(0);
      settextstyle(11,0,1);
      if(code != 41)  outtextxy(135,32,"PAUSE");
      else            outtextxy(135,32,"RESUME");
      outtextxy(135,45,"RESIGN");
      outtextxy(135,58,"HINT");
      outtextxy(135,71,"SUBMIT");
      men_stat = 4;
      return(1);
   }

   if(o.x.cx>=177 && o.x.dx>=6 && o.x.cx<=228 && o.x.dx<=25 &&code <40)
   {
      menubar();
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      frame(177,31,250,58,LIGHTGRAY,DARKGRAY,LIGHTGRAY);
      setcolor(4);
      outtextxy(187,11,"HELP");
      setcolor(0);
      settextstyle(11,0,1);
      outtextxy(182,32,"ABOUT");
      outtextxy(182,45,"CREDITS");
      men_stat = 5;
      return(1);
   }
   return(0);
  }
//--------------------------------------------------------
// very important function
// for displaying the message boxes
void Message_Box()
{
      int x = o.x.cx, y = o.x.dx;
      maze(); fill_maze();

      while(o.x.cx>=x-20 && o.x.dx>=y-20 && o.x.cx<=x+20 && o.x.dx<=y+20)
	{
	    showmouse();
	    getmousepos();
	}

      maze(); fill_maze();
      frame(5,31,260,90,BLUE,BLUE,BLUE);
      menubar();
      return;
}
//--------------------------------------------------------
// highlights the pressed key
void Number_Pad(int p)
 {
    //  curr stores the previuosly pressed key
     switch(p)
       {
	   case 0:_1.button_effect1();_1.highlight(curr); break;
	   case 1:_2.button_effect1();_2.highlight(curr); break;
	   case 2:_3.button_effect1();_3.highlight(curr); break;
	   case 3:_4.button_effect1();_4.highlight(curr); break;
	   case 4:_5.button_effect1();_5.highlight(curr); break;
	   case 5:_6.button_effect1();_6.highlight(curr); break;
	   case 6:_7.button_effect1();_7.highlight(curr); break;
	   case 7:_8.button_effect1();_8.highlight(curr); break;
	   case 8:_9.button_effect1();_9.highlight(curr); break;
	   case 9:_ER.button_effect1();_ER.highlight(curr);break;
       }
       curr = p+1;
 }
//--------------------------------------------------------
