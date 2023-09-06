#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void threadFunction1() {
    std::cout << "Thread 1: Attempting to lock mutex1..." << std::endl;
    std::unique_lock<std::mutex> lock1(mutex1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate some work
    std::cout << "Thread 1: Attempting to lock mutex2..." << std::endl;
    std::unique_lock<std::mutex> lock2(mutex2);
    // Critical section
    std::cout << "Thread 1: Executing critical section..." << std::endl;
    // Release locks
    lock2.unlock();
    lock1.unlock();
}

void threadFunction2() {
    std::cout << "Thread 2: Attempting to lock mutex2..." << std::endl;
    std::unique_lock<std::mutex> lock2(mutex2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Simulate some work
    std::cout << "Thread 2: Attempting to lock mutex1..." << std::endl;
    std::unique_lock<std::mutex> lock1(mutex1);
    // Critical section
    std::cout << "Thread 2: Executing critical section..." << std::endl;
    // Release locks
    lock1.unlock();
    lock2.unlock();
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}