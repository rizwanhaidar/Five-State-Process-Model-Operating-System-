
#include"utill.h"
using namespace std;

char * read_from_running(int fd,int size){
    bool read_s;
  char *data_=new char[size];
        read_s =read(fd, data_ , size);

    if(!read_s){
            while(!read){
                    read_s =read(fd , data_ , size);
            }
        if(read_s){
           cout<<"\n***********************I am your Exit Process State***********************";
            cout<<"\nMessage in exit is = "<<data_;
        }
    }
    else{
        cout<<"\n***********************I am your Exit Process State***********************";
        cout<<"\nMessage in exit is = "<<data_;
    }    
    return data_;
}

int main(int argc, char** argv) 
{

      PROCESS temp;
   int file_desc = open("Output1.txt", O_CREAT|O_WRONLY , 0777); 
 
    if(file_desc < 0) 
       printf("Error opening the file in Exit State\n"); 
    sleep(1);
    stringstream aeek(argv[2]); 
    int fd_pipe_from_new = 0; 
    aeek >> fd_pipe_from_new; 
    char * siz1e = new char[2];
    read(fd_pipe_from_new, siz1e ,sizeof(siz1e));
    stringstream si(siz1e); 
    int t_size = 0; 
    si >> t_size;
    stringstream geek(argv[1]); 
    int fd_pipe_from_running = 0; 
    geek >> fd_pipe_from_running; 
    

    vector<string> exit_array;
    int x=0;
    vector<PROCESS> terminating_proccesses;
 while(x<t_size){
    char * data_from_running = read_from_running(fd_pipe_from_running,100);
    int count = 0;
    for(int i=0;data_from_running[i]!= ';';i++){
        count++;
    }

/*waitingTime = startTime - arrivalTime

turnaroundTime = burstTime + waitingTime = finishTime- arrivalTime*/

    data_from_running[count+1] = '\n'; 
    PROCESS z_proc = to_process(data_from_running);
    z_proc.set_waiting(z_proc.start_time-z_proc.arrival_time);
    terminating_proccesses.push_back(z_proc);
    exit_array.push_back(data_from_running);

    //write(file_desc,data_from_running, count+2); 
    x++;
    cout<<x<<endl;
}

outq:
    int saved =dup(1);
    close(1);
    dup(file_desc);       
    close(file_desc);
    terminating_proccesses.at(0).print_line();
    for(int i=0;i<exit_array.size();i++){
        terminating_proccesses.at(i).getter_PROCESS();
        cout<<"Turn Around Time = "<<terminating_proccesses.at(i).burst_time+terminating_proccesses.at(i).waiting_time_<<endl;
    }
    //printf("ssdfgh\n");
//cout<<data_from_running;
    fflush(stdout);  // <-- THIS
    // restore it back
    dup2(saved, 1);
    close(saved);

    return 0;
}