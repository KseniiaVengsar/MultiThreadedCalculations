// MultiThreadedCalculations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>//для работы со временем

//глобальный мьютекс
std::mutex СMutex;

//функция для потоков *передается номер потока и длительность
void calculate(int threadNum, int duration) {

    auto start = std::chrono::high_resolution_clock::now();//измеряем время

   
    for (int i = 0; i < duration; ++i) {
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // иммитация вычислений
       
        {
            std::lock_guard<std::mutex> lock(СMutex);
            std::cout << "Поток: " << threadNum << " [" << std::string(i + 1, '=') << std::string(duration - i - 1, ' ') << "] " << i + 1 << "/" << duration << "\n";
        }
    }
    //измеряем сколько времени занял расчет
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  
    {
        std::lock_guard<std::mutex> lock(СMutex);
        std::cout << "Поток " << threadNum << " Время: " << duration_ms << " ms\n";
    }
}

int main() {

    std::setlocale(LC_ALL, "RU");

    const int numThreads = 3; // количество потоков
    const int calculationDuration = 10; //длительность расчета

    // Вектор для хранения потоков
    std::vector<std::thread> threads;

    // Запускаем потоки
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(calculate, i + 1, calculationDuration);
    }

    // Дожидаемся завершения всех потоков
    for (std::thread& t : threads) {
        t.join();
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
