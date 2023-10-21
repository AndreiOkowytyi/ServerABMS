#pragma once

#ifndef QUEUE_FOR_WORKONG_WITH_THREADS
#define QUEUE_FOR_WORKONG_WITH_THREADS

#include <mutex>
#include <queue>
#include <condition_variable>
#include <QObject>

// Реализация потокобезопасной очереди.

template <class T>
class Queue{
 public:
	 void emplace(T& data);
     void emplace(T&& data);
	 T back();
	 bool empty();

 private:
	 std::queue<T>           m_queue;
	 std::mutex              m_mut;
     std::condition_variable m_cv;
};

template <class T>
void Queue<T>::emplace(T& data) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	this->m_queue.emplace(data);
	temp_lock.unlock();
	m_cv.notify_all();
}

template <class T>
void Queue<T>::emplace(T&& data) {

    std::unique_lock<std::mutex> temp_lock(this->m_mut);
    this->m_queue.emplace(std::move(data));
    temp_lock.unlock();
    m_cv.notify_all();
}

template <class T>
T Queue<T>::back() {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	this->m_cv.wait(temp_lock, [&]() { return !m_queue.empty(); });
	T temp_data = this->m_queue.front();
	this->m_queue.pop();
	return temp_data;
}

template <class T>
bool Queue<T>::empty() { 

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	return this->m_queue.empty();
}


template <class T>
class Data {
 public: 
	 void emplace(const int id, T *data);
	 void erase(const int key);
	 T* operator[] (const int id);
	 bool empty();

 private:
	 std::map<int, T>        m_map;
	 std::mutex              m_mut;
	 std::condition_variable m_cv;
};

template <class T>
void Data<T>::emplace(const int id, T *data) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	//this->m_map.emplace(std::pair<int, T>(id, data));
	temp_lock.unlock();
	m_cv.notify_all();
}

template<class T>
void Data<T>::erase(const int key) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	this->m_map.erase(key);
	temp_lock.unlock();
	m_cv.notify_all();
}

template <class T>
T* Data<T>::operator[] (const int id) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	auto it_map = this->m_map.find(id);
	if (it_map != this->m_map.end()) return it_map.second;
	else return nullptr;
}

template <class T>
bool Data<T>::empty() {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	return this->m_queue.empty();
}

#endif //QUEUE_FOR_WORKONG_WITH_THREADS