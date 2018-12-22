//
// Created by tapuz_000 on 22/12/2018.
//

#ifndef GITHUB_HW3_TASK_HPP
#define GITHUB_HW3_TASK_HPP

class Task
{
private:
    int start_index;
    int end_index;
    int **curr_table;
    int **next_table;

public:
    Task(): start_index(0),end_index(0),curr_table(0),next_table(0){}
    Task(int start,int ending,int** curr,int** next): start_index(start),end_index(ending),curr_table(curr),next_table(next){}
    int getStartIndex(){ return start_index;}
    int getEndIndex(){ return end_index;}

    Task(const Task& task)= default;
    ~Task() = default;
};


#endif //GITHUB_HW3_TASK_HPP
