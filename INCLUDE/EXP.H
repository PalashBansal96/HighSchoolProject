#ifndef EXP_H
#define EXP_H

double solve(char e[]);

double exp(char e[])
{
	return solve(e);
}

char equals(char a,char b[])
{
	int f=0;
	for(int i = 0;i<strlen(b);i++)
	{
		if(b[i]==a)
		{f=1;break;}
	}
	return f;
}


long nt(char b[],int s)
{
	int l=0,len=strlen(b);
	if(b[s]=='(')
		l=1;
	for(long i = s+1;i<len;i++)
	{
		if(b[i]=='(')
			l++;
		else if(b[i]==')')
		{
			l--;
			if(l<0)
				break;
		}
		else if((b[i]=='+'||b[i]=='-')&&l==0)
			if(isdigit(b[i-1])||b[i-1]=='('||b[i-1]==')')
				break;

	}
	return i;
}

double solve(char e[])
{
	replace(e, " ", "");
	double sum=0;
	long next,len=strlen(e),i=0;char sgn;
	char sgns[]="+-/^*%";
	if(e[0]=='(')
	{
		int l=1;
		for(i = 1; i<len;i++)
			if(e[i]=='(')
				l++;
			else if(e[i]==')')
				if(!--l)
					break;
		sum = exp(substr(e,1,i-1));
	}
	else if(e[0]=='s')
	{
		if(!strcmp("sini",substr(e,0,3)))
		{
			next = nt(e,3);
			double s =exp(substr(e,4,next-1));
			sum = asin(s);
			i=next;
		}
		else if(!strcmp("sin",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			sum = sin(s);
			i=next;
		}
	}
	else if(e[0]=='c')
	{
		if(!strcmp("cosi",substr(e,0,3)))
		{
			next = nt(e,3);
			double s =exp(substr(e,4,next-1));
			sum = acos(s);
			i=next;
		}
		else if(!strcmp("cos",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			sum = cos(s);
			i=next;
		}
	}
	else if(e[0]=='t')
	{
		if(!strcmp("tani",substr(e,0,3)))
		{
			next = nt(e,3);
			double s =exp(substr(e,4,next-1));
			sum = atan(s);
			i=next;
		}
		else if(!strcmp("tan",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			sum = tan(s);
			i=next;
		}
	}
	else if(e[0]=='m')
	{
		if(!strcmp("mod",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			if(s>=0)
				sum = s;
			else
				sum = -1*s;
			i=next;
		}
	}
	else if(e[0]=='g')
	{
		if(!strcmp("gif",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			if(s>=0)
				sum = int(s);
			else
				sum = int(s)-1;
			i=next;
		}
	}
	else if(e[0]=='f')
	{
		if(!strcmp("frc",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			if(s>=0)
				sum = s - int(s);
			else
				sum = s - int(s) + 1;
			i=next;
		}
	}
	else if(e[0]=='l')
	{
		if(!strcmp("log",substr(e,0,2)))
		{
			next = nt(e,3);
			double s =exp(substr(e,3,next-1));
			sum = log10(s);
			i=next;
		}
		if(!strcmp("ln",substr(e,0,1)))
		{
			next = nt(e,2);
			double s =exp(substr(e,2,next-1));
			sum = log(s);
			i=next;
		}
	}
	else if(e[0]=='+')
	{
		sum = exp(substr(e,1,len-1));
		i=len;
	}
	else if(e[0]=='-')
	{
		next = nt(e,1);
		sum = -1*exp(substr(e,1,next-1));
		i = next-1;
	}
	else
	{
		for(i=1;i<len;i++)
			if(equals(e[i],sgns))
				break;
		sum = stof(substr(e,0,i-1));
		i=1;
	}
	for(;i<len;i++)
	{
		sgn=e[i];
		if(sgn=='+')
		{
			sum+=exp(substr(e,i+1,len-1));
			break;
		}
		else if(sgn=='-')
		{
			sum+=exp(substr(e,i,len-1));
			break;
		}
		else if(sgn=='*')
		{
			next = nt(e,i+1);
			sum*=exp(substr(e,i+1,next-1));
			i=next-1;
		}
		else if(sgn=='/')
		{
			next=nt(e,i+1);
			double d=exp(substr(e,i+1,next-1));
			if(d)
			sum/=d;
			else
				return 0;
			i=next-1;
		}
		else if(sgn=='^')
		{
			next = nt(e,i+1);
			sum = pow(sum,exp(substr(e,i+1,next-1)));
			//cout<<e<<endl;
			i=next-1;
		}
		else if(sgn=='%')
		{
			next = nt(e,i+1);
			double d= exp(substr(e,i+1,next-1));
			if(d)
				sum=fmod(sum,d);
			else
				return 0;
			i=next-1;
		}
	}
	return sum;
}

void playCalc()
{
	cleardevice();
	char e[100];
	gotoxy(10,12);
	cout<<"Enter Expression: ";
	cin>>e;
	gotoxy(10,13);
	cout<<"The Solution is "<<solve(e);
	getch();
}
#endif