#ifndef FIELD_H
#define FIELD_H

void playField()
{
	cleardevice();
	double cx[10], cy[10],r[10], q[10], th=0,e[10],fx,fy;
	double curx = 0, cury = 0,fo,k=9000000000,al,nx,ny,pi=3.14,frequency=1;
	long c[10],x,n,mf=1;
	gotoxy(1,1);
	cout<<"\n\tEnter no. of charges: "; cin>>n; cout<<'\n';
	for(int i = 0 ; i<n;i++)
	{
		cout<<"\t\tFor charge "<<i+1<<endl
		    <<"\t\t\tValue: "; cin>>q[i];
		cout<<"\t\t\tCoordinates (640x480): "; cin>>cx[i]>>cy[i];
		cout<<"\t\t\tLine Color (0-15): "; cin>>c[i];
	}
	cleardevice();
	setcolor(15);

	for(i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(fabs(q[i])<fabs(q[j]))
			{
				double t;
				t=q[i];q[i]=q[j];q[j]=t;
				t=cx[i];cx[i]=cx[j];cx[j]=t;
				t=c[i];c[i]=c[j];c[j]=t;
				t=cy[i];cy[i]=cy[j];cy[j]=t;
			}

	for(i = 0; i<n;i++)
	{
		if(q[i]>=0){setfillstyle(1,RED);setcolor(RED);}
		else {setfillstyle(1,GREEN);setcolor(GREEN);}
		pieslice(ftoi(cx[i]),ftoi(480-cy[i]),0,360,ftoi(fabs(q[i])*.9));
	}
	setcolor(0);
	for(i = 0 ; i<n;i++)
	{th=0;
	while(!kbhit()&&th<2*pi)
	{
		nx = cx[i] + fabs(q[i])*cos(th);
		ny = cy[i] + fabs(q[i])*sin(th);
		th+=2*pi/(fabs(q[i])*2);
		if(q[i]>0)
			mf=1;
		else
			mf=-1;
		while(!kbhit())
		{
			curx=nx;cury=ny;fx=fy=0;
			for(int j = 0; j<n;j++)
			{
				e[j]=k*mf*q[j]/(pow((pow(curx-cx[j],2)+pow(cury-cy[j],2)),1.5));
				fx+=e[j]*(curx-cx[j]);
				fy+=e[j]*(cury-cy[j]);
			}
			fo = sqrt(fx*fx+fy*fy);
			while(fo>1)fo/=2;
			al = atan2(fy,fx);
			nx = curx + fo*cos(al);
			ny = cury + fo*sin(al);
			int ck=(int(nx*100)==int(curx*100)&&int(ny*100)==int(cury*100));
			if(ck||(!((int)nx==(int)curx&&(int)ny==(int)cury)&&getpixel(nx,480-ny)))
				break;
			putpixel(nx,480-ny,c[i]);
		}
		if(kbhit())if(getch()==27)break;
	}
	}
	gotoxy(1,1);
	cout<<"Done";
	getch();
}
#endif