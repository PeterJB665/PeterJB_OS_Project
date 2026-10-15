void printString(char*);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int,int,int,int);

main(){
char line[80];
char buffer[512];

printString("Enter a line: ");
readString(line);
printString(line);

readSector(buffer, 30);
printString(buffer);

makeInterrupt21();
interrupt(0x21,0,"Enter a line:",0,0);
interrupt(0x21,1,line,0,0);
interrupt(0x21,0,line,0,0);

while(1);
}

void printString(char* chars)
{
	int i = 0;

	while (chars[i] != '\0')
	{
		char al = chars[i];
		char ah = 0xe;
		int ax = ah*256+al;
		interrupt(0x10,ax,0,0,0);
		i++;
	}
}

void readString(char* chars)
{
	int i = 0;
	char ch;


	while (1)
	{
		ch = (char)interrupt(0x16, 0x0000, 0,0,0);

		//checking for enter
		if (ch == 0x0d)
		{
			chars[i] = interrupt(0x10,0x0e00+0xa,0,0,0);
			chars[i+1] = interrupt(0x10,0x0e00+0x0,0,0,0);
			interrupt(0x10,0x0e00+0xd,0,0,0);
			break;
		}
		//checking for backspace
		else if (ch == 0x8)
		{
			if (i > 0)
			{
				i--;
				interrupt(0x10,0x0e00+0x08,0,0,0);
				interrupt(0x10,0x0e00+' ',0,0,0);
				interrupt(0x10,0x0e00+0x08,0,0,0);
			}
		}
		//checking for any other letter
		else
		{
			chars[i] = ch;
			i++;
			interrupt(0x10,0xe00+ch,0,0,0);
		}
	}
}


void readSector(char* buffer, int sector)
{
	int ah = 2;
	int al = 1;
	char* bx = buffer;
	int ch = 0;
	int cl = sector+1;
	int dh = 0;
	int dl = 0x80;

	int ax = ah * 256 + al;
	int cx = ch * 256 + cl;
	int dx = dh * 256 + dl;

	interrupt(0x13,ax,bx,cx,dx);
}

void handleInterrupt21(int ax, char* bx, int cx, int dx)
{
	if (ax == 0)
	{
		printString(bx);
	}
	else if (ax == 1)
	{
		readString(bx);
	}
	else if (ax == 2)
	{
		readSector(bx, cx);
	}
	else
	{
		printString("ERROR: Please choose from numbers 1, 2, and 3");
	}
}

