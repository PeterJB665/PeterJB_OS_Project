//Peter J Boardman 2026

void printString(char*);
void readString(char*);
void readSector(char*, int);
int readFile(char*, char*, int*);
void executeProgram(char*);
void terminate();
void handleInterrupt21(int,int,int,int);


main(){
	//char buffer[13312]; /*this is the maximum size of a file*/
	//int sectorsRead;
	makeInterrupt21();
	//interrupt(0x21, 3, "messag", buffer, &sectorsRead); /*read the file into buffer*/
	//if(sectorsRead>0)
	//	interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
	//else
	//	interrupt(0x21,0,"messag not found\r\n",0,0); /*no sectors read? then print an error*/


	interrupt(0x21, 4, "shell",0,0);



	while(1); /*hang up*/
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

int readFile(char* fileName, char* buffer, int* sectorsRead)
{
	char dir[512];
	int fileEntry;
	int found = 0;
	int entry;
	int ch;
	int sectornumber;
	int j;

	readSector(dir,2);

	for(entry = 0; entry < 16; entry++)
	{
		fileEntry = entry*32;

		found = 0;

		for(ch = 0; ch <= 5; ch++)
		{
			if (fileName[ch] == dir[fileEntry+ch])
			{
				found++;
			}
			else
			{
				break;
			}
		}
		if (found == 6)
		{
			int count = 0;
			for (j = 0; j < 26; j++)
			{
				sectornumber=dir[fileEntry+6+j];
				if (sectornumber==0)
				{
					break;
				}
				readSector(buffer+512*j,sectornumber);
				count++;
			}
			*sectorsRead =  count;
			return count;
		}
	}
	*sectorsRead = 0;
	return 0;
}

void executeProgram(char* name)
{
	char buffer[13312];
	int sectorsRead;
	int i;

	interrupt(0x21, 3, name, buffer, &sectorsRead);
	if (sectorsRead > 0)
	{
		for (i = 0; i < sectorsRead*512; i++)
		{
			putInMemory(0x2000, i, buffer[i]);
		}
		launchProgram(0x2000);
	}
	else
	{
		interrupt(0x21,0,"program not found\r\n",0,0); /*no sectors read? then print an error*/

	}
}

void terminate()
{
	char shellname[6];
	shellname[0]='s';
	shellname[1]='h';
	shellname[2]='e';
	shellname[3]='l';
	shellname[4]='l';
	shellname[5]='\0';

	executeProgram(shellname);
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
	else if (ax == 3)
	{
		readFile(bx, cx, dx);
	}
	else if (ax == 4)
	{
		executeProgram(bx);
	}
	else if (ax == 5)
	{
		terminate();
	}
	else
	{
		printString("ERROR: Please choose from numbers 1, 2, 3, 4, and 5.");
	}
}
