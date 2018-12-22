#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <string>


static void countDemension(string filename, int* num_of_calls, int* num_of_rows){
	std::ifstream fin;

	fin.open("C:\\Users\\tapuz_000\\Desktop\\Oprating systems\\github_hw3\\tiny.txt");
    int val = 0;
    int num_items = 0;
    char c;
    while ( fin.get(c)){
        if(c!='\n'){
            ++num_items;
        }
    }
    *num_of_calls=num_items;
    while(fin>>val){
        ++num_items;
//        if (num_items%(*num_of_calls)==0){
//
//        }
    }
    *num_of_rows=num_items/(*num_of_calls);
}

Game::Game(game_params params){
    int num_of_calls;
    int num_of_rows;
    countDemension(params.filename,&num_of_calls,&num_of_rows);
    
}



/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
void Game::run() {

	_init_game(); // Starts the threads and all other variables you need
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((float)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(NULL);
	} // generation loop
	print_board("Final Board");
	_destroy_game();
}

void Game::_init_game() {
	// Create threads
	//TODO manage constructor
	tasks_q=new PCQueue<Task>;
	threadArray =new gameThread*[m_thread_num];
	for (int j = 0; j < m_thread_num; ++j){
		threadArray[j] = new gameThread(j,tasks_q);
	}
    // Create game fields --- in constructor

	// Start the threads
	for (int i = 0; i < m_thread_num; ++i){
		threadArray[i]->start();
	}

	// Testing of your implementation will presume all threads are started here
};

void Game::_step(uint curr_gen) {
	// Push jobs to queue

	int min_rows=(height_matrix)/m_thread_num;
	int last_task_rows=height_matrix;
	for (int j = 0; j < m_thread_num; ++j){
		if(j!=m_thread_num-1){
			tasks_q->push(Task(j*min_rows, j*min_rows + min_rows + width_matrix, curr, next,height_matrix,width_matrix));
			last_task_rows-=min_rows;
		}
		else{
			tasks_q->push(Task(j*min_rows, j*min_rows + last_task_rows + width_matrix, curr, next,height_matrix,width_matrix));
		}
	}

	// Wait for the workers to finish calculating
	for (int i = 0; i <m_thread_num; ++i){
		threadArray[i]->join();
	}

	// Swap pointers between current and next field
	int** temp;
	temp=curr;
	curr=next;
	next=temp;
}

void Game::_destroy_game(){
	// Destroys board and frees all threads and resources
	//needed?
	for (int i = 0; i <m_thread_num; ++i){
		threadArray[i]->join();
	}

	delete tasks_q;
	for (int i = 0; i < m_thread_num; ++i){
		delete(threadArray[i]);
	}
	delete[](threadArray);

	// Not implemented in the Game's destructor for testing purposes. 
	// Testing of your implementation will presume all threads are joined here
}

/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
inline  void Game::print_board(const char* header) {

	if(print_on){

		// Clear the screen, to create a running animation 
		if(interactive_on)
			system("clear");

		// Print small header if needed
		if (header != NULL)
			cout << "<------------" << header << "------------>" << endl;
		
		// TODO: Print the board 

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}

}


/* Function sketch to use for printing the board. You will need to decide its placement and how exactly 
	to bring in the field's parameters. 

		cout << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
		for (uint i = 0; i < field_height ++i) {
			cout << u8"║";
			for (uint j = 0; j < field_width; ++j) {
				cout << (field[i][j] ? u8"█" : u8"░");
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;
*/ 



