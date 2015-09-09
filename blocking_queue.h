#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <iostream>
#include <vector>
#include <queue>
#include <condition_variable>
#include <assert.h>

#include "opencv2/core/core.hpp"

#define MAX_CAPACITY 20
template<typename T>
class BlockingQueue{

	public:
		BlockingQueue() :mtx(), m_full(), m_empty(), m_capacity(MAX_CAPACITY) { }
		void put(const T& task);
		T take();
		T front(); 
		T back();
		size_t size();
		bool empty();
		void setCapacity(const size_t capacity);
	private:
		BlockingQueue(const BlockingQueue& rhs);
		BlockingQueue& operator= (const BlockingQueue& rhs);

	private:
		mutable std::mutex mtx;
		std::condition_variable m_full;
		std::condition_variable m_empty;
		std::queue<T> m_queue;
		size_t m_capacity; 
};

#endif
