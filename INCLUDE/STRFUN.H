#ifndef STRFUN_H
#define STRFUN_H

char b_w(double what, double min, double max)
{
	return what>min && what<max;
}

void iGraph()
{
	int gd = DETECT, gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
}

void clrKeyBuff(){ while(kbhit()) getch(); }

// Prototypes
	char * ctos(char);
	char * itos(int);
	char * ftos(float);
	long ftoi(double);
	long stoi(char *);
	double stof(char *);
	int ctoi(char);
	char * rstrcat(char *, char *);
	char * substr(char *, int , int);
	void replace(char *, char *, char *);
	char * remspace(char *, int, int);
	void trim(char *, int, int);
	int * getNos(char *, int);
	char scmp(char *, char *);
	void scpy(char *, char *);

long ftoi(double a)
{
	return fmod(a,1)<0.5?(a):(a+1);
}

inline char* ctos(char ch)
{
	char *str = new char[2];
	sprintf(str, "%c", ch);
	return str;
}

inline char* itos(int ch)
{
	char *str = new char[20];
	sprintf(str, "%i", ch);
	return str;
}

inline char* ftos(double ch)
{
	char *str = new char[20];
	sprintf(str, "%lf", ch);
	return str;
}

int ctoi(char ch)
{
	return ch-48;
}

long stoi(char *ch)
{
	long n = 0,j = 1, i;
	for(i = strlen(ch) - 1 ; i > 0 ; i--)
	{
		n += ctoi(ch[i]) * j;
		j *= 10;
	}
	if(ch[0] != '-' && ch[0]!='+')
	{
		n += ctoi(ch[0]) * j;
	}
	else if(ch[0] == '-')
	{
		n *= -1;
	}

	return n;
}

double stof(char * ch)
{
	if(!strcmp(ch,"pi")||!strcmp(ch,"PI"))
		return M_PI;
	long p =-1,len=strlen(ch);
	double n =0;
	for(long i = 0;i< len;i++)
		if(ch[i]=='.')
		{
			p=i;
			break;
		}
	if(p==-1)
	{	strcat(ch,".0");
		p=len++;len++;
	}
	else if(p==0)
	{
		ch = rstrcat("0",ch);
		len++;p++;
	}
	n += stoi(substr(ch, (ch[0]=='-'?1:0), p-1));
	double de = stoi(substr(ch,p+1,len-1))/pow(10,len-1-p);
	n += (n>=0?1:-1)*de;
	//cout<<ch[0];
	n *= (ch[0]=='-'?-1:1);
	return n;
}

char* rstrcat(char * str1, char* str2)
{
	char str3[100];
	strcpy(str3,str1);
	strcat(str3,str2);
	return str3;
}

char * substr(char* a,int start, int end)
{
	char n[500];
	for(int i=start;i<=end;i++)
		n[i-start]=a[i];
	n[end-start+1]='\0';
	return n;
}

void replace(char str[], char mat[], char rep[])
{
	int len = strlen(str),mlen = strlen(mat),rlen = strlen(rep);
	for(int i = 0; i<len;i++)
	{
		if(str[i]==mat[0])
			if(!strcmp(substr(str,i,i+mlen-1),mat))
			{
				char buff[200] = "\0";
				strcpy(buff,substr(str,i+mlen,len-1));
				str[i] = '\0';
				strcat(str,rep);
				strcat(str,buff);
				len+=rlen;
				i+=rlen-1;
			}
	}
}

char * remspace(char str[], int b = 1, int e = 1)
{
	trim(str, b, e);
	int n = strlen(str),c=0;
	for(int i = 0; i<n ;i++)
	{
		str[c++]=str[i];
		if(str[i]==' ')
		{
			for(;str[i]==' ';i++);
			i--;

		}
	}
	str[c]='\0';
	return str;
}

void trim(char str[], int b = 1, int e = 1)
{
	int n=strlen(str);
	if(b)
	{
		for(int i =0;str[i]==' ';i++);
		strcpy(str,substr(str,i,n));
	}
	if(e)
		for(n--;str[n]==' ';n--)
			str[n]='\0';
}

int * getNos(char str[], int n)
{
	int c=0,a[100], l = strlen(str);
	for(int i = 0; i < n ; i++)
		a[i] = 0;
	for(i=0; i<l&&c<n;i++)
	{
		if(str[i]==' ') c++;
		else a[c] = a[c]*10 + str[i] - 48;
	}
	return a;
}

char scmp(char str1[], char str2[])
{
	int l1 = strlen(str1), l2 =strlen(str2);
	for(int i = 0 ; i < (l1>l2?l1:l2); i++)
	{
		if(  (str1[i]=='?'&&str2[i]!=0) || (str1[i]!=0&&str2[i]=='?') )
			continue;
		else if(isalpha(str1[i])&&(tolower(str1[i])!=tolower(str2[i])))
			return 0;
		else if(str1[i]!=str2[i])
			return 0;
	}
	return 1;
}

void scpy(char str[], char src[])
{
	for(int i = 0, l = strlen(src); i <= l ; i++)
		str[i]=src[i];
}

#endif