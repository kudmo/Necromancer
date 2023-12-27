#include <Game.h>
#include <iostream>
#include <chrono>

int main() {

    Game g = Game("Profiling/input_files/test_dungeon.json");

    auto start = std::chrono::system_clock::now();
    g.Update();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;


    std::cout << "TIME : " << elapsed_seconds.count() << std::endl;
}
