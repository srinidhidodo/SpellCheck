# SpellCheck
Can find spelling errors in a text file, and has a word lookup feature. The dictionary may be customized by the user, who can add whatever words they like.

This program accepts a file name (.txt file) and performs spell check and word suggestions for incorrect words. Program also supports addition of new words to the dictionary.

Run exec.out you'll be shown a menu with options to perform the operations of the program. The file name entered should contain the extension and shouldn't be more than 30 characters including the file extension. 

Windows and Ubuntu

1. Copy the folder 'SpellCheck' onto your system.
2. Open the terminal.
3. Use the cd command to navigate to the directory containing the programs for the spell check.

Ubuntu

4. Type in the command make -f install.txt
5. ./exec.out to run the program

Windows

4. gcc -c node.h
5. gcc -c node.c
6. gcc -c spell_check.c
7. gcc -o exec.out node.o spell_check.o
8. exec.out to run the program

File Manifest :
node.h
node.c
english_wordlist1.txt
spell_check.c
install.txt
