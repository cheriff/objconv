
#include <chrono>
struct Timer {
    Timer(): start(std::chrono::steady_clock::now()) {}
    Timer(std::string t): start(std::chrono::steady_clock::now()), title(t) {}
    ~Timer() {
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        std::cout << title <<": "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    }
    private:
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::string title;
};
