
#include "utill.h"
using namespace std;

int main(int argc, char **argv)
{
    cout << "\n***********************I am your New Process State***********************\n";

    int choice = argv[0][0];

    choice -= 48;

    //int choice = 3;
    if (choice != 0 && choice <= 4)
    {

        char status[8] = "written";
        int file_desc;

        //Opening file on the basis of th choice
        if (choice == 1)
        {
            file_desc = open("RR.txt", O_RDONLY);
            //Round Robin
        }
        else if (choice == 2)
        {
            file_desc = open("FCFS.txt", O_RDONLY);
            //First come first serve
        }
        else if (choice == 3)
        {
            file_desc = open("SJF.txt", O_RDONLY);
            //Shortest job first
        }
        else if (choice == 4)
        {
            file_desc = open("SRTF.txt", O_RDONLY);
            //Strf
        }

        if (file_desc < 0)
            printf("\nError opening the file in the new state\n");

        //Reading the file
        int copy_desc = dup(file_desc);
        int size_ = 200;
        char readbuffer_new[size_];
        cout << "\nNew Process (State 1) Reading from file " << endl;

        if (!read(file_desc, readbuffer_new, size_))
        {
            //reading from file
            cout << "\nError in File reading in New state\n";
            exit(-1);
        }

        //A vector to store ever process indiviualy as a PROCESS (user defined variable)
        vector<PROCESS> *procs_array_new = process_Array(choice, readbuffer_new);
        //Process array will take choice and read buffer will return a vector that will contain different process
        //in short char * to list of PROCESSES

        cout << "\nBelow is the list of processes read from file\n";

        cout << "\n";
        cout << "\n*************\tAlgorithm Name = " << procs_array_new->front().type << "\t*************\n";
        procs_array_new->front().print_line();
        get_Vector_printed(procs_array_new); //it will print all the processes of the vector

        int fd_pipe_for_ready = argv[1][0];
        fd_pipe_for_ready -= 48;
        stringstream geek(argv[2]);
        int fd_pipe_for_exit = 0;
        geek >> fd_pipe_for_exit;
        
        int size__= procs_array_new->size();
        char * sizee = toArray(size__);
        cout<<size__<<endl;
        write(fd_pipe_for_exit,sizee,sizeof(sizee));
        if (write(fd_pipe_for_ready, readbuffer_new, sizeof(readbuffer_new)))
        { //writing to the ready state
            cout << "\nwritten to pipe for ready from new\n";
        }
    }
}