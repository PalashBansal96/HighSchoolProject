#ifndef SNAKE_H
#define SNAKE_H

const char UP =2, RIGHT=1, LEFT=-1, DOWN=-2;
struct snakes
{
	Coord pt;
	char dir;
	char ch;
};
class Snakes
{
	public:
		char POINT, SNAKE, WALL, EMPTY,B_OPEN,B_CLOSE,B_DL,B_DR,B_UL,B_UR,DRAW,ERASE,HEAD,TAIL;
		int pix, score, length,backcolor,level;
		Coord point;
		snakes snake[500];
		char key, del, direction, moving, speed, flag, screen[50][66];
		Label*l;

		Snakes();
		void play();
		void initialize();
		void putFigure(Coord, char, char=1, char=0);
		void updateSnake();
		void checkInput();
		void setScreen(int);
		void changeDir(int);
		void tab(int);
		void chooseSnake();
		void resetPoint();
		void printScreen();
		void lost(char);
		char exist(int,int);
		char exist(Coord);
};

void playSnake()
{
	Snakes snake;
	snake.chooseSnake();
	snake.play();
}

Snakes::Snakes()
{
	level = -1;
	HEAD = SNAKE = TAIL = 15;
	l = new Label(550,10,"");
	initialize();
}

void Snakes::changeDir(int dir)
{
	if(direction == dir)
		//speed++
		;
	else if(direction == -1*dir)
		//speed--
		;
	else
		direction = dir;
}

char Snakes::exist(int x,int y)
{
	return screen[y][x];
}

void Snakes::lost(char why)
{
	flag = why;
}

void Snakes::checkInput()
{
	if(kbhit())
	{
		key = getch();
		switch(key)
		{
			case K_UP:
				changeDir(UP);
				break;
			case K_DOWN:
				changeDir(DOWN);
				break;
			case K_LEFT:
				changeDir(LEFT);
				break;
			case K_RIGHT:
				changeDir(RIGHT);
				break;
			case 'p':
				getch();
			case 0:  checkInput();break;
			case K_ESC:
				flag = 21;
				break;
			default: break;
		};
	}
}

void Snakes::resetPoint()
{
	pt:
	point.X = random(60)+2;
	point.Y = random(45)+2;
	if(exist(point))
		goto pt;
	screen[point.Y][point.X]=POINT;
	putFigure(point,POINT);
}

char Snakes::exist(Coord coord)
{
	return screen[coord.Y][coord.X];
}

void Snakes::initialize()
{
	randomize();
	clrKeyBuff();
	snake[0].pt.X = 5;
	snake[0].pt.Y = 12;
	snake[0].dir = RIGHT;
	direction = RIGHT;
	length = 1;
	score = 1;
	speed = 1;
	del=0;
	flag = 0;
	pix = 10;
	backcolor=0;
	level++;
	resetPoint();
	B_OPEN = 5;
	B_CLOSE = 6;
	B_DL = 7;
	B_DR = 8;
	B_UL = 9;
	B_UR = 10;
	POINT = 20;
	DRAW = 1;
	ERASE = 0;
	WALL = -1;
	EMPTY = 0;
	DRAW = 1;
}

void Snakes::chooseSnake()
{
	cleardevice();
	settextstyle(4,0,5);
	setcolor(2);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(4,0,5);
	outtextxy(300,50,"Design Your Snake");
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(0,0,1);
	setcolor(4);
	for(int i=0;i<5;i++)
		outtextxy((11+i*10)*pix-5,-5+21*pix-1.5*pix,itos(i+1));
	Coord pos = {11,21};
	putFigure(pos,2); pos.X+=10;
	putFigure(pos,6,1,RIGHT); pos.X+=10;
	putFigure(pos,18);
	pos.X+=10;
	putFigure(pos,12,1,RIGHT); pos.X+=10;
	putFigure(pos,15);
	int a=0;
	gotoxy(20,17);
	cout<<"Enter Head Character: "; cin>>a;
	if(++a==3)a=5;
	else if(a==4)a=18;
	else if(a==5)a=12;
	else if(a==6)a=15;
	HEAD=a;
	gotoxy(20,18);
	cout<<"Enter Snake Character: ";
	cin>>a;
	if(++a==3)a=6;
	else if(a==4)a=18;
	else if(a==5)a=12;
	else if(a==6)a=15;
	gotoxy(20,19);
	cout<<"Enter Tail Character: ";
	SNAKE=a;
	cin>>a;
	if(++a==3)a=5;
	else if(a==4)a=18;
	else if(a==5)a=12;
	else if(a==6)a=15;
	TAIL=a;
	snake[0].ch = SNAKE;
	cleardevice();
}

