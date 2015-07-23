#include "palash/include.h"

void main()
{
	iGraph();
	cleardevice();
	settextstyle(4,0,5);
	setcolor(RED);
	settextjustify(1,1);
	outtextxy(320,25,"Welcome to THE Project By");
	settextstyle(4,0,7);
	setcolor(RED);
	drawImage("palash/profile.img",170,77);
	settextstyle(10,0,3);
	setcolor(LIGHTBLUE);
	delay(10);
	outtextxy(320,420,"Made Under Guidance of");
	drawImage("palash/teacher.img",550,350);
	clrKeyBuff();
	getch();
	char flag=1,flag2;
	while(flag)
	{
		flag2=1;
		cleardevice();
		clrKeyBuff();
		Button button[10];
		button[0].initialize(25, 15, 205, 155,0,0,"Graphs");
		button[1].initialize(230, 15, 410, 155,0,0,"Snakes");
		button[2].initialize(435, 15, 615, 155,0,0,"Pong");
		button[3].initialize(25, 170, 205, 310,0,0,"Calculator");
		button[5].initialize(435, 170, 615, 310,0,0,"Sorting");
		button[6].initialize(25, 325, 205, 465,0,0,"SHM");
		button[7].initialize(230, 325, 410, 465,0,0,"Field Lines");
		button[8].initialize(435, 325, 615, 465,0,0,"Tic Tac Toe");
		for(int i = 0; i<9;i++)
		{
			button[i].BorderColor[NORMAL] = BLUE-(i==4);
			button[i].BorderColor[FOCUS] = RED;
			button[i].FillType[NORMAL]=button[i].FillType[FOCUS]=1;
			button[i].FillColor[NORMAL]=button[i].FillColor[FOCUS]=i+6;
			button[i].TextColor[NORMAL]=button[i].TextColor[FOCUS]=RED;
			button[i].Font[NORMAL]=button[i].Font[FOCUS]=6;
			button[i].FontSize[NORMAL]=button[i].FontSize[FOCUS]=4;
			if(i!=4)button[i].make();
		}
		settextjustify(1,1);
		settextstyle(4,0,7);
		setcolor(LIGHTRED);
		outtextxy(320,190,"Welcome");
		settextstyle(3,0,3);
		outtextxy(320,240,"Choose One");
		settextstyle(0,0,1);
		setcolor(BLUE);
		outtextxy(320,280,"(ESC to Quit)");
		int curr =1;
		button[curr].gotFocus();
		while(flag&&flag2){
			int k = getch();
			switch(k)
			{
				case K_LEFT:
					button[curr].lostFocus();
					if(--curr==-1)curr=8;
					if(curr==4)curr=3;
					button[curr].gotFocus();
					break;
				case K_RIGHT:
					button[curr].lostFocus();
					if(++curr==9)curr=0;
					if(curr==4)curr=5;
					button[curr].gotFocus();
					break;
				case K_DOWN:
					button[curr].lostFocus();
					curr+=3;
					if(curr>8)curr-=9;
					if(curr==4)curr=7;
					button[curr].gotFocus();
					break;
				case K_UP:
					button[curr].lostFocus();
					curr-=3;
					if(curr<0)curr+=9;
					if(curr==4)curr=1;
					button[curr].gotFocus();
					break;
				case K_ENTER:
					switch(curr)
					{
						case 0:
							playGraph();
							break;
						case 1:
							playSnake();
							break;
						case 2:
							playPong("Player");
							break;
						case 3:
							playCalc();
							break;
						case 5:
							playSort();
							break;
						case 6:
							playSHM();
							break;
						case 7:
							playField();
							break;
						case 8:
							playTicTacToe();
							break;
					};
					flag2=0;
					break;
				case K_ESC:
					flag=0;
					break;
				default: break;
			};
		}
	}
	cleardevice();
	closegraph();
}
