#include "blocking_queue.h"
#include<stdio.h>
#include<stdlib.h>

namespace blocking {
	
	template<typename T>
	void BlockingQueue<T>::put(const T& task){
		std::lock_guard<std::mutex> lock(_mutex);
		_queue.push_back(task);
		std::cout << "put: " << task << std::endl;
		_condvar.notify_all(); 
	}

	template<typename T>
	T BlockingQueue<T>::take(){
		std::unique_lock<std::mutex> lock(_mutex);
		_condvar.wait(lock, [this]{return !_queue.empty();} );
		assert(!_queue.empty());
		T front(_queue.front());
		_queue.pop_front();
		std::cout << "take: " << front << std::endl;
		return front;
	}

	template<typename T>
	size_t BlockingQueue<T>::size(){
		std::lock_guard<std::mutex> lock(_mutex);
		return _queue.size();
	}

}

