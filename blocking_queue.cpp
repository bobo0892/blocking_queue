#include "blocking_queue.h"
	
template<typename T>
void BlockingQueue<T>::put(const T& task){
	std::unique_lock<std::mutex> lock(mtx);
	m_full.wait(lock, [this]{return (m_queue.size() < m_capacity);} );
	assert(m_queue.size() < m_capacity);
	m_queue.push(task);
	m_empty.notify_all(); 
}

template<typename T>
T BlockingQueue<T>::take(){
	std::unique_lock<std::mutex> lock(mtx);
	m_empty.wait(lock, [this]{return !m_queue.empty();} );
	assert(!m_queue.empty());
	T front(m_queue.front());
	m_queue.pop();
	m_full.notify_all();
	return front;
}

template<typename T>
size_t BlockingQueue<T>::size(){
	std::lock_guard<std::mutex> lock(mtx);
	return m_queue.size();
}

template<typename T>
T BlockingQueue<T>::front(){
	std::unique_lock<std::mutex> lock(mtx);
	m_empty.wait(lock, [this]{return !m_queue.empty();} );
	assert(!m_queue.empty());
	T front(m_queue.front());
	return front;
}

template<typename T>
T BlockingQueue<T>::back(){
	std::unique_lock<std::mutex> lock(mtx);
	m_empty.wait(lock, [this]{return !m_queue.empty();} );
	assert(!m_queue.empty());
	T back(m_queue.back());
	return back;
}

template<typename T>
bool BlockingQueue<T>::empty(){
	std::unique_lock<std::mutex> lock(mtx);
	return m_queue.empty();
}

template<typename T>
void BlockingQueue<T>::setCapacity(const size_t capacity){
	m_capacity = (capacity > 0 ? capacity : MAX_CAPACITY);
}
	
template class BlockingQueue<int>;
template class BlockingQueue<float>;
template class BlockingQueue<double>;
template class BlockingQueue<cv::Mat>;
