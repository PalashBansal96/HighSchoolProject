#ifndef PONG_H
#define PONG_H

class Pong
{
	private:
		int BallRadius , ForeColor , BackColor , Key , TempX , TempY[3] , Score[2];
		float PaddleSpeed[2];
		char Flag , Temp , PositionChanged[2];
		char YES, NO, PLAYER, CPU, BALL;
		Coord PaddleSize , BallSpeed , Origin , ScreenSize , Position[3];

		void initVariables();
		void initGame();
		void updatePosition(int);
		void reInitGame();
		void drawFig(char, int, int, int);
		Label* PlayerScore;
		Label* CPUScore;
		char* CPUString;
		char* PlayerString;

	public:
		int Play(char*, int, int, int);
};

void playPong(char name[])
{
	Pong pong;
	pong.Play(name,5,RED, LIGHTGREEN);
}

int Pong::Play(char* Name, int HighScore, int FColor = 15, int BColor = 0)
{
	randomize();
	ForeColor = FColor;
	BackColor = BColor;
	PlayerString = new char[100];
	CPUString = new char[100];
	PlayerScore = new Label ( 20 , 10 , "" , 0 , 2 , ForeColor , BackColor);
	CPUScore = new Label( 400 , 10 , "" , 0 , 2 , ForeColor , BackColor);
	strcpy(PlayerString, Name);
	strcat(PlayerString , "'s score: " );
	strcpy(CPUString,"CPU's score: ");

	initVariables();
	initGame();

	while(Flag)
	{
		PositionChanged[PLAYER]=PositionChanged[CPU]=NO;
		if(kbhit())
		{
			do
			{
				Key=getch();
				switch(Key)
				{
					case K_UP:
						PaddleSpeed[PLAYER]+=1.2;
						PositionChanged[PLAYER]=1;
						break;
					case K_DOWN:
						PaddleSpeed[PLAYER]+=1.2;
						PositionChanged[PLAYER]=2;
						break;
					case K_ESC:
						return 0;
					default:
						continue;
				};
				break;
			}while(1);
		}
		Position[BALL].X += BallSpeed.X;
		Position[BALL].Y += BallSpeed.Y;

		PaddleSpeed[CPU] = random(3) + 2;

		if(PaddleSpeed[PLAYER] >= 5)
		{
			if(PositionChanged[PLAYER] == 1)
				Position[PLAYER].Y -= PaddleSpeed[PLAYER];
			else if(PositionChanged[PLAYER] == 2)
				Position[PLAYER].Y += PaddleSpeed[PLAYER];
			if(PositionChanged[PLAYER])
			{
				PaddleSpeed[PLAYER] -= 0.2;
				PositionChanged[PLAYER] = YES;
			}
			else
				PaddleSpeed[PLAYER]--;
		}

		if ( Position[PLAYER].Y <= Origin.Y + PaddleSize.Y / 2 && PositionChanged[PLAYER])
		{
			Position[PLAYER].Y = Origin.Y + PaddleSize.Y / 2 + 2;
		}
		else if ( Position[PLAYER].Y >= Origin.Y + ScreenSize.Y - PaddleSize.Y / 2 && PositionChanged[PLAYER] )
		{
			Position[PLAYER].Y = Origin.Y + ScreenSize.Y - PaddleSize.Y / 2 - 2;
		}

		if ( Position[BALL].X <= Origin.X + BallRadius )
		{
			Position[BALL].X = Origin.X + BallRadius;
			BallSpeed.X *= -1;
			Score[CPU]++;
			getch();
			if ( Score[CPU] == HighScore )
				return CPU;
			reInitGame();
		}
		else if ( Position[BALL].X >= Origin.X + ScreenSize.X - BallRadius )
		{
			Position[BALL].X = Origin.X + ScreenSize.X - BallRadius;
			BallSpeed.X *= -1;
			Score[PLAYER]++;
			getch();
			if ( Score[PLAYER] == HighScore )
				return PLAYER;
			reInitGame();
		}

		if ( Position[BALL].Y <= Origin.Y + BallRadius )
		{
			Position[BALL].Y = Origin.Y + BallRadius;
			BallSpeed.Y *= -1;
		}
		else if ( Position[BALL].Y >= Origin.Y + ScreenSize.Y - BallRadius )
		{
			Position[BALL].Y = Origin.Y + ScreenSize.Y - BallRadius;
			BallSpeed.Y *= -1;
		}

		if ( BallSpeed.X > 0)
		{	if ( Position[CPU].Y < Position[BALL].Y - 10 )
			{
				Position[CPU].Y += PaddleSpeed[CPU];
				PositionChanged[CPU] = YES;
			}
			else if ( Position[CPU].Y > Position[BALL].Y + 10 )
			{
				Position[CPU].Y -= PaddleSpeed[CPU];
				PositionChanged[CPU] = YES;
			}
		}
		else if( Position[CPU].Y >= Origin.Y + ScreenSize.Y / 2 + 10)
		{
			Position[CPU].Y -= PaddleSpeed[CPU];
			PositionChanged[CPU] = YES;
		}
		else if( Position[CPU].Y <= Origin.Y + ScreenSize.Y / 2 - 10)
		{
			Position[CPU].Y += PaddleSpeed[CPU];
			PositionChanged[CPU] = YES;
		}
		if (
			Position[BALL].X <= Position[PLAYER].X + PaddleSize.X / 2 + BallRadius &&
			Position[BALL].Y >= Position[PLAYER].Y - PaddleSize.Y / 2 &&
			Position[BALL].Y <= Position[PLAYER].Y + PaddleSize.Y / 2
		   )
		{
			if ( BallSpeed.X < 0 )
			{
				BallSpeed.X *= -1;
				Position[BALL].X = Position[PLAYER].X + PaddleSize.X / 2 + BallRadius + 2;
				BallSpeed.Y = 5 * ( ( Position[BALL].Y - Position[PLAYER].Y ) / 25.0 ) +
						(
						 ( Position[BALL].Y > Position[PLAYER].Y ) ? 4 * PositionChanged[PLAYER] : -4 * PositionChanged[PLAYER]
						);
			}
		}
		else if (
				Position[BALL].X >= Position[CPU].X - PaddleSize.X / 2 - BallRadius &&
				Position[BALL].Y >= Position[CPU].Y-PaddleSize.Y/2 &&
				Position[BALL].Y <= Position[CPU].Y+PaddleSize.Y/2
			)
		{
			if( BallSpeed.X > 0 )
			{
				BallSpeed.X *= -1;
				Position[BALL].X = Position[CPU].X - PaddleSize.X / 2 - BallRadius - 2;
				BallSpeed.Y = 5 * ( ( Position[BALL].Y-Position[CPU].Y ) / 25.0 ) +
						(
						 ( Position[BALL].Y >= Position[CPU].Y ) ? 2 * PositionChanged[CPU] : -2 * PositionChanged[CPU]
						);
			}
		}

		if ( Position[CPU].Y <= Origin.Y + PaddleSize.Y / 2 && PositionChanged[CPU])
		{
			Position[CPU].Y = Origin.Y + PaddleSize.Y / 2 + 2;
		}
		else if ( Position[CPU].Y >= Origin.Y + ScreenSize.Y - PaddleSize.Y / 2 && PositionChanged[CPU] )
		{
			Position[CPU].Y = Origin.Y + ScreenSize.Y - PaddleSize.Y / 2 - 2;
		}

		updatePosition(BackColor);
		TempX=Position[BALL].X;TempY[2]=Position[BALL].Y;TempY[1]=Position[CPU].Y;
		TempY[0]=Position[PLAYER].Y;
		updatePosition(ForeColor);

		delay(15);
	}
	getch();
	delete PlayerScore; delete CPUScore;
	return PLAYER;
}
void Pong::updatePosition(int Color)
{
	if(Temp)
		cleardevice();

	drawFig(BALL,TempX,TempY[BALL],Color);

	if(PositionChanged[CPU])
		drawFig(CPU,Position[CPU].X,TempY[CPU],Color);
	if(PositionChanged[PLAYER])
		drawFig(PLAYER,Position[PLAYER].X,TempY[PLAYER],Color);

	if(Color!=BackColor)
		rectangle(Origin.X , Origin.Y ,
			Origin.X + ScreenSize.X , Origin.Y + ScreenSize.Y );
}
void Pong::drawFig(char Fig,int x, int y,int Color)
{
	setcolor(Color);
	setfillstyle(SOLID_FILL,Color);
	if(Fig==BALL)
	{
		settextstyle(0,0,2);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		//char* sm = new char[2];
		//sprintf(sm,"%c",1);
		outtextxy(x,y,ctos(1));
	}
	else
		bar( x - PaddleSize.X / 2 , y - PaddleSize.Y / 2 ,
			x + PaddleSize.X / 2 , y + PaddleSize.Y / 2 );
}
void Pong::initVariables()
{
	PLAYER = 0;
	CPU = 1;
	BALL = 2;
	YES = 1;
	NO = 0;
	PaddleSize.X = 10;
	PaddleSize.Y = 50;
	BallSpeed.X = -2;
	BallSpeed.Y = 2;
	BallRadius = textwidth(ctos(1))/2;
	Key = 0;
	PaddleSpeed[PLAYER] = 5;
	PaddleSpeed[CPU] = 5;
	TempX = 0;
	Score[PLAYER] = 0;
	Score[CPU] = 0;
	Flag = 1;
	Temp = 0;
	Origin.X = 45;
	Origin.Y = 40;
	ScreenSize.X = 550;
	ScreenSize.Y = 400;
}
void Pong::initGame()
{
	clrKeyBuff();

	cleardevice();

	setfillstyle( 1 , BackColor);
	floodfill( 0 , 0 , ForeColor);

	Position[PLAYER].X = Origin.X + 20 ;
	Position[PLAYER].Y = Origin.Y + 200;
	Position[CPU].X = Origin.X + ScreenSize.X - 20;
	Position[CPU].Y = Origin.Y + ScreenSize.Y - 200;
	Position[BALL].X = Origin.X + 275;
	Position[BALL].Y = Origin.X + 200;

	PlayerScore->setText(rstrcat(PlayerString,itos(Score[PLAYER])));
	CPUScore->setText(rstrcat(CPUString,itos(Score[CPU])));

	TempX = Position[BALL].X;

	TempY[PLAYER] = Position[PLAYER].Y;
	TempY[CPU] = Position[CPU].Y;
	TempY[BALL]= Position[BALL].Y;

	PositionChanged[PLAYER]=PositionChanged[CPU]=YES;

	updatePosition(ForeColor);
	getch();
}
void Pong::reInitGame()
{
	initGame();
}

#endif
