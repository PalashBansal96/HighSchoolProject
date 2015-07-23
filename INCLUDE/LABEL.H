#ifndef LABEL_H
#define LABEL_H

class Label
{
	char text[100];
	public:
	int x, y, font, color, fsize, bcolor, justx, justy, dir;

	Label(int x, int y, char t[] = " ", int f = 0,int fs =1,int fc =15,int bc=0,int jx = LEFT_TEXT, int jy = TOP_TEXT, int d=0)
	{
		this->x=x;this->y=y;font=f;strcpy(text,t);color=fc;fsize=fs;bcolor=bc;justx=jx;justy=jy;dir=d;
		this->setText(t);
	}
	void setText(char * t)
	{
		settextjustify(justx,justy);
		settextstyle(font,dir,fsize);
		setcolor(bcolor);
		outtextxy(x,y,text);
		strcpy(text,t);
		setcolor(color);
		outtextxy(x,y,text);
	}
	char * getText()
	{
		char t[100];
		strcpy(t,text);
		return t;
	}
	void changePos(int x, int y)
	{
		char * t = this->getText();
		this->setText("");
		this->x = x;
		this->y = y;
		setText(t);
	}
	int width()
	{
		return textwidth(text);
	}
	int height()
	{
		return textheight(text);
	}
};
#endif