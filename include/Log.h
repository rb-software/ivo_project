#ifndef LOG_H
#define LOG_H

#include <string>
#include <chrono>

enum LOG_LEVEL { INFO = 1, ERROR , WARNING };

#define ENABLED

#ifdef ENABLED
  #define DBG_PRINTF(mode, sText)                                                                                                                                    \
      if(mode == INFO)           Log::getInstance()->info(std::string(__FILE__) + '|' + std::string(__func__)+ "():" + std::to_string(__LINE__) + "| " + sText);     \
      else if(mode == ERROR)     Log::getInstance()->error(std::string(__FILE__) + '|' + std::string(__func__) + "():" + std::to_string(__LINE__) + "| " + sText);   \
      else if(mode == WARNING)   Log::getInstance()->warning(std::string(__FILE__) + '|' + std::string(__func__) + "():" + std::to_string(__LINE__) + "| " + sText); \
      else                       exit(1);
#else
  #define DBG_PRINTF(mode, sText)
#endif

#define LOG_SPECIAL *(Log::getInstance())
#define LOG Log::getInstance()

// Singleton logging class
class Log{
public:
  Log();
  
  void info(const std::string& sText);
  void warning(const std::string& sText);
  void error(const std::string& sText);
  
  Log& operator<<(const std::string& sText);
  Log& operator<<(const float& sText);
  
  static Log* getInstance();
  
private:
  static Log* m_pThis_Log;
  static std::ostream& m_Log_buf;
  static std::chrono::system_clock::time_point startTime;
};

#endif /* LOG_H */
