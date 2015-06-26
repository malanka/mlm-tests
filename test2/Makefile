all: consumer producer

consumer: consumer.cc 
	g++ -std=c++11 consumer.cc -ggdb -lmlm -lczmq -o consumer

producer: producer.cc 
	g++ -std=c++11 producer.cc -ggdb -lmlm -lczmq -o producer

clean:
	rm consumer producer
