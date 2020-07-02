
#include<iostream>
#include<vector>
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
#include<math.h>
#include<cmath>
#include<algorithm> // for heap  
#include <queue>
#include <sstream>    
using namespace std;
//CLASS OF PROCESS


char *concat(const char *a, const char *b){
    int lena = strlen(a);
    int lenb = strlen(b);
    char *con = (char*)malloc(lena+lenb+1);
    // copy & concat (including string termination)
    memcpy(con,a,lena);
    memcpy(con+lena,b,lenb+1);        
    return con;
}

char * toArray(int number)
    {
 
  stringstream ss;  
  ss<<number;  
  string s;  
  ss>>s;    
  int n = s.length(); 
  
    // declaring character array 
  char *char_array = new char[n + 1]; 
  
    // copying the contents of the 
    // string to char array 
    strcpy(char_array, s.c_str());  
   // cout<<char_array<<endl;
    return char_array;
}
struct PROCESS
{
	int pid;
	int arrival_time;
	//int status;
	int burst_time;
    bool quantam;
    int quantam_;
    int waiting_time_;
    int completion_time_;
    int priority_;
    int processing_time;
    bool prior;
	//int priority;
	int blocked_time;
	int start_time;
    string type;
	//string code;
	//queue<string> q_code;

	PROCESS()
	{
        prior = false;
		pid = 0;
		arrival_time = 0;
        burst_time = 0;
        quantam = false;
        quantam_ =0;
        waiting_time_ = 0;
        completion_time_ = 0;
        priority_=0;
        processing_time = 0;
		blocked_time = 0;
        start_time = 0;
	}

    void setter_PROCESS_RR( string type1,int id_,int arrival_time1,int burst_time1, bool quan, int quant)
	{   
        pid = id_;
        burst_time = burst_time1;
		arrival_time = arrival_time1;
		type = type1;
        if(quan == true){
            quantam = true;
            quantam_ = quant;
        }
	}
    void set_pid(int p){
        pid = p;
    }
    void set_type(string type_){
        type  =type_;
    }
    string get_type(){
        return type;
    }
    int get_pid(){
        return pid;
    }
    int get_arr_time(){
        return arrival_time;
    }
    void set_arr_time(int arr){
        arrival_time = arr;
    }
    int get_pro_time(){
        return processing_time;
    }
    void set_pro_time(int pro){
        processing_time = pro;
    }
    void set_burst_time(int burst){
        burst_time = burst;
    }
    void set_quantam(int quan){
        quantam_ = quan;
        quantam = true;
    }
    int get_burst_time(){
        return burst_time;
    }
    int get_quantam(){
        return quantam_;
    }
    void set_priority(int pri){
            prior = true;
            priority_ = pri;
    }
    int get_priority(){
        return priority_;
    }
    void set_waiting(int wait_){
            waiting_time_ = wait_;
    }
    int get_Waiting(){
        return waiting_time_;
    }
    void set_completion_time(int comple_){
        completion_time_ =comple_;
    }
    int get_conpletion_time(){
        return completion_time_;
    }

	void getter_PROCESS()
	{
		cout << "   " <<pid;
		cout <<"        "<<arrival_time << "               " << burst_time <<"               "<<waiting_time_<<"                 "<<completion_time_<<"    "<<"          "<<start_time<<"          "<<blocked_time<<"      ";
        if(quantam && !prior){
            cout<<"       "<<quantam_;
        }
        else if(prior && !quantam){
            cout<<"       "<<priority_;
        }
        else if(prior && quantam){
            cout<<"       "<<priority_<<"       "<<quantam_<<endl;
        }
    
    cout<<endl;
    }
    void print_line(){
        cout<<" P_ID \t"<<" Arr_time \t"<<" Burst_time \t"<<" wait_time \t"<<" comp_time \t"<<" Start_t \t"<<" Block_t \t";
       if(quantam && !prior){
            cout<<"quantam\n";
        }
        else if(prior && !quantam){
            cout<<"priority\n";
        }
        else if(prior && quantam){
            cout<<"  Priority           Quantum     \n";
        }
        cout<<endl;
    }
    char *to_char (){
     
     char *pid_ = toArray(pid);
     //cout<<" pid = "<<pid_<<endl;
	 char * temp = concat (pid_,",");
     char *arr_ = toArray(arrival_time );
     temp = concat (temp,arr_ );
     temp = concat (temp,",");
     
     //cout<<" Arrival time = "<<arr_<<endl;
	 char *burs_ = toArray(burst_time);
     temp = concat(temp, burs_);
     temp = concat (temp,",");
     //cout<<" burst time = "<<burs_<<endl;
     char *quan_ = toArray((int)quantam);
     temp = concat(temp, quan_);
     temp = concat (temp,",");
     //cout<<" quantum bool = "<<quan_<<endl;
     char *qua_t = toArray(quantam_);
     temp = concat(temp, qua_t);
     temp = concat (temp,",");
     //cout<<" quantum int = "<<qua_t<<endl;
     char *wait_t =toArray(waiting_time_);
     temp = concat(temp, wait_t);
     temp = concat (temp,",");
     //cout<<" wait time = "<<wait_t<<endl;
     char *com_t = toArray(completion_time_);
     temp = concat(temp, com_t);
     temp = concat (temp,",");
     //cout<<" completion time = "<<com_t<<endl;
     char *prio_b = toArray((int)prior);
     temp = concat(temp, prio_b);
     temp = concat (temp,",");
     //cout<<" Bool Priority = "<<prio_b<<endl;
     char *prio_ = toArray(priority_);
     temp = concat(temp, prio_);
     temp = concat (temp,",");
     //cout<<" priority int = "<<prio_<<endl;
     char *proc_t = toArray(processing_time);
     temp = concat(temp, proc_t);
     temp = concat (temp,",");
     //cout<<" processing time = "<<proc_t<<endl;
     char *s_T = toArray(start_time);
     temp = concat(temp, s_T);
     temp = concat (temp,",");

     char *bl_t = toArray(blocked_time);
     temp = concat(temp, bl_t);
     temp = concat (temp,",");     
    
     char* type_ = new char[type.length()]; 
  
     // Copy character by character into array 
     for (int i = 0; i < type.length(); i++) { 
           type_[i] = type[i]; 
     } 
     //cout<<" Type = "<<type_<<endl; 
	 temp = concat(temp, type_);
     temp = concat (temp,";");
     //cout<<"\nTO CHar \n"<<temp;
     return temp;
    }
};
