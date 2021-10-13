#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) { 
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        cout << "I am the grandparent process [PID:" << getpid() << "]"<< endl;
        wait(nullptr);
    } else {
        pid_t grandchild_pid = fork(); // the child will create its own child process which will be the grandchild
        if(grandchild_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if(grandchild_pid > 0) {
            cout << "I am the parent process [PID:" << getpid() << "]"<< endl;
            wait(nullptr);
        } else {
            cout << "I am a grandchild process [PID:" << getpid() << "]"<< endl;
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}

/* OUTPUT:
I am the grandparent process [PID:522]
I am the parent process [PID:526]
I am a grandchild process [PID:527]
*/