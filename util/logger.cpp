#include "logger.h"
void Logger::log(string message){
	if(Logger::logEnabled) lout<<message<<endl;
}

 void Logger::log(int message){
     if(Logger::logEnabled) lout<<message<<endl;
 }

void Logger::enableLogs(){
	logEnabled = true;
	lout.open("git-helper.log", std::ios_base::app);
}

Logger *Logger::s_instance;

Logger* Logger::instance(){
	if (!s_instance)
    	s_instance = new Logger;
      return s_instance;
}


