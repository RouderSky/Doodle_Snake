#pragma warning( disable : 4996)
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>                   //use for kbhit
#include<time.h>                    //use for random number
#include <malloc.h>
#include<mmsystem.h>                //use for music
#pragma comment (lib,"winmm.lib")   //use for music


#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define BL 50
#define BW 25


//snake stepping: dy = 1(up),-1(down);dx = -1(left),1(right),0(no move)   
void snakeMove(char);
//put a food randomized on a blank cell
void put_money(void);
//out cells of the grid
void output(void);
//outs when gameover
void gameresult(int);
//eat food and change length
void eat_change(void);
//when it was killed by itself,return 0;otherwise return 1;
int zisha(void);
//locate cursor 
void gotoxy(int, int);		
//change color
void color(int);
//judge whether you play again 
int isagain(void);
//judge the speed of the snake
void judge_speed(int);

//define vars for snake ,notice name of vars in C
int snakeX[SNAKE_MAX_LENGTH];
int snakeY[SNAKE_MAX_LENGTH];
int snakeLength;

//position of food
struct
{
	int x;
	int y;               
}food;

//license of puting food 
int det;               

//save the last location of the snake tail        
int locationX,locationY;                       //注意：全局变量不可以在头文件中初始化，但要在头文件中声明；
											   //在函数外的声明都是全局声明，
//save the result of game					   //c中在一个文件中定义了全局变量后，在别的文件中使用时不用加上extern，直接再定义一遍就好了（但是这时不可以赋值）,这样就是声明了。
int situation;

//the speed of the snake
int snakespeed;

//the level of the snake
int level;

