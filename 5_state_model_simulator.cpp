
#include "utill.h"
using namespace std;

int main()
{
        int choice;
        //Menu
        //to chose between the algorithms to run
        cout << "\nMain Process\n";
        cout << "\nMake your choice for a Specific Algorithm\n";
        cout << "\nPress 1 for RR";
        cout << "\nPress 2 for FCFS";
        cout << "\nPress 3 for SJF";
        cout << "\nPress 4 for STRF\n";
        cin >> choice;

        //Pipes creation for inter process communication
        int fd_new_to_ready_procs[2], fd_running_to_ready_state[2],
            fd_ready_to_running_state[2], fd_Blocked_to_ready_state[2],
            fd_Running_to_block_state[2], fd_running_to_exit_state[2],
            fd_ready_to_exit_state[2];
        //pipes initialization
        int new_to_ready_procs = pipe(fd_new_to_ready_procs);
        int ready_to_running = pipe(fd_ready_to_running_state);
        int running_to_ready = pipe(fd_running_to_ready_state);
        int Running_to_block = pipe(fd_Running_to_block_state);
        int running_to_exit = pipe(fd_running_to_exit_state);
        int Blocked_to_ready = pipe(fd_Blocked_to_ready_state);
        int ready_to_exit = pipe(fd_ready_to_exit_state);

        pid_t new_proc_id = fork();
        if (new_proc_id == 0)
        {
                //New State as Child

                char choice_ = choice + 48;
                const char arg[] = {choice_};
                //new to ready Write mode
                close(fd_new_to_ready_procs[0]);                     //closing read end
                int pipe_copy_write = dup(fd_new_to_ready_procs[1]); //creating duplicate
                //typecasting of fd
                string s = to_string(pipe_copy_write);
                char *arg2 = new char[s.size() + 1];
                s.copy(arg2, s.size() + 1);
                arg2[s.size()] = '\0';

                //new to exit Write mode
                //type casting of fd
                close(fd_ready_to_exit_state[0]);
                int pipe_copy_write_ready_to_exit = dup(fd_ready_to_exit_state[1]);
                string s4 = to_string(pipe_copy_write_ready_to_exit);
                char *arg6 = new char[s4.size() + 1];
                s4.copy(arg6, s4.size() + 1);
                arg6[s4.size()] = '\0';


                execlp("./new", arg, arg2,arg6, NULL); //arg =  choice, arg2 =fd
                printf("\nExec failed while doinf Main child to new\n");
                exit(-1);
        }

        pid_t ready_proc_id = fork();
        if (ready_proc_id == 0 && new_proc_id != 0)
        {
                //Ready State Exec Child

                char choice_ = choice + 48;
                const char arg[] = {choice_};
                //new to ready, read mode
                //type casting of fd
                close(fd_new_to_ready_procs[1]);
                int pipe_copy_read_new_to_ready = dup(fd_new_to_ready_procs[0]);
                string s = to_string(pipe_copy_read_new_to_ready);
                char *arg2 = new char[s.size() + 1];
                s.copy(arg2, s.size() + 1);
                arg2[s.size()] = '\0';

                //ready to running Write mode
                //type casting of fd
                close(fd_ready_to_running_state[0]);
                int pipe_copy_write_ready_to_running = dup(fd_ready_to_running_state[1]);
                string s1 = to_string(pipe_copy_write_ready_to_running);
                char *arg3 = new char[s1.size() + 1];
                s1.copy(arg3, s1.size() + 1);
                arg3[s1.size()] = '\0';

                //running to ready, read mode
                //type casting of fd
                close(fd_running_to_ready_state[1]);
                int pipe_copy_read_running_to_ready = dup(fd_running_to_ready_state[0]);
                string s2 = to_string(pipe_copy_read_running_to_ready);
                char *arg4 = new char[s2.size() + 1];
                s2.copy(arg4, s2.size() + 1);
                arg4[s2.size()] = '\0';

                //block to ready read mode
                //type casting of fd
                close(fd_Blocked_to_ready_state[1]);
                int pipe_copy_read_block_to_ready = dup(fd_Blocked_to_ready_state[0]);
                string s3 = to_string(pipe_copy_read_block_to_ready);
                char *arg5 = new char[s3.size() + 1];
                s3.copy(arg5, s3.size() + 1);
                arg5[s3.size()] = '\0';

                execlp("./ready", arg, arg2, arg3, arg4, arg5, NULL); //arg = choice, arg2,arg3,arg4,arg5 = fd;
                printf("\nExec failed while main child to ready\n");
                exit(-1);
        }

        pid_t running_proc_id = fork();
        if (running_proc_id == 0 && new_proc_id != 0 && ready_proc_id != 0)
        {
                //Running State Exec Child
                char choice_ = choice + 48;
                const char arg[] = {choice_};

                //Ready to running, read mode
                //type casting of fd
                close(fd_ready_to_running_state[1]);
                int pipe_copy_read_ready_to_running = dup(fd_ready_to_running_state[0]);
                string s = to_string(pipe_copy_read_ready_to_running);
                char *arg2 = new char[s.size() + 1];
                s.copy(arg2, s.size() + 1);
                arg2[s.size()] = '\0';

                //running to ready Write mode
                //type casting of fd
                close(fd_running_to_ready_state[0]);
                int pipe_copy_write_running_ready = dup(fd_running_to_ready_state[1]);
                string s1 = to_string(pipe_copy_write_running_ready);
                char *arg3 = new char[s1.size() + 1];
                s1.copy(arg3, s1.size() + 1);
                arg3[s1.size()] = '\0';

                //Running to block Write mode
                //type casting of fd
                close(fd_Running_to_block_state[0]);
                int pipe_copy_write_running_to_block = dup(fd_Running_to_block_state[1]);
                string s2 = to_string(pipe_copy_write_running_to_block);
                char *arg4 = new char[s2.size() + 1];
                s2.copy(arg4, s2.size() + 1);
                arg4[s2.size()] = '\0';

                //running to exit Write mode
                //type casting of fd
                close(fd_running_to_exit_state[0]);
                int pipe_copy_write_running_to_exit = dup(fd_running_to_exit_state[1]);
                string s3 = to_string(pipe_copy_write_running_to_exit);
                char *arg5 = new char[s3.size() + 1];
                s3.copy(arg5, s3.size() + 1);
                arg5[s3.size()] = '\0';

                execlp("./running", arg, arg2, arg3, arg4, arg5, NULL);
                printf("\nExec failed while main child to running\n");
                exit(-1);
        }

        pid_t blocked_proc_id = fork();
        if (blocked_proc_id == 0 && new_proc_id != 0 && ready_proc_id != 0 && running_proc_id != 0)
        {
                //Blocked State Exec Child
                char choice_ = choice + 48;
                const char arg[] = {choice_};

                //running to block, read mode
                //type casting of fd
                close(fd_Running_to_block_state[1]);
                int pipe_copy_read_running_to_block = dup(fd_Running_to_block_state[0]);
                string s = to_string(pipe_copy_read_running_to_block);
                char *arg2 = new char[s.size() + 1];
                s.copy(arg2, s.size() + 1);
                arg2[s.size()] = '\0';

                //Blocked to ready Write mode
                //type casting of fd
                close(fd_Blocked_to_ready_state[0]);
                int pipe_copy_write_blocked_to_Ready = dup(fd_Blocked_to_ready_state[1]);
                string s1 = to_string(pipe_copy_write_blocked_to_Ready);
                char *arg3 = new char[s1.size() + 1];
                s1.copy(arg3, s1.size() + 1);
                arg3[s1.size()] = '\0';

                execlp("./blocked", arg, arg2, arg3, NULL); //arg = choice, arg2,arg3 = fd
                printf("\nExec failed while main child to block\n");
                exit(-1);
        }

        pid_t exit_proc_id = fork();
        if (exit_proc_id == 0 && new_proc_id != 0 && ready_proc_id != 0 && running_proc_id != 0 && blocked_proc_id != 0)
        {
                //Exit State Exec Child

                char choice_ = choice + 48;
                const char arg[] = {choice_};

                //running to exit, read mode
                close(fd_running_to_exit_state[1]);
                int pipe_copy_read_running_to_exit = dup(fd_running_to_exit_state[0]);
                string s = to_string(pipe_copy_read_running_to_exit);
                char *arg2 = new char[s.size() + 1];
                s.copy(arg2, s.size() + 1);
                arg2[s.size()] = '\0';
                
                //new to exit, read mode
                close(fd_ready_to_exit_state[1]);
                int pipe_copy_read_ready_to_exit = dup(fd_ready_to_exit_state[0]);
                string s1 = to_string(pipe_copy_read_ready_to_exit);
                char *arg3 = new char[s1.size() + 1];
                s1.copy(arg3, s1.size() + 1);
                arg3[s1.size()] = '\0';                

                execlp("./exit", arg, arg2,arg3, NULL); //arg =choice, arg2 = fd
                printf("\nExec failed while main child to exit\n");
                exit(-1);
        }

        return 0;
}
