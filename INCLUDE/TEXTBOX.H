#ifndef TEXTBOX_H
#define TEXTBOX_H

class TextBox
{

public:
	int len, sx , sy, w , h, key, bcolor, fcolor, i, endtype;
	char text[100], ch, flag, retend, retbksp;

	void initialize(int ux=1,int uy=1,int l=50,char t[] = "",int fc=15, int bc=0)
	{
		len = l;
		key = -1;
		retbksp=0;
		sx = ux;
		sy = uy;
		flag = 1;
		i = 0;
		retend = 0;
		strcpy(text,t);
		bcolor = bc;
		endtype = 0;
		fcolor = fc;
		w = textwidth(" ");
		h = textheight(" ");
		settextjustify(LEFT_TEXT, TOP_TEXT);
		outtextxy(sx,sy,text);
	}

	char * focus()
	{
		moveto(sx + i*w, sy);
		setcolor(fcolor);
		endtype = 0;
		while(flag)
		{
			if(i==len&&retend)
			{
				endtype=1;
				break;
			}
			ch = getch();
			switch(ch)
			{
				case 0:
					key=1;
					break;
				case '\b':
					if(i != 0)
					{
						moveto(getx() - w, gety());
						setcolor(bcolor);
						outtext(ctos(text[i-1]));
						setcolor(fcolor);
						moveto(getx() - w, gety());
						text[--i]='\0';
						//outtextxy(sx, sy, text);
					}
					else if(retbksp)
						endtype = flag--;//=1
					break;
				case '\n':
				case '\r':
					endtype = 0;
					flag = 0;
					break;
				case K_LEFT:
					if(!key)
					{

					}
				case K_RIGHT:
					if(!key)
					{

					}
				default:
					if(i<len&&key)
					{
						text[i]=ch;
						text[i + 1]='\0';
						outtextxy(sx, sy, text);
						moveto(sx + (w * (++i)), sy);
					}
			};//End of Switch
		};//End of While
		if(key>=0)
		       key--;
		flag = 1;
		return text;
	} // End of focus()

	void setText(char t[])
	{
		settextjustify(LEFT_TEXT, TOP_TEXT);
		setcolor(bcolor);
		outtextxy(sx,sy,text);
		strcpy(text, t);
		setcolor(fcolor);
		outtextxy(sx,sy,text);
		i=strlen(text);
	}

}; //End of Class TextBox

#endif