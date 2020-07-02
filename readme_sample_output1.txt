Input_1 contains the FCFS input
while output_1 contains the output of the Processing

In Processing_1a screen we can see that 

after entering the choice all processes read by the "New state"
are shown with their respective details and times
Now new write a signal and process to ready 
and ready after readding it write the process to the pipe for running 
meanwhile running starts working and accepts the process


In processing_1b Screen we can see that


some process continues it execution in running and after completing the processing 
it has been written to the pipe for exit
and meanwhile a signal back to the ready.
In ready process state it reads the signal meanwhile exit process has received the completed process
and print it
anter that line shows ready has written a process for running
running starts working , read process shows it
and after completing the processing write it to exit
exit process has received the completed process
and print it
Now ready starts working it reads signal which says send next but there is no next
so it waits if there is some in block but there is no one 
so after 25 seconds it terminates all and says that all processes have been processed