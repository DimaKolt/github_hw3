#include "Game.hpp"


static void countDemension(string filename, int* num_of_calls, int* num_of_rows){
    std::ifstream fin;
//	fin.open("C:\\Users\\Dima\\Desktop\\Operation System\\github_hw3\\tiny.txt"); //TODO change to filename
	fin.open(filename);
    if (!fin.is_open()){
    	cout<< "Can't open " << filename << "!\n";
    }
    int num_items = 0;
    char c;
    while (fin.get(c) && c!='\n'){
        if(c!=' '){
            ++num_items;
        }
    }
    *num_of_calls=num_items;
    while(fin.get(c) ){
    	if(c!=' ' && c!='\n'){
		    ++num_items;
	    }
    }
    *num_of_rows=num_items/(*num_of_calls);
}

static void InitTheBoards(int** curr, int** next , int rows, int cols, string filename){
	std::ifstream fin;
//	fin.open("C:\\Users\\Dima\\Desktop\\Operation System\\github_hw3\\tiny.txt"); //TODO change to filename
	fin.open(filename);
	char c;
	int j = 0;
	for (int i = 0; i < rows; ++i){
		while (fin.get(c) && c != '\n'){
			if (c != ' '){
				curr[i][j] = std::atoi(&c);
				next[i][j]=0;
				j++;
			}
		}
		j=0;
	}
//	for (int i = 0; i < rows; ++i){
//		for (int j = 0; j < rows; ++j){
//			cout << curr[i][j] << " ";
//		}
//		cout << "\n";
//	}

}

/* Function sketch to use for printing the board. You will need to decide its placement and how exactly
	to bring in the field's parameters.
*/
static void PrintTheBoard(int** field, int field_height, int field_width){
	cout << u8"╔" ;
	for (int k = 0; k < field_width; ++k){
		cout << (u8"═");
	}
	cout << u8"╗" << endl;
	for (uint i = 0; i < (uint)field_height ;++i){
		cout << u8"║";
		for (uint j = 0; j < (uint)field_width; ++j){
			cout << (field[i][j] ? u8"█" : u8"░");
		}
		cout << u8"║" << endl;
	}
	cout << u8"╚" ;
	for (int k = 0; k < field_width; ++k){
		cout << (u8"═");
	}
	cout << u8"╝" << endl;
	
}

Game::Game(game_params params){
    int num_of_calls;
    int num_of_rows;
    countDemension(params.filename,&num_of_calls,&num_of_rows);
    
	m_gen_num=params.n_gen;
	if (params.n_thread< (uint)num_of_rows){
		m_thread_num=params.n_thread;
	}else{
		m_thread_num = (uint)num_of_rows;
	}
//	m_tile_hist = 0;
	interactive_on=params.interactive_on;
	print_on=params.print_on;
	height_matrix=num_of_rows;
	width_matrix=num_of_calls;
//	curr = new int[num_of_calls][num_of_rows];
	curr = new int*[num_of_rows];
	next = new int*[num_of_rows];
	for(int i = 0; i < num_of_rows; ++i){
		curr[i] = new int[num_of_calls];
		next[i] = new int[num_of_calls];
	}
	InitTheBoards(curr,next,height_matrix,width_matrix,params.filename);
	print_board("tiny");
}

Game::~Game(){
	for(int i=0;i<height_matrix; i++){
		delete curr[i];
		delete next[i];
	}
	delete[] curr;
	delete[] next;
}



/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
//void Game::run() {
//
//	_init_game(); // Starts the threads and all other variables you need
//	print_board("Initial Board");
//	for (uint i = 0; i < m_gen_num; ++i) {
//		auto gen_start = std::chrono::system_clock::now();
//		_step(i); // Iterates a single generation
//		auto gen_end = std::chrono::system_clock::now();
//		m_gen_hist.push_back((float)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
//		print_board(NULL);
//	} // generation loop
//	print_board("Final Board");
//	_destroy_game();
//}
//
//void Game::_init_game() {
//	// Create threads
//	//TODO manage constructor
//	gameThread* threadArray=new gameThread[m_thread_num];
//    // Create game fields
//	curr = new int*[height_matrix];
//	for(int i=0;i<width_matrix;i++)
//	{
//		curr[i]=new int[width_matrix];
//	}
//	next = new int*[height_matrix];
//	for(int i=0;i<width_matrix;i++)
//	{
//		curr[i]=new int[width_matrix];
//	}
//	// Start the threads
//	for (int i = 0; i < m_thread_num; ++i){
//		threadArray[i].start();
//	}
//	// Testing of your implementation will presume all threads are started here
//};

void Game::_step(uint curr_gen) {
	// Push jobs to queue
	//TODO create jobs
	// Wait for the workers to finish calculating
	// Swap pointers between current and next field
}

void Game::_destroy_game(){
	// Destroys board and frees all threads and resources 
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
		PrintTheBoard(curr,height_matrix,width_matrix);

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}

}





