#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>

#define MAX_RANGE 100000000
#define SQRT_RANGE int (sqrt(MAX_RANGE))
#define SMALLEST_PRIME 2

bool is_prime[MAX_RANGE] = {};

void get_primes_thread(int min_range, int max_range) {
  for (int i = min_range; i <= max_range; i++) {
    if (is_prime[i]) {
      for (int j = i; j * i < MAX_RANGE; j++) {
        is_prime[j * i] = false;
      }
    }
  }
}

std::vector<int> get_primes_under() {

  std::fill_n(is_prime, MAX_RANGE, true);
  is_prime[0] = false; is_prime[1] = false;

  int range_increment = SQRT_RANGE / 8;

  std::thread primes_threads[8];

  for (int i = 0; i < 7; i++) {
    int min = std::min(3, range_increment * i);
    int max = range_increment * (i + 1);

    primes_threads[i] = std::thread(get_primes_thread, min, max);
  }

  for (auto& thread : primes_threads) {
    thread.join();
  }

  std::vector<int> primes;

  for (int i = 0; i < MAX_RANGE; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }

  return primes;
}

int main() {
  auto begin_execution = std::chrono::high_resolution_clock::now();

  std::vector<int> primes = get_primes_under();

  auto stop_execution = std::chrono::high_resolution_clock::now();

  auto execution_time = std::chrono::duration_cast<std::chrono::microseconds>(
      stop_execution - begin_execution);

  std::ofstream PrimesFile("primes.txt");

  long long prime_sum = 0;

  for (auto& prime : primes) {
    prime_sum += prime;
  }

  PrimesFile << execution_time.count() << " " << primes.size() << " " << prime_sum << std::endl;

  for (int i = primes.size() - 10; i < primes.size(); i++) {
    PrimesFile << primes[i] << " ";
  }

  PrimesFile.close();

  return 0;
}