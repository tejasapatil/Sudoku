typedef struct sud
{
 int  curr1,
      men_stat1,
      code1,
      puz_typ1,
      cnt1,
      arr1[9][9],
      puzz1[9][9],
      stat1[9][9],
      hnt1[9][9],
      mat1[9][9];
}sud;

sud e;
long int recsize = sizeof(e);
FILE *fp;

int open_file()
{
  fp = fopen(File_name,"rb+");

  if(fp == NULL)
   {
      fp = fopen(File_name,"wb+");

      if(fp == NULL)
      {
	frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
	frame(196,186,424,200,BLUE,BLUE,BLUE);
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(280,190,"ERROR");
	setcolor(BLACK);
	outtextxy(203,230,"FILE NOT FOUND !! ");
	delay(1000);
	Message_Box();
	return(0);
      }
   }
   return(1);
}

void save(void)
{
  int i,j;
  if(open_file())
  {
    fseek(fp,0,SEEK_END);
    for(i=0;i<9;i++)
     for(j=0;j<9;j++)
     {
      e.arr1[i][j] = arr[i][j];
      e.puzz1[i][j] = puzz[i][j];
      e.stat1[i][j] = stat[i][j];
      e.hnt1[i][j] = hnt[i][j];
      e.mat1[i][j] = mat[i][j];
     }

    e.curr1 = curr;
    e.men_stat1 = men_stat;
    e.code1 = code;
    e.puz_typ1 = puz_typ;
    e.cnt1 = cnt;

    fwrite(&e,recsize,1,fp);
    fclose(fp);

    frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
    frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
    frame(196,186,424,200,BLUE,BLUE,BLUE);
    setcolor(WHITE);
    settextstyle(0,0,1);
    outtextxy(280,190," MESSAGE ");
    setcolor(BLACK);
    outtextxy(203,230," GAME SAVED !");
    delay(1000);
    Message_Box();
  }
}

void load(void)
{
  open_file();
  int i,j,no;

  if(fread(&e,recsize,1,fp) == 1)
  {
    for(i=0;i<9;i++)
     for(j=0;j<9;j++)
     {
       arr[i][j] = e.arr1[i][j];
       puzz[i][j] = e.puzz1[i][j];
       stat[i][j] = e.stat1[i][j];
       hnt[i][j] = e.hnt1[i][j];
       mat[i][j] = e.mat1[i][j];
     }

    men_stat = e.men_stat1;
    code = e.code1;
    puz_typ = e.puz_typ1;
    cnt = e.cnt1;
    frame(190,180,430,300,LIGHTBLUE,LIGHTBLUE,WHITE);
    frame(193,183,427,297,LIGHTBLUE,LIGHTBLUE,WHITE);
    frame(196,186,424,200,BLUE,BLUE,BLUE);
    setcolor(WHITE);
    settextstyle(0,0,1);
    outtextxy(280,190," MESSAGE ");
    setcolor(BLACK);
    outtextxy(203,230,"RESTORING THE GAME..");
    delay(500);
    Number_Pad(e.curr1-1);
    curr = e.curr1;
    Message_Box();
  }
}