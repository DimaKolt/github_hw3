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
	gameThread(int id ,PCQueue<Task>* queue) :Thread(id),task_queue(queue){};
	 void thread_workload() override{
		 while (1){
			 //?????
			 task = task_queue->pop();
			 printf("task num: %d pop task from line %d, to line %d \n",thread_id(), task.getStartIndex(), task.getEndIndex());
			 //start timer
			
			 calcNextGen();
            
             //stop timer
             //append duration to shared tile history vector
            
            
            
             task.get_mutex()->down(); //TODO here for debug
            
             task.counterDown();
			 printf("counter from thread is %d\n", task.check_counte());
			 if (task.check_counte() == 0){
				 task.get_barrier()->up();
				 printf("all tasks is finished\n");
			 }
			 task.get_mutex()->up();
		 }
	 }

	 int cubeStatus(int i,int j, int width,int hight,int** curr){
		if( i<0 || i>=hight || j <0 || j>=width) return 0;
		printf("curr[%d][%d]=%d,",i,j,curr[i][j]);
		 return curr[i][j];
	 }
	 int cubeInNextGen(int i,int j, int width,int hight,int** curr){
	 	int cube_current_status=curr[i][j];
	 	int cube_neighbours=0;
		 printf("start handle curr[%d][%d], status: %d by task: %d\n",i,j,cube_current_status,thread_id());
		 for (int k = 0; k <3; ++k){
		 	
			 cube_neighbours+=cubeStatus(i-1,j-1+k,width,hight,curr);
			 cube_neighbours+=cubeStatus(i+1,j-1+k,width,hight,curr);
		 }
		 cube_neighbours+=cubeStatus(i,j-1,width,hight,curr);
		 cube_neighbours+=cubeStatus(i,j+1,width,hight,curr);
		 printf("\n num of neighb %d \n", cube_neighbours);
		 if(cube_current_status==0 && cube_neighbours==3) return 1;
		 if(cube_current_status==1 && (cube_neighbours==2 || cube_neighbours==3)) return 1;
		 return 0;
	 }
	 void calcNextGen(){
         for (int i = task.getStartIndex(); i < task.getEndIndex(); ++i){
			 for (int j = 0; j <task.getWidth(); ++j){
			 	printf("the next matrix in next[%d][%d]=%d \n",i,j,task.getNext()[i][j]);
//			 	printf("check H : %d, W: %d \n",task.getHight(),task.getWidth());
				printf("check start index : %d , stop index: %d \n",task.getStartIndex(),task.getEndIndex());
			 	task.getNext()[i][j]=cubeInNextGen(i,j,task.getWidth(),task.getHight(),task.getCurr());
			 }
         }
	 }
private:
	PCQueue<Task>* task_queue;
	Task task;
//	Semaphore* sem;
    };




#endif
