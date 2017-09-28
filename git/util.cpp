#include<vector>
#include<string>
#include "util.h"
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

}

void GitHelper::setRecentBranches() {

}

void GitHelper::setCurrentStatus() { 

}
