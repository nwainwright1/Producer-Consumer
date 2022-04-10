# Producer-Consumer
By: Nathaniel Wainwright

# Main Idea
This program simulates the producer consumer problem using semaphores and mutex. The semaphore is used to sync the producer and consumer in order to keep mutual exclusion.

# Compile and Run
In linux terminal:

$ gcc producer.c -pthread -lrt -o producer

$ gcc consumer.c -pthread -lrt -o consumer

$ ./producer & ./consumer &

# Output

![](https://github.com/nwainwright1/Images/blob/main/producer-consumer.png)

