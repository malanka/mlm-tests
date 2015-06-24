all: consumer producer

consumer: consumer.cc 
	g++ consumer.cc -lmlm -lczmq -o consumer

producer: producer.cc 
	g++ -std=c++11 producer.cc -lmlm -lczmq -o producer

clean:
	rm consumer producer
