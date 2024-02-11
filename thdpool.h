#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <set>
#include <unistd.h>
using callback = void*(*)(void*);
//定义任务
struct task
{
	task()
	{
		function=nullptr;
		arg=nullptr;
	}
	task(callback a,void* b)
	{
		function=a;
		arg=b;
	}
	callback function;
	void* arg;
};
//定义任务队列
class taskqueue
{
private:
	pthread_mutex_t tq_mutex;
	std::queue<task> tq_queue;
public:
	taskqueue();
	~taskqueue();
	void addtask(task &t);
	task taketask();
	inline int tasknum()
	{
		return tq_queue.size();
    };
};	
//定义线程池
class threadpool
{
private:
	std::set<pthread_t> workthds;
	pthread_t managerthd;
	taskqueue* tq;
	int minnum;
	int maxnum;
	int busynum;
	int alivenum;
	int killnum;
	pthread_mutex_t thdp_mutex;
	sem_t sem_wkr;
	bool shutdown = false;
private:
	static void* worker(void* arg);
	static void* manager(void* arg);
	void threadexit();
public:
	threadpool(int min,int max);
	~threadpool();
	void addtask(task &t);
	inline int getbusynum(){return busynum;};
	inline int getalivenum(){return alivenum;};
};

#endif










