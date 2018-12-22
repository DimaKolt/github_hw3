#ifndef __GAMERUN_H
#define __GAMERUN_H

#include "Headers.hpp"
#include "Thread.hpp"

/*--------------------------------------------------------------------------------
								  Auxiliary Structures
--------------------------------------------------------------------------------*/
struct game_params {
	// All here are derived from ARGV, the program's input parameters. 
	uint n_gen;
	uint n_thread;
	string filename;
	bool interactive_on; 
	bool print_on; 
};
/*--------------------------------------------------------------------------------
									Class Declaration
--------------------------------------------------------------------------------*/
class Game {
public:

	Game(game_params); //TODO init param to class parameters, but before to understant the N and the M size of given matrix. allocate 2 matrix on heap (curr & next)
	~Game();
	void run(); // Runs the game
	const vector<float> gen_hist() const; // Returns the generation timing histogram  
	const vector<float> tile_hist() const; // Returns the tile timing histogram
	uint thread_num() const; //Returns the effective number of running threads = min(thread_num, field_height)


protected: // All members here are protected, instead of private for testing purposes

	// See Game.cpp for details on these three functions //TODO
	void _init_game(); 
	void _step(uint curr_gen); 
	void _destroy_game(); 

	uint m_gen_num; 			 // The number of generations to run
	uint m_thread_num; 			 // Effective number of threads = min(thread_num, field_height)
	vector<float> m_tile_hist; 	  // Shared Timing history for tiles: First m_thread_num cells are the calculation durations for tiles in generation 1 and so on.

    inline void print_board(const char* header); //TODO this func after we know N and M of matrix

    // Note: In your implementation, all m_thread_num threads must write to this structure.
	vector<float> m_gen_hist;  	 // Timing history for generations: x=m_gen_hist[t] iff generation t was calculated in x microseconds
	vector<Thread*> m_threadpool; // A storage container for your threads. This acts as the threadpool. //TODO init here (from _init func) vector of threads
	
	
	bool interactive_on; // Controls interactive mode - that means, prints the board as an animation instead of a simple dump to STDOUT 
	bool print_on; // Allows the printing of the board. Turn this off when you are checking performance (Dry 3, last question)

	// TODO: Add in your variables and synchronization primitives
	
	int height_matrix;
	int width_matrix;
	PCQueue<Task> tasks_q; //TODO ThrTask
	//TODO add 2 heap feilds curr & next
	int** curr;
	int** next;
	
};
#endif
