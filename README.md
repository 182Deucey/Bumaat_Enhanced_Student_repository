# Student Registry Project

Hello sir mao ni enhanced version I apologize for passing late couldnt properly figure out how to do struct but i did my best and hopefully maka remmeber which is which sa defense 

## What it does

You can add students, see all of them, search by ID, find students with a
GPA above a certain number, and find students by their major. When you pick
"save and quit" it writes everything to a file called students.dat, and next
time you open the program it loads that file back in automatically.

## How to compile

Easiest way, just run:

```
make
```

or if you want to compile and run right away:

```
make run
```

If make doesn't work for some reason you can do it by hand:

```
gcc -c student_registry.c -o student_registry.o
gcc -c main.c -o main.o
gcc student_registry.o main.o -o student_registry
```

## How to run

```
./student_registry
```

## Why I made the struct the way I did

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

## Why I picked a text file instead of binary

I used a text file with | between each piece of info, like:

1001|Alice|CompSci|3.85|90

I picked text over binary mainly because I can literally open students.dat
in notepad or any text editor and see if it saved right, which made it way
easier for me to debug when something wasn't working. Binary probably
would've been faster or smaller but I couldn't have checked it as easily
and I don't really need speed for something this small anyway (max 10
students).

## Tests I ran

- Ran it with no students.dat file at all, it just said no file found and
  started empty, didn't crash.
- Added 2 students (Alice and Bob), saved and quit, then opened
  students.dat in a text editor to make sure the info looked right. It did.
- Reopened the program after that and it loaded both students back in and
  showed the right info when I displayed all.
- Searched for an ID that exists, got the right student back. Searched for
  one that doesn't exist, got the "no student with that id" message.
- Tried find by GPA with 3.5, only got Alice back since Bob's GPA is 3.45.
- Tried find by major with "Business", only Bob showed up and the total
  count was right (1).
- Kept adding students until I hit 10 (the max) and tried adding an 11th
  one, it correctly said the list is full instead of crashing or messing
  up the array.
- Tried adding a student with a multi-word name ("Ken Miles") and major
  ("Computer Science") after running into a bug where they got cut off
  and shifted into the wrong fields (see below) — after the fix, both
  came through correctly and saved to the file exactly as typed.

## Problems I ran into / things I had to think about

The biggest thing I had to figure out was strtok for reading the file back
in, since I hadn't really used it before. It splits the line by the | but
you have to keep calling it with NULL to get the next piece, which was
kinda confusing at first until I looked at the example in the notes.

Another thing was deciding when to actually save the file. I decided to
only save when you pick option 6 (save and quit), not after every single
add, since that's what the menu in the assignment shows. That does mean if
the program crashes before you save, you lose whatever you added, but I
figured that's fine since the assignment menu is built that way anyway.

I didn't add extra error checking beyond what's needed to get it working
(like checking scanf return values) since that wasn't really covered in
the lessons yet, but the basic file checks (making sure fopen doesn't
return NULL) are there since that was in the notes.

While testing, I ran into a bug where entering a name with a space in it
(like "Ken Miles") broke everything after it. It turned out scanf with
%s stops reading at the first space, so it only grabbed "Ken" and left
"Miles" sitting there to get read as the next field (major), which
pushed every field after that one over by one, and eventually a text
word landed where a number was expected and scanf just got stuck. I
fixed it by switching name and major to scanf(" %99[^\n]", ...) instead
of %s, which reads the whole line up to the newline instead of stopping
at the first space, so multi-word names and majors like "Computer
Science" work correctly now.
