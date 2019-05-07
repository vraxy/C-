#include <iostream>
#include <curses.h>
#include<stdlib.h>
#include<dos.h>
const int sz=3;
char bars[]="|     |     |     |     |";
int b=sz*6;
struct save
{int arr[sz][sz];};
int turn=0;
int u_done=5;
int u=0;
int max;
int movesmade=1;
int game[sz][sz];
int score=0;
void back(int u);
void up();
void init();
void down();
void display();
void left();
void right();
void error();
int check_greatest();
int s[1000];
int checkmoves();
int checkup();
int checkdown();
int checkleft();
int checkright();

char acceptmove();
save undo[1000];

void main()
{

clrscr();

init();
int ri,rj;

int choose[]={2,2,4,2,2};
for(int i=0;i<sz;i++)
{for(int j=0;j<sz;j++)
 {game[i][j]=0;}
 }
l:

randomize();

ri=random(sz);
rj=random(sz);
game[rj][ri]=2;


int finish=0;
int greatest=0;
do{


int rno;
int cno;
finish=0;
if(movesmade>0)
{
do{
rno=random(sz);
cno=random(sz);
}while(game[rno][cno]!=0);

int rand=random(4);
game[rno][cno]=choose[rand];
}
movesmade=0;
for(i=0;i<sz;i++)
{for(int j=0;j<sz;j++)
  {undo[u].arr[i][j]=game[i][j];}
}
s[u]=score;
label:
display();

for(i=0;i<sz;i++)
{for(int j=0;j<sz;j++)
 {if(game[i][j]==0)
  finish++;
}
}
if(finish==0)
{int check=checkmoves();
 if(check==0)
{delay(500);
 cout<<"\nGAME OVER";
 for(int d=0;d<3;d++)
 {sleep(1);
  cout<<".";}
cout<<"\nPress any key to exit................";
sleep(1);
getch();
exit(0);}
else
goto again;

}




again:
char move=acceptmove();
switch(move)
{case 'w':up();break;
 case 's':down();break;
 case 'a':left();break;
 case 'd':right();break;
 case 'x':exit(0);break;
 case 'u':if(u>0&&u_done>0)
	  {back(u);
	  u_done--;
	  u--;
	  goto label;}

 default :goto again;
 }
if(movesmade==0)
{goto again;}
turn++;
if(turn>0)
u++;

greatest=check_greatest();
}while(greatest<max);

if(greatest>=max)
{display();
 cout<<"\nCongratulations You win in "<<turn<<" turns";
 for(int t=0;t<4;t++)
 {sleep(1);
cout<<".";}
}

getch();
exit(0);
}



//Beginning of functions
void display()
{clrscr();
 cout<<"\t\t2048 - By Varun Kaushik";
 cout<<"\n\t\t********************";


 cout<<"\n\n\n";
 cout<<"score="<<score<<"      UNDOs Left:"<<u_done<<"\n";

 int sp=1;
for(int i=0;i<sz;i++)
{if(i==0)
{cout<<"+";
for(int n=0;n<b-1;n++)
 {cout<<"-";}
cout<<"+\n";
}
for(int k=0;k<=b;k++)
cout<<bars[k];
cout<<"\n";

for(int j=0;j<sz;j++)
 {
 if(game[i][j]<9)
  {sp=4;}
  else if(game[i][j]>9&&game[i][j]<100)
  {sp=3;}
  else if(game[i][j]>100&&game[i][j]<1000)
  {sp=2;}
  else if(game[i][j]>1000)
  {sp=1;}

  if(j==0)
  cout<<"|";

  if(game[i][j]==0)
  {cout<<" ";
  switch(sp)
  {
   case 1:cout<<" ";break;
   case 2:cout<<"  ";break;
   case 3:cout<<"   ";break;
   case 4:cout<<"    ";break;
   }
   cout<<"|";

   }
  else
  {
  switch(sp)
  {
   case 1:cout<<" "<<game[i][j];break;
   case 2:cout<<" "<<game[i][j]<<" ";break;
   case 3:cout<<" "<<game[i][j]<<"  ";break;
   case 4:cout<<"  "<<game[i][j]<<"  ";break;
   }
   cout<<"|";

  }

    }
cout<<"\n";
for( k=0;k<=b;k++)
cout<<bars[k];
cout<<"\n";

 cout<<"+";
for(int n=0;n<b-1;n++)
 {cout<<"-";}

 cout<<"+\n";
 }
}

char acceptmove()
{ display();
cout<<"\n\nEnter your move(w/s/a/d):";
 char move=getch();

 return(move);}

