all: producer consumer

consumer: consumer.c
	gcc -Wall consumer.c -o consumer -lrt

producer: producer.c
	gcc -Wall producer.c -o producer -lrt

clean:
	rm -f consumer producer