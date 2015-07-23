#ifndef FIG_H
#define FIG_H

class Circle
{
	int x, y, r, c, bc;
	public:
		Circle(int x1, int y1, int rad = 1, int col = 15, int bcol = 0)
		{
			x =x1; y=y1; r=rad;c=col;bc=bcol;

		}
		void make()
		{
			setcolor(c);
			circle(x,y,r);
		}
		void erase()
		{
			setcolor(bc);
			circle(x,y,r);
		}
		void set(int x1, int y1)
		{
			erase();
			x=x1;y=y1;
			make();
		}

};

class Rectangle
{
	int x, y, l, h, c, bc;
	public:
		Rectangle(int x1, int y1, int hi = 1, int le = 1 , int col = 15, int bcol = 0)
		{
			x =x1; y=y1; h=hi;l=le;c=col;bc=bcol;

		}
		void make()
		{
			setcolor(c);
			rectangle(x-l/2,y-h/2,x+l/2, y+h/2);
		}
		void erase()
		{
			setcolor(bc);
			rectangle(x-l/2,y-h/2,x+l/2, y+h/2);
		}
		void set(int x1, int y1)
		{
			erase();
			x=x1;y=y1;
			make();
		}

};

class Bar
{
	int x, y, l, h, c, bc;
	public:
		Bar(int x1, int y1, int hi = 1, int le = 1 , int col = 15, int bcol = 0)
		{
			x =x1; y=y1; h=hi;l=le;c=col;bc=bcol;

		}
		void make()
		{
			setfillstyle(1,c);
			bar(x-l/2,y-h/2,x+l/2, y+h/2);
		}
		void erase()
		{
			setfillstyle(1,bc);
			bar(x-l/2,y-h/2,x+l/2, y+h/2);
		}
		void set(int x1, int y1)
		{
			erase();
			x=x1;y=y1;
			make();
		}

};

class Spring
{
	int x,y,r,ring,h;
	public:
		Spring(int x1, int y1, int r1, int ri, int h1)
		{
			x=x1;y=y1;r=r1;ring=ri;h=h1;
		}
		void make()
		{
			setcolor(15);
			for(int i = y; i<y+h ; i+=h/ring)
				circle(x,i,r);
		}
		void erase()
		{
			setcolor(0);
			for(int i = y; i<y+h ; i+=h/ring)
				circle(x,i,r);
		}
		void sheight(int h1)
		{
			erase();
			h=h1;
			make();
		}
};
#endif