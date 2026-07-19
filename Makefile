CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = student_registry
OBJS = student_registry.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

student_registry.o: student_registry.c student_registry.h
	$(CC) $(CFLAGS) -c student_registry.c -o student_registry.o

main.o: main.c student_registry.h
	$(CC) $(CFLAGS) -c main.c -o main.o

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) students.dat
