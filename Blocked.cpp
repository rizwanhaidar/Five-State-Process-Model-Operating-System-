#include "utill.h"
#include <pthread.h>
using namespace std;

pthread_t thread_id1;
pthread_t thread_id2;
pthread_t thread_id3;
pthread_t id_x;
pthread_t id_X1;
queue<char *> que;
int fd_pipie_to_the_ready = 0;
int fd_pipe_from_running = 0;
bool writing = false;
bool wait_ = false;
bool proce = false;

char *read_from_running(int fd, int size)
{
    bool read_s = false;
    char *data_ = new char[size];
    read_s = read(fd, data_, size);

    if (!read_s)
    {
        while (!read)
        {
            read_s = read(fd, data_, size);
        }
        if (read_s)
        {
            cout << "\n***********************I am your Blocked Process State***********************\n";
            cout << "\nRead successfuly\n";
        }
    }
    else
    {
        cout << "\n***********************I am your Blocked Process State***********************\n";
        cout << "\nRead successfuly\n";
    }
    //cout<<"data in function \n "<<data_;

    return data_;
}

void perfrom_IO_print(void *input)
{
    char *data_from_running = (char *)input;
    char *data = (char *)input;
    PROCESS temp = to_process(data);
    //temp.getter_PROCESS();
    srand(time(NULL));
    int iSecret = rand() % 3;

    if (iSecret == 0)
    {
        cout << "\nI am in Input Queue\n";
    }
    else if (iSecret == 1)
    {
        cout << "\nI am in Output Queue\n";
    }
    else if (iSecret == 2)
    {
        cout << "\nI am in Print Queue\n";
    }

    srand(time(NULL));
    int iSecret_ = 15 + rand() % 10;
    cout << "I\\O will take " << iSecret_ << " Seconds ";
    sleep(iSecret_);
    temp.blocked_time += iSecret_;
    data = temp.to_char();
    if (write(fd_pipie_to_the_ready, data, 100))
    {
        cout << "\n Blocked : written to pipe of ready from Blocked\n";
    }
}

