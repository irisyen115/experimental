#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono> // 加入 chrono 標頭檔

int shared_counter = 0;

void increment_counter(int num_iterations, int thread_id) {
    for (int i = 0; i < num_iterations; ++i) {
        shared_counter++;
        // std::cout << "Thread " << thread_id << " incremented shared_counter to " << shared_counter << std::endl;
    }
}

int main() {
    const int num_iterations = 5000;
    std::vector<std::thread> threads;

    auto start_time = std::chrono::high_resolution_clock::now(); // 開始計時

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(increment_counter, num_iterations, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // 結束計時
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Final counter value: " << shared_counter << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl; // 輸出經過的時間

    return 0;
}