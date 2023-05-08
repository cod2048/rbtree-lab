CC = gcc
TARGET = que.out
OBJS = que.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): que.c
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
