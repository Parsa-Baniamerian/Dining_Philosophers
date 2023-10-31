#include <iostream>
#include <thread>
#include <mutex>

const int num_philosophers = 5;
std::mutex forks[num_philosophers];
std::mutex print_mutex; // Mutex for synchronized printing

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % num_philosophers;

    while (true) {
        // Think
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "Philosopher " << id << " is thinking." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Pick up left fork
        std::unique_lock<std::mutex> left(forks[left_fork]);
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "Philosopher " << id << " picked up the left fork." << std::endl;
        }

        // Check if the right fork is available
        if (forks[right_fork].try_lock()) {
            // Pick up the right fork
            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "Philosopher " << id << " picked up the right fork." << std::endl;
            }

            // Eat
            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "Philosopher " << id << " is eating." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            // Release forks
            forks[right_fork].unlock();
            forks[left_fork].unlock();

            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "Philosopher " << id << " is done eating and returning to thinking." << std::endl;
            }
        } else {
            // Release left fork if the right fork is not available
            left.unlock();
            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "Philosopher " << id << " released the left fork because the right fork was not available." << std::endl;
            }
        }
    }
}

int main() {
    std::thread philosophers[num_philosophers];
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i] = std::thread(philosopher, i + 1);
    }

    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i].join();
    }

    return 0;
}
