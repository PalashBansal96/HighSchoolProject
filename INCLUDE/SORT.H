#ifndef SORT_H
#define SORT_H

void draw(int a[])
{
	int w= 60, mf=50;
	setfillstyle(1,BLUE);
	settextjustify(CENTER_TEXT,BOTTOM_TEXT);
	setcolor(15);
	settextstyle(10,0,0);
	for(int i = 0; i < 9 ; i++)
	{
		bar(20+i*w+6, 480-10,20+i*w+w, 480-mf*a[i]);
		setusercharsize(w-6,40,mf*a[i]-10,40);
		outtextxy(20+i*w+(w+14)/2, 470, itos(a[i]));
	}
}

void Bubble(int a[])
{
	for(int i = 0 ; i< 9;i++)
		for(int j = 0;j<9-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				int x= a[j+1];
				a[j+1]=a[j];a[j]=x;
				cleardevice();
				draw(a);
				getch();
			}
		}
}

void Selection(int a[])
{
	for(int i = 0 ; i< 9;i++)
	{
		int low=a[i],pos=i;
		for(int j = i+1;j<9;j++)

			if(low>a[j])
			{
				low = a[j];
				pos=j;
			}
		int t = a[i];
		a[i]=a[pos];
		a[pos]=t;
		if(pos!=i)
		{cleardevice();
		draw(a);getch();}

	}
}

void Sequential(int a[])
{
	for(int i = 0 ; i< 9;i++)
		for(int j = i;j<9;j++)
		{
			if(a[j]<a[i])
			{
				int x=a[i];
				a[i]=a[j];a[j]=x;
				cleardevice();
				draw(a);getch();
			}
		}
}

void Insertion(int a[])
{
	for(int i = 1 ; i< 9;i++)
	{
		int t=a[i],j;
		for(j=i-1;j>=0;j--)
			if(a[j]>t)
			{
			a[j+1]=a[j];
			cleardevice();draw(a);
			getch();
			}
			else break;
		a[j+1]=t;
		cleardevice();
		draw(a);
		getch();
	}
}

void playSort()
{
	cleardevice();
	char flag = 1,flag2=1;
	while(flag)
	{
		flag2=1;
		cleardevice();
		clrKeyBuff();
		settextjustify(1,1);
		settextstyle(10,0,5);
		setcolor(LIGHTBLUE);
		outtextxy(320,25,"Sorting");

		Button button[4];
		button[0].initialize(25, 100, 615, 170,0,0,"Bubble");
		button[1].initialize(25, 200, 615, 270,0,0,"Sequential");
		button[2].initialize(25, 300, 615, 370,0,0,"Selection");
		button[3].initialize(25, 400, 615, 470,0,0,"Insertion");

		for(int i = 0; i<4;i++)
		{
			button[i].BorderColor[NORMAL] = WHITE;
			button[i].BorderColor[FOCUS] = RED;
			button[i].FillColor[NORMAL]=button[i].FillColor[FOCUS]=BLUE;
			button[i].TextColor[NORMAL]=button[i].TextColor[FOCUS]=RED;
			button[i].Font[NORMAL]=button[i].Font[FOCUS]=4;
			button[i].FontSize[NORMAL]=button[i].FontSize[FOCUS]=3;
			button[i].make();
		}
		int curr=0;
		button[curr].gotFocus();
		while(flag&&flag2){
			int k = getch();
			switch(k)
			{
				case K_UP:
					button[curr].lostFocus();
					if(--curr==-1)
						curr=3;
					button[curr].gotFocus();
					break;
				case K_DOWN:
					button[curr].lostFocus();
					if(++curr==4)
						curr=0;
					button[curr].gotFocus();
					break;
				case K_ENTER:
					int a[] = {2,5,1,7,3,6,9,4,8};
					cleardevice();
					draw(a);
					getch();
					switch(curr)
					{
						case 0:
							Bubble(a);
							break;
						case 1:
							Sequential(a);
							break;
						case 2:
							Selection(a);
							break;
						case 3:
							Insertion(a);
							break;
					};
					draw(a);
					getch();
					flag2=0;
					break;
				case K_ESC:
					flag=0;
					break;
				default: break;
			};
		}
	};
}
#endif