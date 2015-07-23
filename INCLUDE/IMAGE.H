#ifndef IMAGE_H
#define IMAGE_H

void drawImage(char name[], int x=0, int y=0)
{
	ifstream a(name,ios::binary);
	int i=0,j=0,no,k,l;
	char n[2],c;
	while(!a.eof())
	{
		no=1;int f=0;
		while(a.read((char*)&n,1))
		{
			if(n[0]>=48&&n[0]<=57)
			{
				if(!f++)
					no=0;
				no=no*10+n[0]-48;
			}
			else break;
		}
		c=n[0];
		for(k = 0 ; k <= 16 ; k++)
		{
			if(k==16)
			{
				i++;
				j=0;
			}
			else if(c==(char(65+k)))
			{
				for(l=0;l<no;l++)
					putpixel(i+x, j+++y, k);
				break;
			}
		}
	}
}
#endif