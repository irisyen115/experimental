#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>

std::vector<int> poisoned_apples; // 毒蘋果陣列
std::mutex mtx; // 互斥鎖
int total_eaten = 0; // 總共吃掉的蘋果數量

// 模擬吃蘋果的函式
void eat_apples(int thread_id, int num_threads) {
    while (true) {
        int apple_index;
        {
            std::lock_guard<std::mutex> lock(mtx); // 上鎖保護臨界區
            if (total_eaten >= poisoned_apples.size()) {
                break; // 所有蘋果都被吃完了
            }
            apple_index = total_eaten; // 取得下一個蘋果的索引
            total_eaten++;
        }

        int sleep_time = poisoned_apples[apple_index];
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time)); // 模擬麻痺時間
        // std::cout << "Thread " << thread_id << " ate apple " << apple_index << " in " << sleep_time << "ms" << std::endl;
    }
}

int main() {
    const int num_apples = 1024;
    const int num_threads[] = {1, 4, 8, 16}; // 不同數量的執行緒

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(10, 100); // 隨機生成毒蘋果的麻痺時間

    for (int i = 0; i < num_apples; ++i) {
        poisoned_apples.push_back(dis(gen));
    }

    for (int i = 0; i < sizeof(num_threads) / sizeof(num_threads[0]); ++i) {
        total_eaten = 0; // 重設總共吃掉的蘋果數量

        auto start_time = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> threads;

        for (int j = 0; j < num_threads[i]; ++j) {
            threads.emplace_back(eat_apples, j, num_threads[i]);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "With " << num_threads[i] << " threads, time taken: " << duration.count() << " milliseconds" << std::endl;
    }

    return 0;
}