#ifndef GRAPH_H
#define GRAPH_H

double graph(char fn[],char inv=0,double scaleX=1,double scaleY=1,double accuracy=1,double sDomain = 0,double  eDomain = 0,double width = 640,double height = 480,char minus =0,char color = WHITE, char m = 0)
{       clrKeyBuff();

	char temp[1000],fn2[1000]; temp[0] = '\0';
	strcpy(fn2,fn);
	replace(fn2,"x","(x)");
	double frequency = 1.0/accuracy;

	if((sDomain*scaleX)<-1*width/2)
		sDomain=-1*width/(2*scaleX);
	if((eDomain*scaleX)>width/2)
		eDomain=width/(scaleX*2);
	if(sDomain==eDomain&&sDomain==0)
	{
		sDomain=-1*width/(2*scaleX);
		eDomain=width/(2*scaleX);
	}
	double x = sDomain, y = 0, tvalx = 0, tvaly=0, tvalx1=0, tvaly1=0, sum=0;
	while(!kbhit()&&x<=eDomain)
	{
		strcpy(temp, fn2);
		char *xs = new char[20];
		sprintf(xs,"%lf",x);
		replace(temp, "x" , xs);
		delete xs;
		y = exp(temp);
		sum+=fabs(y*frequency);
		if(m)y*=-1;
		if(ftoi(x*scaleX+width/2)==tvalx && tvaly==ftoi(height/2-y*scaleY))
		{
			x+=frequency;
			continue;
		}
		else
		{
			tvalx1 = ftoi(x*scaleX+width/2);
			tvaly1 = ftoi(height/2-y*scaleY);
		}
		if(b_w(y*scaleY,-1*height/2-1,height/2+1)&&b_w(x*scaleX,-1*width/2-1,width/2+1)&&tvalx&&tvaly)
			if(!inv)
			{
				line(tvalx,tvaly,tvalx1,tvaly1);
				if(minus)
					line(tvalx,480-tvaly,tvalx1,480-tvaly1);
			}
			else
			{
				putpixel(ftoi(width/2+y*scaleY),ftoi(-x*scaleX+height/2),color);
				if(minus)
					putpixel(ftoi(width/2+y*scaleY),ftoi(x*scaleX+height/2),color);
			}
		x+=frequency;
		tvalx=tvalx1;tvaly=tvaly1;
	}
	temp[0] = '\0';
	clrKeyBuff();
	return sum;
}

int matherr(struct exception *a)
{
	a->retval=0;
	return 5;
}

int showGraph(char * fn)
{
	double scaleX =1, scaleY=1, accuracy=10, sDomain = 0, eDomain = 0;
	char minus =0, inverse =0, faa=1;
	int curr = 0;
	Button button[8];
	TextBox tbox[7];
	do{
	cleardevice();
	button[0].initialize(500, 315, 620, 330,0,0,"Scale - X");
	button[1].initialize(500, 335, 620, 350,0,0,"Scale - Y");
	button[2].initialize(500, 355, 620, 370,0,0,"Start Range");
	button[3].initialize(500, 375, 620, 390,0,0,"End Range");
	button[4].initialize(500, 395, 620, 410,0,0,"Accuracy");
	button[5].initialize(500, 415, 620, 430,0,0,"Invresion");
	button[6].initialize(500, 435, 620, 450,0,0,"Added (+-)");
	button[7].initialize(500, 455, 620, 470,0,0,"Function");

	for(int i = 0; i<8;i++)
	{
		button[i].BorderColor[NORMAL] = 0;
		button[i].BorderSize[FOCUS] = 1;
		button[i].make();
	}

	button[curr].gotFocus();

	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(490, 40, "Scale");
	outtextxy(490, 120, "Range");
	outtextxy(510, 60, "X-axis:");
	outtextxy(510, 80, "Y-axis:");
	outtextxy(510, 140, "Start :");
	outtextxy(510, 160, "End   :");
	outtextxy(495, 200, "Accuracy:");
	outtextxy(495, 230, "Inverse :");
	outtextxy(495, 260, "Add (+-):");
	outtextxy(490, 300, "Change");

	tbox[0].initialize(570,60,8,ftos(scaleX));
	tbox[1].initialize(570,80,8,ftos(scaleY));
	tbox[2].initialize(570,140,8,ftos(sDomain));
	tbox[3].initialize(570,160,8,ftos(eDomain));
	tbox[4].initialize(570,200,8,ftos(accuracy));
	tbox[5].initialize(570,230,8,itos(inverse));
	tbox[6].initialize(570,260,8,itos(minus));

	graph("0",0,1,1,1,0,0,480);
	graph("0",1,1,1,1,0,0,480);
	graph("239",1,1,1,1,0,0,480);
	double area = graph(fn,inverse,scaleX, scaleY, accuracy, sDomain, eDomain, 480, 480, minus);
	gotoxy(1,1); cout<<"Area under graph = "<<area;
	faa=1;
	while(faa)
	{
		int k = getch();
		switch(k)
		{
			case K_UP:
				button[curr].lostFocus();
				if(--curr==-1)
					curr=7;
				button[curr].gotFocus();
				break;
			case K_DOWN:
				button[curr].lostFocus();
				if(++curr==8)
					curr=0;
				button[curr].gotFocus();
				break;
			case K_ENTER:
				if(curr==7)
					return 1;
				tbox[curr].setText("");
				tbox[curr].focus();
				char t[100];
				strcpy(t, tbox[curr].text);
				switch(curr)
				{
					case 0:
						scaleX=stof(t);
						break;
					case 1:
						scaleY=stof(t);
						break;
					case 2:
						sDomain=stof(t);
						break;
					case 3:
						eDomain=stof(t);
						break;
					case 4:
						accuracy=stof(t);
						break;
					case 5:
						inverse=stoi(t);
						break;
					case 6:
						minus=stoi(t);
						break;
				}
				faa=0;break;
			case K_ESC:
				return 0;
		}
	}
	}while(1);
}

void playGraph()
{
	cleardevice();
	char fn[100];
	fn[0]=0;
	while(1)
	{
		gotoxy(10, 12);
		cout<<"Enter the Equation: ";
		cin>>fn;
		if(showGraph(fn))
			continue;
		else return;
	}
}
#endif