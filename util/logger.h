#ifndef __UTIL_LOGGER_H_
#define __UTIL_LOGGER_H_

#include <fstream>
#include <string>
using std::endl;
using std::string;
class Logger
{
    bool logEnabled;
    std::ofstream lout;
    static Logger *s_instance;
    Logger(){}
  public:
	void log(string message);
	void log(int message);
    void enableLogs();
    static Logger* instance();
/*    static Logger* instance(){
        if (!s_instance)
            s_instance = new Logger;
        return s_instance;
    }*/

};
#endif
