#include <sys/wait.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main() {
    void showIDs(int, string);

    int pid = fork();

    if (pid == 0) {
	execl ("/bin/eclipse","eclipse", (char *)0);
        showIDs(pid, string("I am the child"));
    }
    else if (pid > 0) {
	waitpid(pid, 0, 0);

	sleep(15);
        showIDs(pid, string("I am the parent"));
    }
    else
        cout << "fork was not successful" << endl;

    return 0;
}

void showIDs(int childPid, string msg) {
    cout << msg << " (pid=" << getpid()
         << ", ppid=" << getppid()
	 << ", child=" << childPid << ")" << endl;
}
