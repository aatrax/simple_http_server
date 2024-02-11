#include "thdpool.h"
#include <iostream>
#include <cstring>
taskqueue::taskqueue()
{
	pthread_mutex_init(&tq_mutex,nullptr);
}
taskqueue::~taskqueue()
{
	pthread_mutex_destroy(&tq_mutex);
}

void taskqueue::addtask(task& t)
{
	pthread_mutex_lock(&tq_mutex);
	tq_queue.push(t);
	pthread_mutex_unlock(&tq_mutex);
}

task taskqueue::taketask()
{
	task t;
	pthread_mutex_lock(&tq_mutex);
	if(!tq_queue.empty())
	{
		t=tq_queue.front();
		tq_queue.pop();
	}
	else
	{
		std::cout<<"take a task error"<<std::endl;
	}	
	pthread_mutex_unlock(&tq_mutex);
	return t;
}

threadpool::threadpool(int min,int max)
{
	minnum=min;
	maxnum=max;
	busynum=0;
	alivenum=min;
	killnum=0;
	sem_init(&sem_wkr,0,0);
	pthread_mutex_init(&thdp_mutex,nullptr);
	do{
		//这里使用new若堆内存不够实际上会抛出错误并终止程序，但加上检测增加稳健性
		tq = new taskqueue;
		if(tq == nullptr)
		{
			std::cout<<"init taskqueue failed..."<<std::endl;
			break;
		}
		pthread_t tmp_thd;
		//创建工作线程
		//创建的工作线程与管理员线程都选择和主线程分离，工作线程经常退出，所以线程回收
		//比较麻烦
		for(int i=0;i<minnum;i++)
		{
			pthread_create(&tmp_thd,NULL,worker,this);
			pthread_detach(tmp_thd);
			workthds.insert(tmp_thd);
			std::cout<<"create threads:"<<tmp_thd<<std::endl;
		}
		//创建管理员线程
		pthread_create(&managerthd,NULL,manager,this);
		pthread_detach(managerthd);
	}while(0);
}

void threadpool::addtask(task &t)
{
	tq->addtask(t);
	sem_post(&sem_wkr);
}
void* threadpool::worker(void* arg)
{
	threadpool* pool=(threadpool*)arg;
	task t;
	//工作线程不断工作，从任务队列取任务执行
	while (true)
	{
		sem_wait(&pool->sem_wkr);
		t=pool->tq->taketask();
		pthread_mutex_lock(&pool->thdp_mutex);
		pool->busynum++;
		pthread_mutex_unlock(&pool->thdp_mutex);
		std::cout<<"thread "<<std::to_string(pthread_self()) << " start working..." << std::endl;
		t.function(t.arg);
		std::cout<<"thread "<<std::to_string(pthread_self()) << " end working" << std::endl;
		//执行完毕，查看是否需要终止该线程
		pthread_mutex_lock(&pool->thdp_mutex);
		if(pool->shutdown==true)
		{
			pool->busynum--;
			pool->alivenum--;
			pthread_mutex_unlock(&pool->thdp_mutex);
			pool->threadexit();
		}
		pthread_mutex_unlock(&pool->thdp_mutex);
		//检查管理员是否想杀死一些工作进程
		pthread_mutex_lock(&pool->thdp_mutex);
		if(pool->killnum>0)
		{
			pool->killnum--;
			pool->busynum--;
			pool->alivenum--;
			pthread_mutex_unlock(&pool->thdp_mutex);
			pool->threadexit();
		}
		pool->busynum--;	
		pthread_mutex_unlock(&pool->thdp_mutex);
	}
} 

//manager线程主要是管理worker线程数量的，如果太多了则杀死一些worker线程，如果
//任务队列中还有许多任务得不到执行，那么需要增加一些worker线程
//关于具体删除和增加worker线程的最经济算法。。。
void* threadpool::manager(void* arg)
{
	threadpool* pool=(threadpool*) arg;
	int crt_num;//要创建线程的数量
	pthread_t crt_tid;//要创建线程的id
	int alivenum_tmp=pool->alivenum;
	int busynum_tmp=pool->busynum;
	int maxnum_tmp=pool->maxnum;
	int minnum_tmp=pool->minnum;
	while(true)
	{
		pthread_mutex_lock(&pool->thdp_mutex);
		if(pool->tq->tasknum()>alivenum_tmp/4 && alivenum_tmp<maxnum_tmp)
		{
			if(alivenum_tmp/4 > maxnum_tmp-alivenum_tmp)
				crt_num=maxnum_tmp-alivenum_tmp;
			else
				crt_num=alivenum_tmp/4;
			for(int j=0;j<crt_num;j++)
			{
				pthread_create(&crt_tid,NULL,worker,pool);
				std::cout<<"manager create a thread,id: "<<crt_tid<<std::endl;
				pool->workthds.insert(crt_tid);
			}
			pool->alivenum=pool->alivenum+crt_num;
		}
		if(busynum_tmp < alivenum_tmp/2 && alivenum_tmp > minnum_tmp)
		{
			if(alivenum_tmp/4 > alivenum_tmp-minnum_tmp)
				pool->killnum=alivenum_tmp-minnum_tmp;
			else
				pool->killnum=alivenum_tmp/4;
		}
		pthread_mutex_unlock(&pool->thdp_mutex);
		if(pool->shutdown==true)
			pthread_exit(NULL);
		sleep(5);
	}
}

threadpool::~threadpool()
{
	shutdown=true;
	//唤醒所有工作线程
	for(int i=0;i<workthds.size();i++)
		sem_post(&sem_wkr);	
	pthread_mutex_destroy(&thdp_mutex);
	sem_destroy(&sem_wkr);
	delete tq;
}

//创建这个threadexit函数在于结束一个工作线程时要将线程id数组中该线程id变为
void threadpool::threadexit()
{
	pthread_t my_tid=pthread_self();
	workthds.erase(my_tid);
	pthread_exit(NULL);
}




	








