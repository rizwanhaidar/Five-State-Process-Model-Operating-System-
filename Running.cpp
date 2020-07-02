#include "utill.h"
using namespace std;

char *read_from_ready(int fd, int size)
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
            cout << "\n***********************I am your Running Process State***********************\n";
            cout << "\nRead successfuly\n";
        }
    }
    else
    {
        //if success in ist attemnt
        cout << "\n***********************I am your Running Process State***********************\n";
        cout << "\nRead successfuly\n";
    }
    return data_;
}

int main(int argc, char **argv)
{
    sleep(4);
    //sleep(4);
//type casting of the the argumnets
    int choice = argv[0][0];
    choice -= 48;

    stringstream geek(argv[1]);
    int fd_pipe_from_ready = 0;
    geek >> fd_pipe_from_ready;

    stringstream r_to_ready(argv[2]);
    int fd_pipe_to_ready = 0;
    r_to_ready >> fd_pipe_to_ready;

    stringstream ru_to_bl(argv[3]);
    int fd_pipe_to_block = 0;
    ru_to_bl >> fd_pipe_to_block;

    stringstream ru_to_ex(argv[4]);
    int fd_pipe_to_exit = 0;
    ru_to_ex >> fd_pipe_to_exit;

    if (choice == 1)
    {
        cout << "RR in running\n";
    }
    else if (choice == 2)
    {
        cout << "FCFS in running\n";
        char *data_from_new = read_from_ready(fd_pipe_from_ready, 100);
        //cout<<data_from_new<<endl;
        PROCESS temp = to_process(data_from_new);
        cout << endl;

        int process = 1;
        temp.getter_PROCESS();//printing the process
        int cpu_time = 0;
        while (cpu_time < temp.arrival_time)
        {
            sleep(temp.arrival_time);
            cpu_time = temp.arrival_time;
        }
    label_Z:
        if (process > 1)
        {
            // send signal back to the ready to send next process
            if (write(fd_pipe_to_ready, "Send Next Process", sizeof("Send Next Process")))
            {
                cout << "\nwritten to pipe for ready from Running\n";
            }
            //read the pipe for new process
            //start execution of that process
            data_from_new = read_from_ready(fd_pipe_from_ready, 100);
            temp = to_process(data_from_new);
            temp.getter_PROCESS();
            cout << endl;
        }
        if (temp.blocked_time == 0)
        {
            temp.start_time = cpu_time;
            temp.processing_time = 0;
        }
        while (temp.processing_time < temp.burst_time)
        {
            sleep(1);
            temp.processing_time++;
            cpu_time++;
            if ((cpu_time % 5 == 0) && (temp.processing_time != temp.burst_time) && (temp.start_time != cpu_time))
            {
                /* initialize random seed: */

                srand(time(NULL));
                /* generate secret number between 1 and 10: */
                int iSecret = rand() % 2;
                //write to block state or continue
                if (iSecret == 1)
                {
                    cout << "\nProcess wil continue\n";
                    ; //continue
                }
                else if (iSecret == 0)
                {
                    sleep(1);
                    //write to the block state
                    // temp.getter_PROCESS();
                    char *ptr = temp.to_char();
                    if (write(fd_pipe_to_block, ptr, 100))
                    {

                        cout << "\nwritten to pipe for Block from Running\n";
                        goto por;
                    }
                }
            }
            if (temp.processing_time == temp.burst_time)
            {
                temp.completion_time_ = temp.blocked_time+cpu_time;
                char *ptr = temp.to_char();
                if (write(fd_pipe_to_exit, ptr, 100))
                {
                    cout << "\nwritten to pipe for exit from Running\n";
                }
                cpu_time++;
                //write to exit
            }
        }
    por:
        process++;
        goto label_Z;
    }
    else if (choice == 3)
    {
        cout << "SJF in running\n";
    }
    else if (choice == 4)
    {
        cout << "STRF in running\n";
    }

    return 0;
}