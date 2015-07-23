#ifndef BUTTON_H
#define BUTTON_H

const char NORMAL = 0, FOCUS = 1;

struct Coord
{
	int X;
	int Y;
};

double mean(double x, double y)
{
	return (x + y) / 2;
}
const char
	FALSE = 0,
	false = 0,
	False = 0,
	TRUE = 1,
	true = 1,
	True = 1;

class Button
{
	public:
		Coord Start, End;
		int FillType[2], BorderType[2], TextColor[2], FillColor[2], TextAlign[2], ForeColor[2], BackColor[2], BorderColor[2], BorderSize[2], FontSize[2], Font[2];
		char * Caption;
		char Focus, eras;
		int BackgroundColor;

		void initialize(int StartX, int StartY, int EndX, int EndY, int BColor = 0 , char Make = FALSE , char * Caption = "", char er = TRUE) //, Property ForeColor = {15,15} , Property BackColor = {0,0} , Property BorderColor = {15,15} , Property BorderSize = {2,3} , Property FontSize = {1,2} , Property FontStyle = {1,1})
		{
			Start.X = StartX;
			Start.Y = StartY;
			End.X = EndX;
			End.Y = EndY;
			this->Caption = Caption;
			BackgroundColor = BColor;
			TextColor[NORMAL] = 15;
			TextColor[FOCUS] = 15;
			FillColor[NORMAL] = 0;
			FillColor[FOCUS] = 0;
			BorderColor[NORMAL] = 15;
			BorderColor[FOCUS] = 15;
			BorderSize[NORMAL] = 1;
			BorderSize[FOCUS] = 3;
			FontSize[NORMAL] = 1;
			FontSize[FOCUS] = 1;
			TextAlign[NORMAL] = 5;
			TextAlign[FOCUS] = 5;
			FillType[NORMAL] = 1;
			FillType[FOCUS] = 1;
			BorderType[NORMAL] = 0;
			BorderType[FOCUS] = 0;
			Font[NORMAL] = 0;
			Font[FOCUS] = 0;
			Focus = FALSE;
			setVariables();
			eras=er;
			if(Make)
			{
				make();
			}
		}
		void setVariables(){}
		void click(){}
		void make()
		{
			erase();
			setlinestyle(BorderType[Focus] , 0 , BorderSize[Focus]);
			setcolor(BorderColor[Focus]);
			setfillstyle(FillType[Focus] , FillColor[Focus]);
			bar(Start.X , Start.Y , End.X , End.Y);
			if(BorderSize[Focus])
				rectangle(Start.X , Start.Y , End.X , End.Y);
			fillPattern();
		}
		void fillPattern()
		{
			int xp = (TextAlign[Focus]-1) % 3, yp = (TextAlign[Focus]-1) / 3;
			int x = Start.X + xp*(End.X - Start.X)/2,
			    y = Start.Y + yp*(End.Y - Start.Y)/2;
			settextstyle(Font[Focus],0,FontSize[Focus]);
			yp=(yp-1)*-1+1;
			settextjustify(xp,yp);
			moveto(x,y+1);
			setcolor(TextColor[Focus]);
			outtext(Caption);
		}
		void erase()
		{
			if(eras)
			{setfillstyle(SOLID_FILL, BackgroundColor);
			setcolor(BackgroundColor);
			setlinestyle(SOLID_LINE, 0 , BorderSize[!Focus]);
			rectangle(Start.X, Start.Y, End.X, End.Y);
			bar3d(Start.X, Start.Y, End.X, End.Y,0,0);
			}
		}
		void gotFocus()
		{
			Focus = TRUE;
			make();
		}
		void lostFocus()
		{
			Focus = FALSE;
			make();
		}
};

#endif

/*

void main()
{
	iGraph();
	cleardevice();
	getch();          int curr=0;
	Button* b[3];
	b[0]=new Button(150,80,460,110,0,true,"Palash");
	b[1]=new Button(150,20,460,280,0,true,"Pal");
	b[2]=new Button(150,360,460,450,0,true,"ash");
	b[0]->gotFocus();
	while(1)
	{
		if(kbhit())
		{
		int k = getch();
		switch(k)
		{
		case K_DOWN:
		b[curr]->lostFocus();
		if(++curr==3)curr=0;
		b[curr]->gotFocus();
		break;
		case K_UP:
		b[curr]->lostFocus();
		if(--curr==-1)curr=2;
		b[curr]->gotFocus();
		break;
		case K_ENTER:
			click(curr+1);
		case 27:
		goto end;
		}
		}
	}
	getch();
	end:
} */