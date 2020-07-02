#include <iostream> 
#include<stdlib.h> 
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<errno.h> 
#include<string.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include<string.h>
#include<pthread.h>
#include"Process.h"
#include<algorithm> // for heap  
#include <queue>
using namespace std;



vector<PROCESS> *process_Array(int algo, string instructions){
    
    int count_var =0;
    for(int i=0;i<128;i++){
       if(instructions[i] == '\n'){
            count_var++;    
        }
    }
    if(count_var >=3){
        vector<PROCESS> *to_ret = new vector<PROCESS>;
        
        //PROCESS * to_ret = new PROCESS[count_var/3];
        bool end_of_file = false;
        
        int i=0;
        int temp = 0;
        for( i=0; instructions[i]!='\n'; i++){
            temp++;
        }
        i++;
        string algo_name = instructions.substr(0,temp);
        //cout<<algo_name<<endl;
        bool quan_flag =false;
        char quan = 'd', burst_ = 'd', arr_ = 'd';
        int quantum_time = 0;
        if(algo == 1){
            quan_flag = true;
            
            for(;instructions[i]!='\n';i++){
                quan = instructions[i];
                quantum_time =quantum_time *10;
                int qaz = (int)quan -48;
                quantum_time = quantum_time + qaz;
            }
            
            i++;
        }    
        //cout<<quan<<endl;
        //cout<<instructions[i]<<endl;
        //cout<<quan<<endl;



     // cout<<"\n"<<algo_name<<endl;
        int proc_counter = 1, array_assignment = 0;
        do{
            for(;instructions[i]!='\n';i++){
                ;
            }    
            
            i++;
            int arr_time = 0;
            for(;instructions[i]!='\n';i++){
                arr_ = instructions[i];
                arr_time = arr_time *10;
                int asd = (int)arr_-48;
                arr_time = arr_time +  asd;
            }
            
            //cout<<arr_<<endl;
            i++;
            int burst_time = 0;
            for(;instructions[i]!='\n';i++){
                burst_ = instructions[i]; 
                burst_time = burst_time*10;
                int xsw = (int)burst_ -48;
                burst_time = burst_time + xsw;
            }
              
           // cout<<burst_<<endl;
            i++;
 
            PROCESS temp;
            //cout<<endl<<quan<<endl;
            temp.setter_PROCESS_RR(algo_name,array_assignment+1,arr_time,burst_time,quan_flag,quantum_time);
            //to_ret[array_assignment].setter_PROCESS_RR(algo_name,array_assignment+1,(int)arr_-48,(int)burst_-48,quan_flag,(int)quan-48);
           // to_ret[array_assignment].getter_PROCESS();  
                to_ret->push_back(temp);
                
                //to_ret->push_back(temp);
            if(proc_counter == (count_var/3)){
                end_of_file =true;
            }
            else{
                proc_counter++;
                
            }
            array_assignment++;
            //cout<<end_of_file<<endl;
        }
        while(!end_of_file);
 
    return to_ret;
    }
    
}


void get_Vector_printed(vector<PROCESS> *temp ){
    
    vector<PROCESS>::iterator ptr; 
    ptr = temp->begin();
    // Displaying vector elements using begin() and end() 
    for (int i=0; i < temp->size(); i++ ){ 
       ptr->getter_PROCESS() ;
        ptr++;
    }
}

void print_array(char * ptr, int size){
    for(int i=0;i<size;i++){
        cout<<ptr[i];
    }
    cout<<endl;
}


PROCESS to_process(char * ptr){
    
    PROCESS temp;
    char arr[2];
    int counter=0;
    int i=0;
  //pid 
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_pid((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.set_pid(t);
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }
    //arr time
    i++;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_arr_time((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.set_arr_time(t);
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }    
   //burst time 
    i++;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_burst_time((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.set_burst_time(t);
    } 
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }    
   //Quantum time 
//1,3,9,1,5,0,0,0,0,0,RR;

    i++;
    counter = 0;
    int quantum_bool = (int)ptr[i]-48;
    if(quantum_bool == 0){
        i+=3;
        //cout<<"\nNo Quantum\n";
    }
    else{
    i+=2;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_quantam((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;
        temp.set_quantam(t);
    } 
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }     
}

   //waiting time 
    i+=1;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_waiting((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.set_waiting(t);
    }      
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }    
    //completion time 
    i+=1;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_completion_time((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.set_completion_time(t);
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }    
    //priority 
   i++;
   counter = 0;
    int priority_bool = (int)ptr[i]-48;
    if(priority_bool == 0){
        i+=3;
    }
    else{
    i+=2;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_priority((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;
        temp.set_priority(t);
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }      
}
    //Processing time 
    i+=1;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.set_pro_time((int)ptr[i-1]-48);
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.set_pro_time(t);
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }    
    //start time
    i+=1;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.start_time = (int)ptr[i-1]-48;
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.start_time = t;
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }    

    ///blocked time
    i+=1;
    counter = 0;
    while(ptr[i]!= ','){
        i++;
        counter++;
    }
    if(counter == 1){
        temp.blocked_time = (int)ptr[i-1]-48;
    }
    else if(counter == 2){
        int t = (int)ptr[i-2];
        t-=48;
        t*=10;
        t+= (int)ptr[i-1]-48;

        temp.blocked_time = t;
    }
    else if(counter == 3){
        int t = (int)ptr[i-3];
        t-=48;
        t*=10;
        t+= (int)ptr[i-2]-48;
        t*=10;
        t+= (int)ptr[i-1]-48;
    }        
    //Type 
    i++;
    char *ti= new char[5];
    int j=0;
    while(ptr[i]!= ';'){
        ti[j] = ptr[i];
        i++;
        j++;
    }
    ti[j] = '\0';
    temp.set_type(ti);
    //cout<<"\n To Process\n";
    //temp.getter_PROCESS();
    return temp;
}