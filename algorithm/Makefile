CC = gcc
TARGET = stack.out
OBJS = stack.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): stack.c
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
