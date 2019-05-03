// This is a dirty hack for the fcitx which will 
// sometimes be insane under Ubuntu 18.04+. 
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;
extern pid_t getPID(const string&);

#include "getUsage.hpp"

int main(int argc, char **argv) 
{
    int ret = 0;
    const string name("fcitx");
    while (1) {
        const pid_t pid = getPID(name);
        struct pstat before;
        get_usage(pid, &before);
        sleep(5);
        struct pstat after;
        get_usage(pid, &after);
        double ucpu_usage;
        double scpu_usage;
        calc_cpu_usage_pct(&after, &before, &ucpu_usage, &scpu_usage);
        if (ucpu_usage > 0.10 || scpu_usage > 0.10) {
            // it's time to terminate it!
            kill(pid, SIGKILL);
        }
        cout << "ucpu_usage = " << ucpu_usage << ", scpu_usage = " << scpu_usage << endl;
    }
    return ret;
}