void left()
{for(int j=1;j<sz;j++)
 {for(int i=0;i<sz;i++)
   {if(game[i][j]!=0)
    {for(int left=j;left>0;left--)
    { if(game[i][left-1]==0)
     { movesmade++;
      int temp=game[i][left];
      game[i][left]=game[i][left-1];
       game[i][left-1]=temp;}
      //add
      else if(game[i][left-1]==game[i][left])
      {movesmade++;
       game[i][left-1]=game[i][left]+game[i][left];
       score+=game[i][left-1];
       game[i][left]=0;}



}      if(movesmade!=0)
       {delay(100);
       display();}

}
}
}
}
void right()
{for(int j=sz-2;j>=0;j--)
 {for(int i=0;i<sz;i++)
   {if(game[i][j]!=0)
    {for(int r=j;r<sz-1;r++)
    {if(game[i][r+1]==0)

     {movesmade++;
      int temp=game[i][r];
      game[i][r]=game[i][r+1];
       game[i][r+1]=temp;}
      //add
     else if(game[i][r+1]==game[i][r])
      {movesmade++;
       game[i][r+1]=game[i][r]*2;
       score+=game[i][r+1];
       game[i][r]=0;}
}
}
if(movesmade!=0)
       {delay(200);
       display();
}
}
}

}

void up()
{
for(int i=1;i<sz;i++)
 {for(int j=0;j<sz;j++)
  {if(game[i][j]!=0)
     {for(int up=i;up>0;up--)
       {  if(game[up-1][j]==0)
	   {movesmade++;
	    int temp=game[up][j];
	    game[up][j]=game[up-1][j];
	    game[up-1][j]=temp;}
	   //add
	   else if(game[up-1][j]==game[up][j])
	   {movesmade++;
	    game[up-1][j]=game[up][j]+game[up][j];
	    score+=game[up-1][j];
	    game[up][j]=0;}


	}
	if(movesmade!=0)
       {delay(200);
       display();}
      }
   }

 }
}
void down()
{ for(int i=sz-1;i>=0;i--)
 {for(int j=sz-1;j>=0;j--)
  {if(game[i][j]!=0)
     {for(int down=i;down<sz-1;down++)
       {if(game[down+1][j]==0)
	{movesmade++;
	 int temp=game[down][j];
	 game[down][j]=game[down+1][j];
	 game[down+1][j]=temp;}
	//add
	else if(game[down+1][j]==game[down][j])
	   {movesmade++;
	    game[down+1][j]=game[down][j]+game[down][j];
	    score+=game[down+1][j];
	    game[down][j]=0;}
       }
       if(movesmade!=0)
       {delay(200);
       display();}
     }
  }
}

}

int check_greatest()
{int largest=0;
 for(int i=0;i<sz;i++)
   {for(int j=0;j<sz;j++)
     {largest=game[i][j]>largest?game[i][j]:largest;}
   }
return(largest);
}

void back(int u)
{score=s[u-1];
for(int i=0;i<sz;i++)
 {for(int j=0;j<sz;j++)
  {game[i][j]=undo[u-1].arr[i][j];}
 }
}
int checkright()
{int m=0;
 for(int j=sz-2;j>=0;j--)
 {for(int i=0;i<sz;i++)
  {if(game[i][j]==game[i][j+1])
    {m++;}
    }
  }
  return(m);
  }

  int checkleft()
{int m=0;
 for(int j=1;j>sz;j--)
 {for(int i=0;i<sz;i++)
  {if(game[i][j]==game[i][j+1])
    {m++;}
    }
  }
  return(m);
  }
int checkmoves()
{int moves=0;
 int up=checkup();
 int down=checkdown();
 int right=checkright();
 int left=checkleft();

 moves=up+down+right+left;
 return(moves);
}

int checkup()
{int m_up=0;
 for(int i=1;i<sz;i++)
 {for(int j=0;j<sz;j++)
  {if(game[i][j]==game[i-1][j])
    {m_up++;}
  }
}
  return(m_up);
}

int checkdown()
{int m_d=0;
  for(int i=sz-1;i>0;i--)
 {for(int j=sz-1;j>=0;j--)
  {if(game[i][j]==game[i-1][j])
    m_d++;
   }
  }
  return(m_d);
}
void init()
{
b:
char l;
clrscr();
   cout<<"±±±±±±±±±±±±±±±±±±±±±±±";
 cout<<"\n±±±±2048 MAIN MENU±±±±±\n";
   cout<<"±±±±±±±±±±±±±±±±±±±±±±±\n\n";


cout<<"Choose the maximum no you would like to play till=>";
cout<<"\na) 128";
cout<<"\nb) 256";
cout<<"\nc) 512";
cout<<"\nd) 1028";
cout<<"\ne) 2048";
cout<<"\n\n=>";
cin>>l;
switch(l)
{case 'a':max=128;break;
 case 'b':max=256;break;
 case 'c':max=512;break;
 case 'd':max=1024;break;
 case 'e':max=2048;break;
 default:
 cout<<"\n\n±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±";
 cout<<"\nPlease enter a valid choice.Thank you\n";
 cout<<"±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±\n";
  getch();
goto b;
}
}