int main(int argc, char **argv)
{
    stringstream geek(argv[1]);
    geek >> fd_pipe_from_running;
    stringstream week(argv[2]);
    week >> fd_pipie_to_the_ready;
    while (1)
    {
        char *data_from_running;
        data_from_running = read_from_running(fd_pipe_from_running, 100);
        cout << "\n\n\nBlocked : ";
        cout << data_from_running << endl;
        perfrom_IO_print((void *)data_from_running);
    }

    return 0;
}
/*
void *thr_input(void *input)
{

    char *data = (char *)input;
    PROCESS temp = to_process(data);
    temp.getter_PROCESS();
    srand(time(NULL));

    cout << "\nI am in Input Queue\n";

    srand(time(NULL));
    int iSecret_ = 15 + rand() % 10;
    cout << "I\\O will take " << iSecret_ << " Seconds ";
    sleep(iSecret_);
    temp.blocked_time = iSecret_;
    if (write(fd_pipie_to_the_ready, data, 100))
    {
        cout << "\n Blocked : written to pipe from Blocked\n";
    }

    pthread_exit(NULL);
}

void *thr_output(void *input)
{
    char *data = (char *)input;
    PROCESS temp = to_process(data);
    temp.getter_PROCESS();
    cout << "\nI am in output Queue\n";

    srand(time(NULL));

    int iSecret_ = 15 + rand() % 10;
    sleep(iSecret_);
labqz:
    temp.blocked_time = iSecret_;
    if (writing == false && wait_ == false)
    {
        writing = wait_ = true;
        if (write(fd_pipie_to_the_ready, data, 100))
        {
            cout << "\nwritten to pipe ready from Blocked\n";
        }
        writing = wait_ = false;
    }
    else
    {
        sleep(2);
        goto labqz;
    }
    pthread_exit(NULL);
}

void *thr_Print(void *input)
{
    char *data = (char *)input;
    PROCESS temp = to_process(data);
    temp.getter_PROCESS();
    cout << "\nI am in Print Queue\n";

    srand(time(NULL));

    int iSecret_ = 15 + rand() % 10;
    sleep(iSecret_);
qaws:
    temp.blocked_time = iSecret_;
    if (writing == false && wait_ == false)
    {
        writing = wait_ = true;
        if (write(fd_pipie_to_the_ready, data, 100))
        {
            cout << "\nwritten to pipe ready from Blocked\n";
        }
        writing = wait_ = false;
    }
    else
    {
        sleep(2);
        goto qaws;
    }
    pthread_exit(NULL);
}

/*
void create_thread(void * input){
    char * data_from_running = (char *)input;
    char * data = (char *)input;
    PROCESS temp = to_process(data);
    temp.getter_PROCESS();
    srand(time(NULL));
    int iSecret = rand() % 3 ;
    
    if(iSecret == 0){
    cout<<"\nI am in Input Queue\n";
    }
    else if(iSecret == 1){
    cout<<"\nI am in Output Queue\n";    
    }
    else if(iSecret == 2){
    cout<<"\nI am in Print Queue\n";
    }

    srand (time(NULL));
    int iSecret_ = 15+ rand() %10  ;
    cout<<"I\\O will take "<< iSecret_ <<" Seconds ";
    sleep(iSecret_);
    temp.blocked_time = iSecret_;
    if(write(fd_pipie_to_the_ready , data , 100)){
            cout<<"\n Blocked : written to pipe from Blocked\n";
    }        
    //pthread_create(&thread_id1,NULL,thr_input,(void *)data_from_running);
        //Input Queue
      //  pthread_exit(NULL);
}*/
/*
void *insert_queue(void * input)
{
    while (1)
    {
        char *data_from_running;
        data_from_running = read_from_running(fd_pipe_from_running, 100);
        cout << "\n\n\nBlocked : ";
        cout << data_from_running << endl
             << "\n\n\n";
       que.push(data_from_running);
       // que.push_back(data_from_running);
        proce = true;
    }
      pthread_exit(NULL);
}

void *block_handler(void * input)
{
    while(que.empty()){
        sleep(1);
    }
    while (!que.empty())
    {
        char *data_from_running = que.front();
        que.pop(); 
        
        if (que.size() == 0)
        {
            proce = false;
        }
       // cout<<data_from_running<<endl;
        srand(time(NULL));
        int iSecret = rand() % 3;
        if (iSecret == 0)
        {   cout<<"\nInput\n";
            pthread_create(&thread_id1, NULL, thr_input, (void *)data_from_running);
            //Input Queue
            pthread_exit(NULL);
        }
        else if (iSecret == 1)
        {
            cout<<"\nOutput\n";
            pthread_create(&thread_id2, NULL, thr_output, (void *)data_from_running);
            //Print Queue
            pthread_exit(NULL);
        }
        else if (iSecret == 3)
        {
            cout<<"\nPrint\n";
            pthread_create(&thread_id3, NULL, thr_Print, (void *)data_from_running);
            //Output Queue
            pthread_exit(NULL);
        }
        if(proce == false){
            while(proce == false){
                sleep(2);
            }
        }
    }
      pthread_exit(NULL);
}

int main(int argc, char **argv)
{

    stringstream geek(argv[1]);
    
    geek >> fd_pipe_from_running;
    stringstream week(argv[2]);

    week >> fd_pipie_to_the_ready;
    //char * data_from_running;

    int x = 7;
  
    pthread_create(&id_x, NULL, insert_queue, NULL);
    
    pthread_create(&id_X1, NULL, block_handler, NULL);

        pthread_exit(NULL);
    /*while (1)
    {
            data_from_running = read_from_running(fd_pipe_from_running,100);
            cout<<"\n\n\nBlocked : ";
            cout<<data_from_running<<endl<<"\n\n\n";
    }
    
    //Implementation of multi threading in blocked but works for only ist 2 processes
/*
    while(1){
            data_from_running = read_from_running(fd_pipe_from_running,100);
            cout<<"\n\n\nBlocked : ";
            cout<<data_from_running<<endl<<"\n\n\n";
/*          pthread_create(&thread_id1,NULL,thr_input,(void *)data_from_running);
            //data_from_running = read_from_new(fd_pipe_from_running,100);
            pthread_exit(NULL);
            //create_thread((void *) data_from_running);
   } */
/*     
    srand (time(NULL));
    int iSecret = rand() % 3 ;
    if(iSecret == 0){
        pthread_create(&thread_id1,NULL,thr_input,(void *)data_from_running);
        //Input Queue
        pthread_exit(NULL);
    }
    else if(iSecret == 1){
        pthread_create(&thread_id2,NULL,thr_output,(void *)data_from_running);
        //Print Queue
        pthread_exit(NULL);
    }
    else if(iSecret == 3){
        pthread_create(&thread_id3,NULL,thr_Print,(void *)data_from_running);
        //Output Queue
        pthread_exit(NULL);
    }
}
*/
/* return 0;
}*/