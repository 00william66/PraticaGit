all: writer reader

writer: writer.c
	gcc -Wall writer.c -o writer -lrt

reader: reader.c
	gcc -Wall reader.c -o reader -lrt

clean:
	rm -f reader writer