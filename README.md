# mlm-tests
malamute stress test

Test1

The goal is to test how many messages  malamute can handle.

Producer is very simple. It just creates empty messages and publish them 
to the stream "test-stream" until 20 000 000 messages would be send.

Consumer is also very simple. It just reads messages from the stream 
"test-stream" and destroys them.

How to run:
    1. run malamute with basic configuration
    2. run consumer: ./consumer
    3. run producer: ./producer

Issue: after awhile (500 000 - 5 000 000) consumers stops receive 
messages at all. Nobody crashed.

Test2

The goal is to test how malamute can handle multiple fast producers.

Producer publish maximum 1 message per second into the stream. Consumer
reads all messages from the stream.

How to run:
    1. run malamute with basic configuration
    2. run consumer: ./consumer
    3. run Nth producer: ./producer N

Issue: consumer recieves apriximately 20-25 messages. And then 
receives nothing. Nobody crashed. Producers will continue to publish.
