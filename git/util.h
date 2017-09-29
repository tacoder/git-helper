#ifndef __GIT_UTIL_H_
#define __GIT_UTIL_H_

#include<vector>
#include<iostream>
using std::string;
using std::vector;
/*
 * Util that handles connecting to git and getting repo information
 *
 */
class GitHelper {
    private:
        vector<string> branches;
        vector<string> recentBranches;
        vector<string> currentStatus;
        void setAllBranches();
        void setRecentBranches();
        void setCurrentStatus();
        static GitHelper *s_instance;
        GitHelper();
    public:
        static GitHelper* getInstance();
        vector<string> getAllBranches();
        vector<string> getCurrentStatus();
};


#endif
