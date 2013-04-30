#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int Probability_Test(int,int,int,int);
void initializeGame();
void insert(int);
void draw(int);
void Problem(int,int);

int cnt1,left[10],
Sudoku[9][3][3],
Solution[9][3][3];   // block,row,column format

void insert(int value)
{
   for(int i = 0 ; i<cnt1 ; i++)
   {
      if(left[i] == value)
	 break;
   }

   if ((cnt1==0)||(i==cnt1 && left[i-1] != value))
    {  left[cnt1] = value;  cnt1++;   }
}

void generate_puzzle(int puzz_typ)
{
  initializeGame();

  if(puzz_typ == 1)  Problem(5,6);
  if(puzz_typ == 2)  Problem(3,4);
  if(puzz_typ == 3)  Problem(2,3);

   int i,j,k,x,y;

   for(i=0 ; i<9 ; i++)
     for(j=0 ; j<9 ; j++)
     {  arr[9][9]=puzz[9][9]=stat[9][9]=hnt[9][9]=0; }


   for(i=0 ; i<9 ; i++)      // convert 3-d to 2-d
     for(j=0 ; j<3 ; j++)
     {
	x = ((i/3)*3) + j;
	for(k=0 ; k<3 ; k++)
	{
	     y = ((i%3)*3 ) + k;
	     puzz[x][y] = Solution[i][j][k];
	     stat[x][y] = arr[x][y] = Sudoku[i][j][k];
	}
     }
}
//////////////////////////////////////////////////////////////////
void Problem(int a,int b)
{
  int i,j,k,blk_cnt,blk_max,value;

  for ( i = 0; i < 9; i++ )
  {
     blk_cnt = 0;
     blk_max = random(2);
     if(blk_max == 1)  blk_max = a;
     else              blk_max = b;

   for ( j = 0; blk_cnt < blk_max; j=(j+1)%3)
   {
     k = random(3);
     if(Sudoku[i][j][k] == 0)
     {
	value = random(3);
	if(value == 1)
	{
	  Sudoku[i][j][k] = Solution[i][j][k];
	  blk_cnt++;
	 }
      }
   }
  }
}
//////////////////////////////////////////////////////////////////
void initializeGame()
{
  int i,j,k,temp,flag1,x,y,z,value;
  randomize();   // initialises a random number generator

  for ( i = 0; i < 9; i++ )   // initialise the arrays to 0
   for ( j = 0; j < 3; j++ )
    for (k = 0; k < 3; k++ )
     Sudoku[i][j][k] = Solution[i][j][k] = 0;// fixedBlocks[i][j][k] =

 for ( i = 0; i < 9; i++ )
 {
  for ( j = 0; j < 3; j++)
  {
   for ( k = 0; k < 3; k++ )
    {
      flag1 = 1;
      cnt1 = 0;

      while( Solution[i][j][k] == 0 && flag1 == 1 && cnt1 != 9)
      {
	flag1 = 0;
	value = random (10);
	if(value == 0) 	flag1=1;

	else
	{
	  // check if entry is not repeated in the block
	  for(x=0 ; x<3 && flag1==0 ; x++)
	   for(y=0 ; y<3 && flag1==0 ; y++ )
	    if(Solution[i][x][y] == value)
	      flag1 = 1;

	  if(flag1==1)  insert(value);

	  else
	  {
	   // check if entry is not repeated in the row
	   z = (i/3) * 3;

	   for(x=0 ; x<3 && flag1==0 ; x++)
	    for(y=0 ; y<3 && flag1==0 ; y++)
	      if(Solution[z+x][j][y] == value)
		flag1 = 1;

	   if(flag1==1)  insert(value);

	   else
	    {
	      // check if entry is not repeated in the column
	      z = (i % 3);

	      for( x = 0 ; x<3 && flag1==0 ; x++)
	       for( y = 0 ; y<3 && flag1 ==0 ; y++ )
		if( Solution[z+(x*3)][y][k] == value)
		   flag1 = 1;

	      if(flag1==1)  insert(value);

	      else
	      {
		flag1 = Probability_Test(i,j,k,value);
		if(flag1 == 1)
		  insert(value);
	      }
	    }
	  }
	}
     }  //  end of while

      if(cnt1 == 9)
      {
       for(int h=0;h<9;h++)
	 for(int m=0;m<3;m++)
	    for(int n=0;n<3;n++)
		Solution[h][m][n] = 0;

	 i = -1 ; j = 3 ; k = 3;
      }
    }  // end of for
   }
  }
}

