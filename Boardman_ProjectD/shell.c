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
			char tempCom[80];
			int i = 0;

			while (command[5 + i] != '\0' && command[5 + i] != '\r' && command[5 + i] != '\n' && (5 + i) < 80)
			{
				tempCom[i] = command[5 + i];
				i++;
			}
			tempCom[i] = '\0';

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
			char tempCom[80];
			int i = 0;

			while (command[5 + i] != '\0' && command[5 + i] != '\r' && command[5 + i] != '\n' && (5 + i) < 80)
			{
				tempCom[i] = command[5 + i];
				i++;
			}
			tempCom[i] = '\0';

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
		else if (command[0] == 'd' && command[1] == 'i' && command[2] == 'r')
		{
			char dir[512];
			int entry;
			int i;

			syscall(2, dir, 2);

			for (entry = 0; entry < 16; entry++)
			{
				if (dir[entry * 32] != '\0')
				{
					char filename[7];
					for (i = 0; i < 6; i++)
					{
						filename[i] = dir[entry * 32 + i];
					}
					filename[6] = '\0';

					syscall(0, filename);
					syscall(0, "\r\n");
				}
			}
		}
		else if (command[0] == 'd' && command[1] == 'e' && command[2] == 'l' && command[3] == ' ')
		{
			char tempCom[80];
			int i = 0;

			while (command[4 + i] != '\0' && command[4 + i] != '\r' && command[4 + i] != '\n' && (4 + i) < 80)
			{
				tempCom[i] = command[4 + i];
				i++;
			}
			tempCom[i] = '\0';

			syscall(7, tempCom);

		}
		else if (command[0] == 'c' && command[1] == 'o' && command[2] == 'p' && command[3] == 'y' && command[4] == ' ')
		{
			char tempCom[80];
			int i = 0;
			int sectorsRead;
			int j = 0;
			char copyFile[80];

			while (command[5 + i] != ' ' && command[5 + i] != '\0' && command[5 + i] != '\r' && command[5 + i] != '\n' && (5 + i) < 80)
			{
				tempCom[i] = command[5 + i];
				i++;
			}
			tempCom[i] = '\0';

			if (command[5 + i] == ' ')
			{
				i++;
			}

			while (command[5 + i + j] != '\0' && command[5 + i + j] != '\r' && command[5 + i + j] != '\n' && (5 + i + j) < 80)
			{
				copyFile[j] = command[5 + i + j];
				j++;
			}
			copyFile[j] = '\0';

			syscall(3, tempCom, buffer, &sectorsRead);
			if(sectorsRead>0)
			{
				syscall(8, buffer, copyFile, sectorsRead);
			}
			else
			{
				syscall(0, "File not found!\r\n");
			}
		}
		else if (command[0] == 'c' && command[1] == 'r' && command[2] == 'e' && command[3] == 'a' && command[4] == 't' && command[5] == 'e' && command[6] == ' ')
		{
			char tempCom[80];
			int i = 0;
			char contents[80];
			int sectorsRead = 0;

			while (command[7 + i] != ' ' && command[7 + i] != '\0' && command[7 + i] != '\r' && command[7 + i] != '\n' && (7 + i) < 80)
			{
				tempCom[i] = command[7 + i];
				i++;
			}
			tempCom[i] = '\0';

			syscall(0, tempCom);
			syscall(0, ":>");
			syscall(1, contents);

			syscall(8, contents, tempCom, 1);

		}
		else
		{
			syscall(0, "Bad Command!\r\n");
		}
	}
	syscall(5);
}
