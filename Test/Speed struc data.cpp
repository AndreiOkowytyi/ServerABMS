
#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <map>
#include <queue>
#include <mutex>

class Time{
 public:
	void start();
	void stop();

 private:
	std::chrono::steady_clock::time_point m_start;
	std::chrono::steady_clock::time_point m_stop;
};

void  Time::start() {

	m_start = std::chrono::high_resolution_clock::now();
}

void  Time::stop() {

	this->m_stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time = m_stop - m_start;
	std::cout << time.count() << std::endl;
}


class Thread_Q {
 public:
	 Thread_Q(short x, short y, std::queue<int>& que);
	 ~Thread_Q() { delete[] key; }
	 void work(int x, int y);

 private:
	int* key = nullptr;
	std::queue<int>* m_que = nullptr;
};

void Thread_Q::work(int x, int y) {

	for (; x < y; ++x) {

		auto p = this->m_que->back();
		this->m_que->pop();
		p++;
	}
}

Thread_Q::Thread_Q(short x, short y, std::queue<int>& que) {

	this->m_que = &que;

	key = new int[2500];

	int index = 0;
	for (int k = x; k < y; ++k) {

		key[index] = k;
		index++;
	}
}


class Thread_M {
 public:
	Thread_M(short x, short y, std::map<int, int> &map_);
	~Thread_M() { delete[] key; }
	void work(int x, int y);

 private:
	int* key = nullptr;
	std::map<int, int>* m_map = nullptr;
};

Thread_M::Thread_M(short x, short y, std::map<int, int>& map_) {

	this->m_map = &map_;

	key = new int[2500];

	int index = 0;
	for (int k = x; k < y; ++k) {

		key[index] = k;
		index++;
	}
}

std::mutex as;

void Thread_M::work(int x, int y) {

	for (; x < y; ++x) {
	
		std::unique_lock<std::mutex> v(as);
		auto p = this->m_map->find(this->key[x])->second;
		this->m_map->erase(this->key[x]);
		p++;
	}
}

std::map<int, int> m_map;
std::queue<int> q_1_;
std::queue<int> q_2_;

int main() {

	Thread_M a_M(0, 2500, m_map);
	Thread_M b_M(2500, 5000, m_map);

	Time time_1;
	time_1.start();

	for (short x = 0; x < 5000; ++x) m_map.emplace(std::pair<int, int>(x, x));


	std::thread as_1([&]() {
		
		a_M.work(0, 2500);
		});

	std::thread as_2([&]() {

		b_M.work(0, 2500);
		});

	as_1.join();
	as_2.join();

	time_1.stop();

	////////////////////
	////////////////////
	////////////////////


	Thread_Q a_Q(0, 2500, q_1_);
	Thread_Q b_Q(2500, 5000, q_2_);

	Time time;

	time.start();

	for (short x = 0; x < 5000; ++x) {

		q_1_.emplace(x);
		q_2_.emplace(x);
	}


	std::thread as_3([&]() {

		a_Q.work(0, 2500);
		});

	std::thread as_4([&]() {

		b_Q.work(0, 2500);
		});

	as_3.join();
	as_4.join();

	time.stop();

	return 0;
}