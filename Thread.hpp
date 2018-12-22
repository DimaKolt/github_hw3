#ifndef __THREAD_H
#define __THREAD_H
#include "Headers.hpp"
#include "Task.hpp"
class Thread
{
public:
	Thread(uint thread_id) 
	{
		// Only places thread_id
		m_thread_id=thread_id;
	}

	virtual ~Thread() {} // Does nothing

	/** Returns true if the thread was successfully started, false if there was an error starting the thread */
	bool start()
	{
		int ret=pthread_create(&m_thread,NULL,entry_func,(void*)(this));
		return (!ret);
	}

	/** Will not return until the internal thread has exited. */
	void join()
	{
		pthread_join(m_thread,NULL);
	}

	/** Returns the thread_id **/
	uint thread_id()
	{
        return  m_thread_id;
	}
protected:
	/** Implement this method in your subclass with the code you want your thread to run. */
	virtual void thread_workload() = 0;
	uint m_thread_id ; // A number from 0 -> Number of threads initialized, providing a simple numbering for you to use

private:
	static void * entry_func(void * thread) { ((Thread *)thread)->thread_workload(); return NULL; }
	pthread_t m_thread;
};

class gameThread: public Thread
{
public:
	gameThread(int id ,PCQueue<Task>* queue):Thread(id),task_queue(queue){};
	 void thread_workload() override{}

	 int cubeStatus(int i,int j, int width,int hight,int** curr){
		if( i<0 || i>=width || j <0 || j>=hight) return 0;
		 return curr[i][j];
	 }
	 int cubeInNextGen(int i,int j, int width,int hight,int** curr){
	 	int cube_current_status=curr[i][j];
	 	int cube_neighbours=0;
		 for (int k = 0; k <3; ++k){
			 cube_neighbours+=cubeStatus(i-1,j+k,width,hight,curr);
			 cube_neighbours+=cubeStatus(i+1,j+k,width,hight,curr);
		 }
		 cube_neighbours+=cubeStatus(i,j-1,width,hight,curr);
		 cube_neighbours+=cubeStatus(i,j+1,width,hight,curr);
		 if(cube_current_status==0 && cube_neighbours==3) return 1;
		 if(cube_current_status==1 && (cube_neighbours==2 || cube_neighbours==3)) return 1;
		 return 0;
	 }
	 void calcNextGen(){
         for (int i = 0; i < task.getNumOfRows(); ++i){
			 for (int j = 0; j <task.getWidth(); ++j){
			 	task.getCurr()[i][j]=cubeInNextGen(i,j,task.getWidth(),task.getHight(),task.getCurr());
			 }
         }
	 }
private:
	PCQueue<Task>* task_queue;
	Task task;
};




#endif
