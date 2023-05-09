CC = gcc
TARGET = bst.out
OBJS = bst.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): bst.c
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
