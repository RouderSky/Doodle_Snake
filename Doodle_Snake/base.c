#include "head.h"

//snake stepping: dy = 1(up),-1(down);dx = -1(left),1(right),0(no move)
void snakeMove(char move)
{
	static char lmove='D';
	int dx=0,dy=0,i;
	int flag=1;
	switch(move)
	{
		    case 'A' : 
			case 'a' : dx=-1,dy=0;
					              break;
			case 'W' :
			case 'w' : dx=0,dy=-1;
								  break;
			case 'S' :
			case 's' : dx=0,dy=1;
					          	  break;
			case 'D' :
			case 'd' : dx=1,dy=0;
					          	  break;
			default:flag=0;
	}
		if(snakeX[0]+dx==snakeX[1]&&snakeY[0]+dy==snakeY[1]||flag==0)
			snakeMove(lmove);
		else
		{
			for(i=snakeLength-1;i>0;i--)
			{
				snakeX[i]=snakeX[i-1];
				snakeY[i]=snakeY[i-1];
			}
			snakeX[0]+=dx;
			snakeY[0]+=dy;
			lmove=move;
		}
}

//put a food randomized on a blank cell
void put_money(void)
{
	int flag=1;
	int i;
	srand(time(NULL));
		while(flag)
		{
			food.x=rand()%(BL-2)+1;
			food.y=rand()%(BW-2)+1;
			flag=0;
			for(i=0;i<snakeLength;i++)
			{
				if(snakeX[i]==food.x&&snakeY[i]==food.y)
				{
					flag=1;
					break;
				} 
			}
		}
	det=0;
}

//locate
void gotoxy(int x, int y)		
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//out cells of the grid
void output(void)
{
	int i;                                      //后期使用
	static int n=1;
	gotoxy(locationX,locationY);
	printf(" ");                              //消除蛇的尾巴
	color(14);
	gotoxy(food.x,food.y);
	printf("$");                              //打出食物
	color(11);
	for(i=0;i<snakeLength;i++)
	{
		gotoxy(snakeX[i],snakeY[i]);          //打出蛇身
		printf("*");
	}
	color(112);
	gotoxy(BL+1,3);
	printf("  当前速度等级：%2d",level);
	gotoxy(BL+1,6);
	printf("  当前蛇的长度：%2d",snakeLength);
	gotoxy(BL+1,9);
	printf("  当前食物的坐标：x=%2d,y=%2d",food.x,food.y);
	color(7);
}

/*void output(void) //半成品
{
	int i, j;
	
	char map[12][13] = 
	{"############",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "#          #",
	 "############"};
	for (i = snakeLength - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			map[snakeY[i]][snakeX[i]] = 'H';
		}
		else
		{
			map[snakeY[i]][snakeX[i]] = 'X';
		}
	}
	map[food.y][food.x] = '$';
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}*/


//outs when gameover
void gameresult(int i)
{
	mciSendString(L"stop bgm.mp3", NULL, 0, NULL);

	gotoxy(25,5);
	color(12);
	if(i)	printf("YOU WIN\n");             
	else	
	{
		printf("YOU LOST\n");
	  	mciSendString(L"play gameover.mp3",NULL,0,NULL);
	}
    color(7);
}

//eat food and change length
void eat_change(void)
{
	if(snakeX[0]==food.x&&snakeY[0]==food.y)
	{
		mciSendString(L"play up.mp3",NULL,0,NULL);
		snakeLength++;
		snakeX[snakeLength-1]=locationX;
		snakeY[snakeLength-1]=locationY;
		det=1;
		judge_speed(snakeLength);
	}
}

//判定当前蛇的速度
void judge_speed(int i)
{
	switch(i)    //判定蛇的速度等级（可改）
	{
		case 5:snakespeed=95;level=0;break;


		case 7:snakespeed=85;level=1;break;           //根据蛇身长度来判断速度
		
		
		case 10:snakespeed=75;level=2;break;
		
		
		case 13:snakespeed=65;level=3;break;
		
		
		case 16:snakespeed=55;level=4;break;
		
		
		case 19:snakespeed=45;level=5;break;
	}			
}

//when it was killed by itself,return 0;otherwise return 1;
int zisha(void)
{
	int flag=1,i;
	for(i=1;i<snakeLength;i++)
	{
		if(snakeX[0]==snakeX[i]&&snakeY[0]==snakeY[i])
		{
			flag=0;
			break;
		}
	}
	return flag;
}
/*
//judge the level of the game
void judge_level(int i)              //根据蛇的长度来判断等级
{
	switch(i)
	{
		case 5:level=0;break;
		case 7:level=1;break;         //此函数一旦改动，注意eat_change函数中的snakespeed作相应的调整
		case 10:level=2;break;
		case 13:level=3;break;
		case 16:level=4;break;
		case 19:level=5;break;
	}
}
*/

//颜色函数
void color(int b)          
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;   //空的地方就是底色
    SetConsoleTextAttribute(hConsole,b) ;
} 

//以下用于判断是否重来
int isagain(void)
{
	char i,c;
	int flag;
	gotoxy(0,7);
	color(112);
	printf("您是否想要再来一遍?\n按'y'再来一遍\n按'n'退出游戏\n");
	color(7);
    scanf("%c",&i);
	getchar();                //用于吸收掉多余的回车键
	if(i=='Y'||i=='y')
	{
		flag=1;
	}
	else flag=0;
	return flag;
}