# Dining Philosophers Problem

This is a C++ implementation of the Dining Philosophers problem using mutexes to ensure that the philosophers can eat without causing a deadlock. The problem involves five philosophers sitting at a round dining table, and they must alternate between thinking and eating using shared forks.


### Description

The program simulates the actions of each philosopher, including thinking, picking up forks, eating, and returning to thinking.
Philosophers use mutexes to prevent concurrent access to forks, ensuring that only one philosopher can pick up a fork at a time.
If a philosopher cannot pick up both forks, they release any forks they have picked up and return to thinking.


### Synchronization

Mutexes are used to synchronize the access to forks and to ensure that philosophers take turns in picking up forks.
A separate mutex is used for synchronized printing to prevent overlapping console output.


### Infinite Execution

The program runs indefinitely, allowing philosophers to think, pick up forks, eat, and return to thinking in an endless cycle.


### Contributions

Contributions and improvements to the code are welcome.


### Usage

To compile and run the program, you can use the following commands in your terminal:

```shell
g++ -std=c++11 -o dining_philosophers dining_philosophers.cpp
./dining_philosophers






 
