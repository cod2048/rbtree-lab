CC = gcc
TARGET = test.out
OBJS = test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): test.c
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
