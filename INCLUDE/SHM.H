#ifndef SHM_H
#define SHM_H

void playSHM()
{
	cleardevice();
	double t=0, a=0.1, b, x;
	char str[80]="100*sin(t)", temp[80]="";
	gotoxy(14,24);
	cout<<"Enter Equation (Carefully): "; cin>>str;
	Bar c(350,200,10,10);
	Circle d(500,204,4);
	char sm[58];
	for(int i = 0; i< 57; i++)
		sm[i] = i%2+1;
	sm[57]='\0';
	bar(100,45,550,49);
	Spring s(150,50,5,20,100);
	settextstyle(0,0,1);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setcolor(LIGHTBLUE);
	outtextxy(99,37,sm);
	sm[0]=2;sm[1]=0;
	setcolor(RED);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(150,23,"Spring/Weight");
	outtextxy(325,23,"Wire/Block");
	outtextxy(500,23,"Pendulum");
	settextstyle(0,0,2);
	setlinestyle(0,1,1);
	while(1)
	{
	while(!kbhit())
	{
		setcolor(0);
		outtextxy(150,213+x,sm);                    //Smile
		rectangle(315+x/12,50,335-x/12,200+x);      //Wire
		line(150,200+x,150,207+x);                  //Smile'
		line(325,200+x,325,207+x);                  //Wire'
		line(500,50,500+x/5,200);                   //Pendulum
		strcpy(temp,str);
		replace(temp,"t",ftos(t));
		t+=a;
		x=exp(temp);
		setcolor(15);
		rectangle(315+x/12,50,335-x/12,200+x);      //Wire
		line(150,200+x,150,207+x);                  //Smile'
		line(325,200+x,325,207+x);                  //Wire'
		c.set(325,213+x);                           //Spring
		d.set(500+x/5,204);                         //Bob
		outtextxy(150,213+x,sm);                    //Smile
		s.sheight(200+x-50);                        //Spring
		line(500,50,500+x/5,200);                   //Pendulum
		delay(10);
	};
	char c = getch();
	if(c==' '||c=='p')getch();
	else if(c=='r'){playSHM();return;}
	else if(c==27)return;
	}
}
#endif