void Snakes::setScreen(int value = 0)
{
	switch(value)
	{
		case 1:
			setScreen(0);
			for(int i = 1; i<65;i++)
			{
				screen[1][i] = WALL;
				screen[48][i] = WALL;
				if(i<49)
				{
					screen[i][1] = WALL;
					screen[i][64] = WALL;
				}
			}
			break;
		case 0:
			for(i = 0; i<50;i++)
				for(int j = 0;j<66;j++)
					screen[i][j] = EMPTY;
			break;
		case 2:
			setScreen(0);
			for(i = 1; i<65;i++)
			{
				if(!b_w(i,32,40))
					screen[22][i] = WALL;
				screen[26][i] = WALL;
				if(b_w(i,9,19))
					screen[9][i] = WALL;
				if(b_w(i,0,22))
				{
					screen[i][1] = WALL;
					screen[i][24] = WALL;
				}
				if(b_w(i,26,49))
					screen[i][24] = WALL;
			}
			break;
	}
}

void Snakes::printScreen()
{
	for(int i = 1;i<49;i++)
		for(int j = 1;j<65;j++)
			{
				Coord x = {j,i};
				putFigure(x,screen[i][j]);
			}
}

void Snakes::updateSnake()
{
	if(!del)
	{
		screen[snake[length-1].pt.Y][snake[length-1].pt.X] = EMPTY;
		screen[snake[length-2].pt.Y][snake[length-2].pt.X] = TAIL;
		putFigure(snake[length-1].pt, TAIL, ERASE,snake[length-1].dir);
		putFigure(snake[length-2].pt, snake[length-2].ch, ERASE,snake[length-2].dir);
		if(TAIL==B_OPEN)
			TAIL=B_CLOSE;
		else if(TAIL ==B_CLOSE)
			TAIL=B_OPEN;
		putFigure(snake[length-2].pt, TAIL,DRAW,snake[length-2].dir);
		snake[length-1].pt.X = snake[length-1].pt.Y = 0;
	}
	else
	{
		del--;
		length++;
	}
	for(int i = length-1;i>=0;i--)
			snake[i+1] = snake[i];
	if(abs(direction) == 1)
		snake[0].pt.X += direction;
	else
		snake[0].pt.Y -= direction/2;
	putFigure(snake[1].pt, HEAD, ERASE,snake[1].dir);
	if(b_w(SNAKE,4,11)&&snake[0].dir!=direction)
	{
		if((snake[0].dir == UP && direction == RIGHT)||(direction==DOWN&&snake[0].dir==LEFT))
			snake[1].ch = B_DR;
		else if((snake[0].dir == DOWN && direction == RIGHT)||(direction==UP&&snake[0].dir==LEFT))
			snake[1].ch = B_UR;
		else if((snake[1].dir == DOWN && direction == LEFT)||(direction==UP&&snake[0].dir==RIGHT))
			snake[1].ch = B_UL;
		else if((snake[0].dir == UP && direction == LEFT)||(direction==DOWN&&snake[0].dir==RIGHT))
			snake[1].ch= B_DL;
	}
	snake[0].ch = SNAKE;
	snake[0].dir = direction;
	if(SNAKE==B_OPEN)
		SNAKE=B_CLOSE;
	else if(SNAKE==B_CLOSE)
		SNAKE=B_OPEN;
	if(HEAD==B_OPEN)
		HEAD = B_CLOSE;
	else if(HEAD==B_CLOSE)
		HEAD=B_OPEN;
	if(snake[0].pt.X < 0)
		snake[0].pt.X = 65;
	else if(snake[0].pt.X > 65)
		snake[0].pt.X = 0;
	if(snake[0].pt.Y <0)
		snake[0].pt.Y = 48;
	else if(snake[0].pt.Y>49)
		snake[0].pt.Y = 0;
	char newhead = screen[snake[0].pt.Y][snake[0].pt.X];
	if(newhead ==WALL)
	{
		lost(WALL);
		return;
	}
	else if(b_w(newhead,0,20))
	{
		lost(SNAKE);
		return;
	}
	else if(newhead>=20)
	{
		del = 3;
		resetPoint();
		speed++;
		score++;
		l->setText(rstrcat("Score: ",itos(score-1)));
		putFigure(snake[0].pt,POINT,ERASE);
	}
	putFigure(snake[0].pt, HEAD,DRAW,snake[0].dir);
	putFigure(snake[1].pt, snake[1].ch,DRAW,snake[1].dir);
	screen[snake[1].pt.Y][snake[1].pt.X] = SNAKE;
	screen[snake[0].pt.Y][snake[0].pt.X] = HEAD;
}

