#include <dirent.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

pid_t getPID(const string& name) {
   pid_t pid = -1;
   const char* procDir = "/proc";
   auto dir = opendir(procDir);
   
   if (dir) {
      struct dirent *dirEntry = nullptr;
      // go through the whole directory entry
      while ((dirEntry = readdir(dir)) != nullptr) {
         if (strncmp(dirEntry->d_name, ".", 1) == 0 || 
             strncmp(dirEntry->d_name, "..", 2) == 0) {
               continue;
         }
         // get the pid here (check if it is numeric)
         if (sscanf(dirEntry->d_name, "%d", &pid) == 1) {
            // valid pid, open stat 
            // A maximum of 4 million PIDs should be enough for a while.
            // [NOTE: PID/TIDs are limited to 2^29 ~= 500+ million, see futex.h.]
            // so the statPath length should be length of "/proc" + [PID] + "/stat" = 5+7+5=17
            const size_t statPathLen = strlen(procDir) + 7 + strlen("/stat");
            char statPath[statPathLen];
            sprintf(statPath, "%s/%d/stat", procDir, pid);
            // Do we need to close the file manually?
            // NO - This is what RAII is for, let the destructor do its job. 
            // There is no harm in closing it manually, but it's not the C++ way, 
            // it's programming in C with classes.
            // If you want to close the file before the end of a function you can 
            // always use a nested scope.
            // In the standard (27.8.1.5 Class template basic_ifstream), ifstream 
            // is to be implemented with a basic_filebuf member holding the actual 
            // file handle. It is held as a member so that when an ifstream object 
            // destructs, it also calls the destructor on basic_filebuf. 
            // And from the standard (27.8.1.2), that destructor closes the file.
            ifstream statInfo(statPath);
            string stat;
            getline(statInfo, stat);
            string currProcName;
            int i = 0;
            while (i < stat.length() && stat[i] != '(') 
               i++;
            i++;
            while (i < stat.length() && stat[i] != ')') {
               currProcName.push_back(stat[i]);
               i++;
            }

            if (currProcName == name) 
               break;
         }
      }
   }
   closedir(dir);
   return pid;
}