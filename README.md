# mlm-tests
malamute stress test


The goal is to test how many messages  malamute can handle.

Producer is very simple. It just creates empty messages and publish them 
to the stream "test-stream" until 20 000 000 messages would be send.

Consumer is also very simple. It just reads messages from the stream 
"test-stream" and destroys them.

How to run:
    1. run malamute with basic configuration
    2. run consumer
    3. run producer
