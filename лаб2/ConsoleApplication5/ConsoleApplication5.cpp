#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;

mutex mtx;

int main()
{
	int balls_in_storage = 10000;
	int balls_in_basket = 0;

	thread salesmans[2];
	thread buyers[3];

	for (int i = 0; i < 2; i++) {
		salesmans[i] = thread([&balls_in_storage, &balls_in_basket](int i) {

			int sum = 0;

			while (balls_in_storage != 0) {
				int n = rand() % 101;

				mtx.lock();

				if (n > balls_in_storage) {
					n = balls_in_storage;
				}

				balls_in_storage -= n;
				balls_in_basket += n;
				sum += n;

				mtx.unlock();

				this_thread::sleep_for(1us);
			}

			mtx.lock();
			cout << "Prodavez " << i << " vzyal " << sum << std::endl;
			mtx.unlock();

		}, i);

	}

	for (int i = 0; i < 3; i++) {
		buyers[i] = thread([&balls_in_storage, &balls_in_basket](int i) {
			int sum = 0;

			while (balls_in_storage + balls_in_basket != 0) {

				mtx.lock();

				if (balls_in_basket > 0) {
					sum++;
					balls_in_basket--;
				}

				mtx.unlock();

				this_thread::sleep_for(1us);
			}

			mtx.lock();
			cout << "Pokupatel " << i << " vzyal " << sum << std::endl;
			mtx.unlock();

		}, i);
	}
	for (int i = 0; i < 2; i++)
	{
		salesmans[i].join();
	}
	for (int i = 0; i < 3; i++)
	{
		buyers[i].join();
	}
}