//-----------------------------------------------------------------------
int Probability_Test(int i1,int j1,int k1,int value)
{  // if success , returns 0
  int x,y,z,m,n,count,arr[10],temp,x1;

  Solution[i1][j1][k1] = value;

  for ( x = 0; x < 9; x++ )
  {
   for ( y = 0; y < 3; y++)
   {
    for ( z = 0; z < 3; z++ )
    {
	count = 0;
	if(Solution[x][y][z] != 0) ; // skip filled places
	else if(x==i1 && y==j1 && z==k1);
	else
	{
	  if(x==i1)           //  if same block
	  {
	   for(m=0;m<3;m++)
	    for(n=0;n<3;n++)
	       if(Solution[x][m][n] != 0)  // consider filled places
		{
		    arr[count] = Solution[x][m][n];
		    count ++;
		}
	  }
     //////////////////////////////////////////////////////
	   if(y==j1 && (x/3 == i1/3))   // same row
	   {
	    x1 = (i1/3) * 3;

	    for(m=0;m<3;m++)
	     for(n=0;n<3;n++)
	     {
	      if(Solution[x1+m][y][n] != 0)  // consider filled places
	      {
	       for(temp=0; temp<count; temp++)
	       {
		if(arr[temp] == Solution[x1+m][y][n])
		{
		  temp = -1;
		  break;
		 }
		}

		if(temp != -1)
		{
		 arr[count] = Solution[x1+m][y][n];
		 count ++;
		}
	     }
	   }

     //////////////////////////////////////////////////////
	   if(z==k1 && (x%3 == i1%3))    // same column
	   {
	    x1 = (i1 % 3);

	    for(m=0;m<3;m++)
	    {
	     for(n=0;n<3;n++)
	     {
	      if( Solution[(m*3)+x1][n][z] != 0 )   // consider filled places
	      {
		for(temp = 0; temp<count; temp++)
		{
		  if(arr[temp] == Solution[(m*3)+x1][n][z])
		  {
		    temp = -1;
		    break;
		  }

		if(temp != -1)
		 {
		   arr[count] = Solution[(m*3)+x1][n][z];
		   count ++;
	 }}}}}}

	 if(count==9&&(x==i1||(z==k1&&(x%3==i1%3))||(y==j1&&(x/3==i1/3))))
	 {
	   Solution[i1][j1][k1] = 0;
	   return(1);
	 }}}
	////////////////////////////////////////////////////////
    }  // end of for
  }   // end of for
 }   // end of for
  return(0);
}
//-----------------------------------------------------------------------
void draw(int a)
// if a = 1 , draw solution
// if a = 2 , draw sudoku
{
   int i,j,k,x,y;

   clrscr();
   for(i=0 ; i<9 ; i++)      // convert 3-d to 2-d
     for(j=0 ; j<9 ; j++)
       mat[i][j] = 0;


   for(i=0 ; i<9 ; i++)      // convert 3-d to 2-d
     for(j=0 ; j<3 ; j++)
     {
	x = ((i/3)*3) + j;
	for(k=0 ; k<3 ; k++)
	{
	     y = ((i%3)*3 ) + k;
	     if(a==1)   mat[x][y] = Solution[i][j][k];
	     if(a==2)   mat[x][y] = Sudoku[i][j][k];
	}
     }
}