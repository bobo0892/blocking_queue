#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <iostream>
#include <list>
#include <condition_variable>
#include <assert.h>

namespace blocking {

	template<typename T>
	class BlockingQueue{

		public:
			BlockingQueue() :_mutex(), _condvar(), _queue() { }
			void put(const T& task);
			T take();
			size_t size();
		private:
			BlockingQueue(const BlockingQueue& rhs);
			BlockingQueue& operator= (const BlockingQueue& rhs);

		private:
			mutable std::mutex _mutex;
			std::condition_variable _condvar;
			std::list<T> _queue;
	};

	template class BlockingQueue<int>;
	template class BlockingQueue<float>;
	template class BlockingQueue<double>;

}

#endif
