#ifndef TIC_H
#define TIC_H

const char CIRCLE = -1;
const char CROSS = 1 ;
const char TEMP= 0 ;
const char PERMANENT= 1;
const char ERASE= -1;
const char ENTER = 5;

void drawit();

struct coord {
	int x;
	int y;
};

coord origin = {0, 0};
char curr = 0;
int box = 100;
char linewidth;
char tic[9];

void drawit()
{
	line(origin.x + box , origin.y ,
		origin.x + box , origin.y + box * 3);
	line(origin.x + box * 2 , origin.y ,
		origin.x + box * 2 , origin.y + box * 3);
	line(origin.x , origin.y + box ,
		origin.x + box * 3 , origin.y + box);
	line(origin.x , origin.y + box * 2 ,
		origin.x + box * 3 , origin.y + box * 2);
}

void drawFig(char cr, char fig, char type = PERMANENT)
{
	int color = getcolor();

	coord co = {cr%3+1,cr/3+1};

	if(type==TEMP)
		setcolor(RED);
	else if(type==PERMANENT)
		setcolor(WHITE);
	else if(type==ERASE)
	{
		if(tic[cr]) goto here;

		setcolor(BLACK);
	}

	if(fig == CROSS)
	{
		line(origin.x + box*(co.x + 0.2 -1), origin.y+box * (co.y + 0.2-1),
			origin.x + box*(co.x-0.2), origin.y+box*(co.y-0.2));
		line(origin.x + box*(co.x + 0.2 -1), origin.y+box * (co.y - 0.2),
			origin.x + box*(co.x-0.2), origin.y+box*(co.y+0.2-1));
	}
	else if(fig == CIRCLE)
	{
		circle(origin.x + box * (co.x + 0.5 - 1), origin.y + box * (co.y + 0.5 - 1) , 0.4 * box);
	}
	here:
	setcolor(color);
}
int getNo(int n)
{
	int x, o,nx=0,no=0,num=0;
	if(n<0)
	{
		o = n/CIRCLE;
		x = 0;
	}
	else
	{
		x = n/CROSS;
		o = 0;
	}

	for(int i = 0; i<9 ; i++)  //rows
	{
		if(tic[i] == CROSS)
			nx++;
		else if(tic[i] == CIRCLE)
			no++;
		if(!((i+1)%3))
		{
			if (nx == x && no == o)
				num++;
			nx=no=0;
		}
	}

	for(int j=0;j<3;j++)
	{
		for(i=j;i<9;i+=3)
		{
			if(tic[i]==CROSS)
				nx++;
			else if(tic[i]==CIRCLE)
				no++;
		}
		if(nx==x&&no==o)
			num++;
		nx=no=0;
	}

	for(i=0;i<9;i+=4)
	{
		if(tic[i] ==CROSS)
			nx++;
		else if(tic[i] ==CIRCLE)
			no++;
	}
	if(nx==x&&no==o)
		num++;
	nx=no=0;

	for(i=2;i<8;i+=2)
		if(tic[i]==CROSS)
			nx++;
		else if(tic[i]==CIRCLE)
			no++;
	if(nx==x&&no==o)
		num++;
	return num;
}
char checkWin()
{
	if(getNo(3*CIRCLE)) return CIRCLE;
	else if(getNo(3*CROSS)) return CROSS;
	else return 0;
}

char specialCases()
{
	return 0;
}

int getStateValue()
{
	if(getNo(3*CIRCLE))
		return 50;
	else if(specialCases())
		return -50;
	else
	{
		int x2 = getNo(2*CROSS),
		    x1 = getNo(CROSS),
		    o2 = getNo(2*CIRCLE),
		    o1 = getNo(CIRCLE);
		return 3*o2 + o1 - (3*x2 + x1);
	}
}

char flag=1;
char cfig=CROSS;
int key=0,moves=0;

void changePos(char k)
{
	if(k==ENTER)
	{
		tic[curr]=cfig;
		drawFig(curr,cfig,PERMANENT);
		cfig*=-1;
		k=10;
	}
	do{
	if(!checkWin()&&k!=10)
	{
		drawFig(curr,cfig,ERASE);
		if(abs(k)==1)
		{
			curr+=k;
		}
		else if(k==UP)
		{
			curr-=2+k/2;
		}
		else
		{
			curr+=2-k/2;
		}
		if(curr>=9)curr=curr-9;
		else if(curr<=-1)curr=9+curr;
		if(tic[curr])
			continue;
		drawFig(curr,cfig,TEMP);
	}
	break;
	}while(1);
}

void playTicTacToe()
{
	while(kbhit())
		getch();
	flag=1;
	origin.x = 150;
	origin.y = 75;
	curr = 0;
	box = 100;
	cfig=CROSS;
	key=0;
	moves=0;
	randomize();
	cleardevice();
	settextstyle(10,0,2);
	setcolor(LIGHTBLUE);
	outtextxy(100,40,"Tic Tac Toe");
	linewidth = 3;
	setlinestyle(0,0,linewidth);
	box += 4*linewidth;
	drawit();

	int CPUMove = random(2);

	for(int i =0;i<9;i++)
		tic[i]=0;

	while(flag)
	{
		if(CPUMove)  //CPU Move
		{
			int highvalue = -50, bestposition = 0;
			for(i = 0;i<9;i++)
			{
				if(!tic[i])
				{
					drawFig(i, CIRCLE, TEMP);
					tic[i] = CIRCLE;
					int statevalue = getStateValue();
					if(statevalue > highvalue)
					{
						highvalue = statevalue;
						bestposition = i;
					}
					else if(statevalue == highvalue)
						highvalue = (random(2))?statevalue:highvalue;
					delay(10);
					tic[i] = 0;
					drawFig(i, CIRCLE, ERASE);
				}
			}
			drawFig(bestposition, CIRCLE, PERMANENT);
			tic[bestposition] = CIRCLE;
			moves++;
		}

		if(checkWin()==CIRCLE)
		{
			outtextxy(380,420,"Computer wins"); flag=0;
		}
		else if(moves == 9)
		{
			outtextxy(380,420,"Its a Draw"); flag=0;
		}

		CPUMove = 1;
		int moved = 0;
		cfig = CROSS;
		changePos(RIGHT);
		cfig = CROSS;
		if(flag)
		do      //Player move
		{
			key = getch();
			switch(key)
			{
				case 'W':
				case 'w':
				case K_UP: changePos(UP);
					cfig=CROSS;
					break;
				case 'S':
				case 's':
				case K_DOWN: changePos(DOWN);
					cfig=CROSS;
					break;
				case 'D':
				case 'd':
				case K_RIGHT: changePos(RIGHT);
					cfig=CROSS;
					break;
				case 'A':
				case 'a':
				case K_LEFT: changePos(LEFT);
					cfig=CROSS;
					break;
				case K_ESC: flag=0;
					break;
				case K_SPACE:
				case K_ENTER: changePos(ENTER);
					moved = 1;
					break;
				default: continue;
			};
		}while(!moved);
		moves++;
		if(flag)
		{
		if(checkWin()==CROSS)
		{
			outtextxy(380,420,"Player wins");flag=0;
		}
		else if(moves == 9)
		{
			outtextxy(380,420,"Its a Draw"); flag=0;
		}
		}
	}
	getch();
}
#endif