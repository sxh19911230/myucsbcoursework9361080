#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
int main ()
{
 pid_t pid;
 int i;

 cout << "My process id = " << getpid() << endl;

 for (i = 1; i <= 4; i++)
  switch ( pid = fork() ) {
  case -1:
    cout << "Error in fork"<<endl;

  case 0:
    cout << "Child process: My process id = " << getpid() << endl;
    cout << "Child process: Value returned by fork() = " << pid << endl;
    return 0;

  default:
    cout << "Parent process. My process id = " << getpid() << endl;
    cout << "Parent process. Value returned by fork() = " << pid << endl;

   if (wait(NULL) == -1) 
    cout << "Error in wait"<< endl;

 }  
 return 0;
 }
