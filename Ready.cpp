#include "utill.h"
#include <pthread.h>
using namespace std;
//GLobal Queue of FCFS
queue<PROCESS> FCFS_queue;
//THread id
pthread_t thread_id1;
pthread_t thread_id2;
//Pipe fd's
int fd_pipe_from_running = 0;
int fd_pipe_for_running = 0;
int fd_pipe_from_new = 0;
int fd_pipe_from_blocked = 0;
//different usable variables
bool queue_bool = false; //a variabe that has been used as a flag to avoid the synchorization problem
//as both block thread and ready needs the queue
//so once one is usingother cannot
int choice = 0;

char *read_from_new(int fd, int size)
{
    //A function that will read from the
    //pipe on the basis of provided file descriotor
    //and will read the specified number of bytes
    bool read_s;
    char *data_ = new char[size];
    read_s = read(fd, data_, size);

    if (!read_s)
    {
        //if failed at ist
        while (!read)
        {
            //read untill pipe does not have some important data
            read_s = read(fd, data_, size);
        }
        if (read_s)
        {
            //if reading is successful
            cout << "\n***********************I am your Ready Process State***********************\n";
            cout << "\nRead successfuly\n";
        }
    }
    else
    {
        //if success in ist attemnt
        cout << "\n***********************I am your Ready Process State***********************\n";
        cout << "\nRead successfuly\n";
    }
    return data_;
}

int find_min(vector<PROCESS> *ptr)
{
    //  a utillity function for
    //FCFS that will be help ful while maintaing the queue
    //will reatun the position of min on the basis on arrival time
    int pos = 0;
    int min_arr = INT32_MAX;
    int i;
    for (i = 0; i < ptr->size(); i++)
    {
        PROCESS temp = ptr->at(i);
        if (temp.arrival_time < min_arr)
        {
            pos = i;
            min_arr = temp.arrival_time;
        }
    }
    //returning position of min on the basis of arrival time
    return pos;
}
void *thread_from_block_f(void *input)
{
    //thread 2 that will handle the block to ready state
    char *data_from_blocked; //variable to read the porcees
    PROCESS temp;            //variable to store it as a PROCESS
linza:
    data_from_blocked = read_from_new(fd_pipe_from_blocked, 100); //reading from the blocked pipe
    temp = to_process(data_from_blocked);                         //to process from char *
lsd:
    if (queue_bool == false)
    {
        queue_bool = true;

        FCFS_queue.push(temp);
        queue_bool = false;
    }
    else
    {
        sleep(2);
        goto lsd;
    }
    goto linza;
}

void *thrd_to_ready_f(void *input)
{
    //thread one that will handle the Ready to running situation

    char *data_from_new = read_from_new(fd_pipe_from_new, 200);
    vector<PROCESS> *procs_array_new = process_Array(choice, data_from_new);

    char *signal_from_running = new char[100];
    int size = procs_array_new->size();
    for (int i = 0; i < size; i++)
    {
        int min_pos = find_min(procs_array_new);
        FCFS_queue.push(procs_array_new->at(min_pos));
        procs_array_new->erase(procs_array_new->begin() + min_pos);
    }
    int i = 0;
    while (!FCFS_queue.empty())
    {
        char *ptr = FCFS_queue.front().to_char();
        //avoiding the synchronization problem
    labelss:
        if (queue_bool == false)
        {
            queue_bool == true;
            FCFS_queue.pop();
            queue_bool = false;
        }
        else
        {
            sleep(1);
            goto labelss;
        }
        i++;
        //writing the process to the pipe for running
        if (write(fd_pipe_for_running, ptr, 100))
        {
            cout << "\nwritten to pipe for running from Ready\n";
        }
        signal_from_running = read_from_new(fd_pipe_from_running, 100);
        cout << " Received Signal from running to ready = " << signal_from_running << endl;
        //will wait of there is any process in the blocked state to come
        if (FCFS_queue.empty())
        {
            int ss = 25;
            cout << "\nWaiting for " << ss << " seconds if there is some porcess in Blocked state\n";
            sleep(30);
        }
    }

    cout << "\nAll processes have been processed via Ready\n";
    
    
    pthread_exit(NULL);
}
int main(int argc, char **argv)
{
    sleep(4);
    choice = argv[0][0];
    choice -= 48;
    //cout<<choice<<endl;

    stringstream geek(argv[1]);
    fd_pipe_from_new = 0;
    geek >> fd_pipe_from_new;

    stringstream heek(argv[2]);
    fd_pipe_for_running = 0;
    heek >> fd_pipe_for_running;

    stringstream run_to_ready(argv[3]);
    fd_pipe_from_running = 0;
    run_to_ready >> fd_pipe_from_running;

    stringstream block_to_ready(argv[4]);
    fd_pipe_from_blocked = 0;
    block_to_ready >> fd_pipe_from_blocked;

    if (choice == 1)
    {
        cout << "Welcome to the implementation of Round Robin Algorithm\n";
    }
    else if (choice == 2)
    {
        cout << "Welcome to the implementation of First Come First Serve Algorithm";
        //thread of ready
        pthread_create(&thread_id1, NULL, thrd_to_ready_f, NULL);
        //thread of block
        pthread_create(&thread_id2, NULL, thread_from_block_f, NULL);

        pthread_exit(NULL);
    }
    else if (choice == 3)
    {
        cout << "Welcome to the implementation of SJF Algorithm";
    }
    else if (choice == 4)
    {
        cout << "Welcome to the implementation of STRF Algorithm";
    }

    return 0;
}