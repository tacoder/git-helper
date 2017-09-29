#include<vector>
#include<string>
#include "util.h"
#include "../util/system.h"
#include "../util/logger.h"
using std::vector;
using std::string;
GitHelper *GitHelper::s_instance;


GitHelper *GitHelper::getInstance(){
    if (!s_instance)
        s_instance = new GitHelper;
    return s_instance;
}

GitHelper::GitHelper() {
    setAllBranches();
    setRecentBranches();
    setCurrentStatus();
}

vector<string> GitHelper::getAllBranches(){
    return *(new vector<string>(branches));
}

void GitHelper::setAllBranches() {
    string command = "git branch -a | sed 's/..\\(.*\\)/\\1/g' | grep -v '\\->' | sed 's/remotes\\/origin\\/\\(.*\\)/\\1/g' | sort|uniq";
    string commandLocalBranches = "git branch | sed 's/..\\(.*\\)/\\1/g'";
    string commandRemoteBranches = "git branch -r | grep -v 'HEAD ->' |sed 's/.*origin\\/\\(.*\\)/\\1/g'";
    branches = split(GetStdoutFromCommand(command),'\n');
}

void GitHelper::setRecentBranches() {

}

void GitHelper::setCurrentStatus() { 
    string command = "git status";
    currentStatus = split(GetStdoutFromCommand(command),'\n');
}
