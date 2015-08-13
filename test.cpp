#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include "blocking_queue.h"

#include <sys/time.h>

static double getMS(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec*1000.0 + tv.tv_usec/1000.0;
}

using namespace blocking;
const size_t queueSize = 20;


template<typename T>
void put(BlockingQueue<T> &queue){
	for(int i = 0; i < queueSize; ++i){
		queue.put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(18));
	}
}
template<typename T>
void take(BlockingQueue<T> &queue){
	int k = 0;
	while(1){
	while(queue.size()){
		queue.take();
		std::this_thread::sleep_for(std::chrono::milliseconds(32));
		k++;
	}
	if(k==queueSize) break;}
}

int main(int argc, char* argv[]){

	BlockingQueue<int> queue;

	double st = getMS();
	std::thread t1(put<int>,std::ref(queue));
	std::thread t2(take<int>,std::ref(queue));

	t1.join();
	t2.join();
	double et = getMS();
	std::cout << "Muil threads use time: " << et-st << "ms" << std::endl;

	st = getMS();
	put(queue);
	take(queue);
	et = getMS();
	std::cout << "Single thread use time: " << et-st << "ms" << std::endl;

	return 0;
}

