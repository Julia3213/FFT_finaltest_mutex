#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

int sharedData = 0;
int count = 10;

void writerThread() {
    for (int i = 0; i < count; ++i) {
        mtx.lock();
        sharedData = i;
        std::cout << "Write: " << i << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void readerThread() {
    for (int i = 0; i < count; ++i) {
        mtx.lock();
        std::cout << "Read: " << sharedData << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread writer(writerThread);
    std::thread reader(readerThread);

    writer.join();
    reader.join();

    return 0;
}
