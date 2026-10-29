//Peter J Boardman

main()
{
	char buffer[13312];
	char command[80];

	while(1)
	{
		syscall(0, "SHELL:>");
		syscall(1, command);
		if (command[0] == 't' && command[1] == 'y' && command[2] == 'p' && command[3] == 'e' && command[4] == ' ')
		{
			int sectorsRead;
			char tempCom[6];
			tempCom[0] = command[5];
			tempCom[1] = command[6];
			tempCom[2] = command[7];
			tempCom[3] = command[8];
			tempCom[4] = command[9];
			tempCom[5] = command[10];

			syscall(3, tempCom, buffer, &sectorsRead);
			if(sectorsRead>0)
			{
				syscall(0,buffer);
			}
			else
			{
				syscall(0,"File not found!\r\n");
			}
		}
		else if (command[0] == 'e' && command[1] == 'x' && command[2] == 'e' && command[3] == 'c' && command[4] == ' ')
		{
			int sectorsRead;
			char tempCom[6];
			tempCom[0] = command[5];
			tempCom[1] = command[6];
			tempCom[2] = command[7];
			tempCom[3] = command[8];
			tempCom[4] = command[9];
			tempCom[5] = command[10];

			syscall(3, tempCom, buffer, &sectorsRead);
			if(sectorsRead>0)
			{
				syscall(4,tempCom);
			}
			else
			{
				syscall(0,"File not found!\r\n");
			}
		}
		else
		{
			syscall(0, "Bad Command!\r\n");
		}
	}
	syscall(5);
}
