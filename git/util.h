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
class GitUtil{

    private:
        vector<string> allBranches;
        vector<string> recentBranches;
        vector<string> currentStatus;
        string currentBranch;
        void refresh();
    public:
        vector<string> getAllBranches();
        vector<string> getRecentBranches();
        vector<string> getCurrentStatus();
        string getCurrentBranch();
};

vector<string> getAllBranches();

#endif
