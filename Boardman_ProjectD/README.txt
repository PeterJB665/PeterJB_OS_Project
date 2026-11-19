1) What you did:
	I completed steps 1-6
2) How to Verify it:
	Step 1: See the writeSector function in my kernel.c
    Step 2: Load my disk into the simulator and type "dir" into it, it should list all the files I've inserted into the disk.
    Step 3: You can both check my deleteFile function in my kernel.c and also delete files directly in the simulator by typing "del" and then the filename.
    Step 4: See the writeFile function in my kernel.c
    Step 5: Load the disk, and you can copy a file by typing the command "copy", followed by a filename that already exists in the dir, followed by whatever you want to call the new copy of the file. Example: copy messag mess2
    Step 6: Load the disk, and create a text file by typing "create" followed by whatever you want to call the text file, after that, a new prompt will appear. Instead of SHELL:> it will be the new filename followed by :>. Here, you'll type the contents of your new text file and hit enter when you're done. Please note that you can only make it up to 80 characters long for now, I was not sure how big we were supposed to make it.
