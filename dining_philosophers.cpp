#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
const int num_philosophers = 5;
mutex forks[num_philosophers];
mutex print_mutex; // Mutex for synchronized printing

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % num_philosophers;
    bool done_eating = false;
    while (!done_eating) {
        // Think
        {
            lock_guard<mutex> lock(print_mutex);
            cout << "Philosopher " << id << " is thinking." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Pick up left fork
        unique_lock<mutex> left(forks[left_fork]);
        {
            lock_guard<mutex> lock(print_mutex);
            cout << "Philosopher " << id << " picked up the left fork." << endl;
        }

        // Check if the right fork is available
        if (forks[right_fork].try_lock()) {
            // Pick up the right fork
            {
                lock_guard<mutex> lock(print_mutex);
                cout << "Philosopher " << id << " picked up the right fork." << endl;
            }

            // Eat
            {
                lock_guard<mutex> lock(print_mutex);
                cout << "Philosopher " << id << " is eating." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(1000));

            // Release forks
            forks[right_fork].unlock();
            forks[left_fork].unlock();

            {
                lock_guard<mutex> lock(print_mutex);
                cout << "Philosopher " << id << " is done eating and returning to thinking." << endl;
                done_eating = true;
            }
        } else {
            // Release left fork if the right fork is not available
            left.unlock();
            {
                lock_guard<mutex> lock(print_mutex);
                cout << "Philosopher " << id << " released the left fork because the right fork was not available." << endl;
            }
        }
    }
}

int main() {
    thread philosophers[num_philosophers];
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i] = thread(philosopher, i + 1);
    }

    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i].join();
    }

    return 0;
}