void Snakes::play()
{
	initialize();
	cleardevice();
	clrKeyBuff();
	setScreen(level-1);
	printScreen();
	resetPoint();
	del=3;
	l->setText("Score: 0");
	flag=0;
	checkInput();
	while(!flag)
	{
		if(score%6==0)
		{
			resetPoint();
			score++;
		}
		updateSnake();
		if(speed<11)
		       delay(100-6*speed);
		else
			{play();break;};
		checkInput();
	}
	score = score + 10*(level-1) - 1;
}

void Snakes::putFigure(Coord coord, char character, char type, char dir)
{
	int ox=-5,oy=-5;
	switch(character)
	{
		case -1:     //WALL 1
			setfillstyle(1,1);
			bar(coord.X*pix-pix/2+ox,coord.Y*pix-pix/2+oy,coord.X*pix+pix/2+ox,coord.Y*pix+pix/2+oy);
			break;
		case -2:     //WALL 2
			break;
		case 20:     //POINT 1
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(4);
			settextjustify(CENTER_TEXT,CENTER_TEXT);
			settextstyle(0,0,1);
			outtextxy(coord.X*pix+ox,oy+ coord.Y*pix, ctos((char)1));
			break;
		case 18:     //x Part
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(3);
			settextjustify(CENTER_TEXT,CENTER_TEXT);
			settextstyle(0,0,1);
			outtextxy(coord.X*pix+ox,oy+ coord.Y*pix, ctos('x'));
			break;
		case 2:      //PART 1
			if(type==ERASE)
			{
				setcolor(backcolor);
				setfillstyle(1,backcolor);
			}
			else
			{
				int c=random(13)+1;
				setcolor(c);
				setfillstyle(1,c);
			}
			pieslice(coord.X*pix+ox, coord.Y*pix+oy, 0, 360, (pix)/2);
			break;
		case 5:
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(15);
			settextjustify(CENTER_TEXT,CENTER_TEXT);
			setusercharsize(1,2,1,2);
			if(dir%2)
				settextstyle(1,1,0);
			else
				settextstyle(1,0,0);
			outtextxy(ox+coord.X*pix,oy+coord.Y*pix,"(");
			break;
		case 6:
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(15);
			settextjustify(CENTER_TEXT,CENTER_TEXT);
			setusercharsize(1,2,1,2);
			if(dir%2)
				settextstyle(1,1,0);
			else
				settextstyle(1,0,0);
			outtextxy(ox+coord.X*pix,oy+coord.Y*pix,")");
			break;
		case 9: //B_DL
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(15);
			arc(coord.X*pix-pix/2+ox, oy+coord.Y*pix-pix/2, 270,360,pix/2);
			break;
		case 10: //B_DR
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(15);
			arc(coord.X*pix+pix/2+ox,oy+ coord.Y*pix-pix/2, 180,270,pix/2);
			break;
		case 7: //B_UL
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(15);
			arc(coord.X*pix-pix/2+ox,oy+ coord.Y*pix+pix/2, 0,90,pix/2);
			break;
		case 8: //B_UR
			if(type==ERASE)
				setcolor(backcolor);
			else
				setcolor(15);
			arc(coord.X*pix+pix/2+ox,oy+ coord.Y*pix+pix/2, 90,180,pix/2);
			break;
		case 12: //OPEN MOUTH
			setcolor(0);
			if(type == ERASE)
				setfillstyle(1,0);
			else
				setfillstyle(1,15);
			int s1=0,e1=0,s2=0,e2=0;
			if(dir==LEFT)
			{s1=180+20;e1=360;
			s2=0;e2=180-20;}
			else if(dir==RIGHT)
			{s1=0+20;e1=360-20;s2=e2=0;}
			else if(dir==UP)
			{s1=90+20;e1=360;s2=0;e2=90-20;}
			else if(dir==DOWN)
			{s1=0;e1=270-20;s1=270+20;e2=360;}
			pieslice(coord.X*pix+ox,coord.Y*pix+oy,s1,e1,pix/2+1);
			pieslice(coord.X*pix+ox,coord.Y*pix+oy,s2,e2,pix/2+1);
			break;
		case 15:
			if(type==ERASE)
				setfillstyle(1,0);
			else
				setfillstyle(1,2);
			bar(coord.X*pix-pix/2+ox+1,coord.Y*pix-pix/2+oy+1,coord.X*pix+pix/2+ox-1,coord.Y*pix+pix/2-1+oy);
			break;
		default:
			break;
	}
}
#endif