# Student Registry Project

**Name:** Kiefer Rile B. Buma-at  
**Course:** BSIT (2nd Year)

Hello sir mao ni enhanced version I apologize for passing late couldnt properly figure out how to do struct but i did my best and hopefully maka remmeber which is which sa defense 

## What it does

You can add students, see all of them, search by ID, find students with a
GPA above a certain number, and find students by their major. When you pick
"save and quit" it writes everything to a file called students.dat, and next
time you open the program it loads that file back in automatically. *In this enhanced version, I also added input validation and safety checks so the program won't crash if the user types the wrong thing or if the save file gets messed up.*

## How to compile

Easiest way, just run:

```bash
make
or if you want to compile and run right away:
make run
If make doesn't work for some reason you can do it by hand:
gcc -c student_registry.c -o student_registry.o
gcc -c main.c -o main.o
gcc student_registry.o main.o -o student_registry
How to run
./student_registry
Why I made the struct the way I did
In Day 10 I had a bunch of separate arrays, like id[], name[][], major[][],
gpa[], credits[], and I had to keep them all in sync using the same index
number for one student, which honestly got kind of confusing. This time I
put everything into one struct called Student so all the info for one
person is together in one place. It made it a lot easier to think about
because now students[0] is literally just "student number 1" with all their
stuff attached, instead of me having to remember that id[0] and name[0] and
gpa[0] all belong to the same person.

I also split the code into a .h file and a .c file like the lesson showed,
so the header just has the struct and the list of functions, and the .c
file is where all the actual code is. main.c just calls the functions, it
doesn't need to know how they work inside.

Why I picked a text file instead of binary
I used a text file with | between each piece of info, like:

1001|Alice|CompSci|3.85|90

I picked text over binary mainly because I can literally open students.dat
in notepad or any text editor and see if it saved right, which made it way
easier for me to debug when something wasn't working. Binary probably
would've been faster or smaller but I couldn't have checked it as easily
and I don't really need speed for something this small anyway (max 10
students).

Tests I ran
Ran it with no students.dat file at all, it just said no file found and started empty, didn't crash.

Added 2 students (Alice and Bob), saved and quit, then opened students.dat in a text editor to make sure the info looked right. It did.

Reopened the program after that and it loaded both students back in and showed the right info when I displayed all.

Searched for an ID that exists, got the right student back. Searched for one that doesn't exist, got the "no student with that id" message.

Tried find by GPA with 3.5, only got Alice back since Bob's GPA is 3.45.

Tried find by major with "Business", only Bob showed up and the total count was right (1).

Kept adding students until I hit 10 (the max) and tried adding an 11th one, it correctly said the list is full instead of crashing or messing up the array.

Tried adding a student with a multi-word name ("Ken Miles") and major ("Computer Science") after running into a bug where they got cut off and shifted into the wrong fields (see below) — after the fix, both came through correctly and saved to the file exactly as typed.

[NEW] Tried adding a student with an ID that already exists. The program successfully caught the duplicate and blocked it.

[NEW] Typed letters (like "A") when the program asked for an ID or GPA. Instead of going into an infinite loop, the program cleared the buffer, printed an error, and went back to the menu safely.

[NEW] Purposely deleted some | symbols and data in the students.dat file. The program skipped the corrupted lines safely instead of crashing (Segmentation Fault).

Problems I ran into / things I had to think about
The most frustrating part was definitely figuring out strtok for reading the file back in. It splits the line by the |, but having to keep calling it with NULL to get the next piece felt so unintuitive at first until I stared at the examples long enough. Worse, I found out the hard way that if a line in the text file is blank or corrupted, strtok just throws a NULL and immediately crashes the whole program with a Segmentation Fault. So annoying. I had to go back and sprinkle if (token == NULL) continue; everywhere just to keep it from dying on bad data.

Then there was the scanf infinite loop nightmare. I originally didn't add error checking, but if you accidentally type a letter instead of a number for the ID or GPA, the program just completely loses its mind and loops forever. The letter just gets stuck in the input buffer! I was so confused why it was doing that. I finally fixed it by checking the return value of scanf and writing a clearBuffer() function just to eat the garbage input.

And don't even get me started on the spaces bug. I was testing it and typed "Ken Miles" for a name, and it literally broke every single input after it. It turns out %s in scanf stops reading at the very first space. So it took "Ken" for the name, shoved "Miles" into the major, and pushed everything else down one slot until it hit a number field and got stuck again. I had to scrap %s completely and use this weird syntax scanf(" %99[^\n]", ...) just to let people have spaces in their names. It limits the characters to prevent buffer overflows too, which is a nice bonus.

Deciding when to actually save the file was another thing. I stuck to just saving when you pick option 6 (save and quit) because that matches the assignment menu. It means if the program crashes before you save, you lose everything you added, which kinda sucks, but it is what it is.

Finally, I wasted a bunch of time writing my own custom checkSame function to compare strings character by character, only to realize later I was completely reinventing the wheel. I ended up deleting the whole thing and just using strcmp from <string.h>. Log (2:32am jul 20 2026)
