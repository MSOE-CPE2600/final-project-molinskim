CC = gcc
CFLAGS = -Wall -lrt

PRODUCER = producer
CONSUMER = consumer

all: $(PRODUCER) $(CONSUMER)

$(PRODUCER): producer.c 
	$(CC) $(CFLAGS) -o $(PRODUCER) producer.c

$(CONSUMER): consumer.c 
	$(CC) $(CFLAGS) -o $(CONSUMER) consumer.c

clean:
	rm -f $(PRODUCER) $(CONSUMER)

.PHONY: all clean 