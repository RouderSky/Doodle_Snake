// Created by Hongtao Wang on 15-04-02.

#include "head.h"

/*
//define vars for snake ,notice name of vars in C
int snakeX[SNAKE_MAX_LENGTH]={5,4,3,2,1};
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1};
int snakeLength=5;*/

int main(void)
{
	int i, n;
	char move;
	printf("游戏说明：\n'w'为向上移动\n's'为向下移动\n'a'为向左移动\n'd'为向右移动\n\n\n");
	printf("Createed by 王洪涛\n\n\n");
	printf("请稍等......");
	Sleep(2000);
	do					//由于不可以重复定义，所以定义和初始化分开
	{
		system("cls");

		n = 5;					//用于定位蛇初始的X坐标

		move = 'D';				//蛇最初的移动方向

		situation = 0;			//记录游戏结果

		det = 1;				//食物出现许可

		snakespeed = 95;		//蛇的速度

		level = 0;				//蛇的速度等级

		snakeLength = 5;		//蛇的长度

		for (i = 0; i < 5; i++)	//蛇身开始的地方
		{
			snakeX[i] = n;
			n--;				//注意蛇头方向与move有关联
			snakeY[i] = 1;
		}

		mciSendString(L"play bgm.mp3 repeat", NULL, 0, NULL);
		mciSendString(L"play test.mp4 repeat", NULL, 0, NULL);

		color(116);

		//横为BL,竖为BW
		//打印地图
		for (i = 0; i < BL; i++)    
		{
			gotoxy(i, 0);			
			printf("#");
			gotoxy(i, BW - 1);
			printf("#");
		}
		for (i = 1; i < BW - 1; i++)
		{
			gotoxy(0, i);
			printf("#");
			gotoxy(BL - 1, i);
			printf("#");
		}

		color(7);
		/*for(i=0;i<BL;i++)
		{
		for(j=0;j<BW;j++)
		printf("%c",map[i][j]);
		printf("\n");
		}*/
		while (snakeX[0]>0 && snakeX[0] < BL - 1 && snakeY[0]>0 && snakeY[0] < BW - 1 && zisha())
		{
			locationX = snakeX[snakeLength - 1];	//定位前一次蛇的坐标
			locationY = snakeY[snakeLength - 1];
			if (det)
			{
				put_money();						//定位食物坐标的函数
			}
			if (_kbhit())
			{
				move = _getch();					//不可用getchar,getchar()需要按下回车确认才有效，getch()不需要按下回车也行；
			}										//getchar会从键盘缓存区寻找字符，拿够就弹出;而getch只会等待键盘的输入，并不会找键盘缓存区的字符
			snakeMove(move);
			eat_change();
			if (snakeLength == 20)					//胜利条件判断
			{
				situation = 1;
				output();							//输出当前游戏情况
				break;
			}
			//system("cls");
			output();								//输出当前游戏情况
			Sleep(snakespeed);						//45作为极速
		}
		system("cls");
		gameresult(situation);						//给出游戏结果
	} while (isagain());

	return 0;
}