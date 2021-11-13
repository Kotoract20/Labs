#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

int main()
{
	int n;
	unsigned int available_threads = std::thread::hardware_concurrency();
	
	std::cout << "Vvedite kolichestvo strok/stolbzov dlya matrisi:\n";
	std::cin >> n;
	
	std::cout << available_threads << " dostupno potokov.\n";
	std::cout << "Skolko potokov ispolzovat?\n";
	std::cin >> available_threads;

	int** A = new int*[n];
	int** B = new int*[n];
	int** C = new int*[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i] = new int[n];
			B[i] = new int[n];
			C[i] = new int[n];
		}
	}

	// fill 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
	;
		}

	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			
		}
	
	}

	std::vector<std::thread> thread_pool(available_threads);
	auto start_time = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < available_threads; i++) 
	{
		thread_pool[i] = std::thread([](int** a, int** b, int** c, int n, int available_threads, int thread_number) {

			int N = (n / available_threads) * (thread_number + 1);

			if (thread_number == available_threads - 1) N += n % available_threads;
			
			for (int i = (n / available_threads) * thread_number; i < N; i++) 
			{
				for (int j = 0; j < n; j++) 
				{
					for (int k = 0; k < n; k++) 
					{
						c[i][j] += a[i][k] * b[k][j];
					}
				}

			}

		}, A, B, C, n, available_threads, i);
	}


	for (int i = 0; i < available_threads; i++)
	{
		thread_pool[i].join();
		std::cout << "Potok" << i << " zakonchil rabotu" << std::endl;
	}
	
	auto stop_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
	std::cout << "\nPotrachennoe vremya: " << duration.count()<<" microsekund" << std::endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		}
	}

	return 0;
}
