#include "extsrc.h"

Log* Log::m_pThis_Log = NULL;
std::ostream& Log::m_Log_buf = std::cout;
std::chrono::system_clock::time_point Log::startTime = std::chrono::system_clock::now();

Log::Log()
{
  std::chrono::system_clock::time_point current = std::chrono::system_clock::now();

  m_Log_buf << std::endl << "TIME: " 
            << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(current-startTime).count() 
            << " [INIT     ] Initialized logging Singleton class ..." ;
}

Log* Log::getInstance()
{
  if (m_pThis_Log == NULL)
  {
    m_pThis_Log = new Log();
  }
  return m_pThis_Log;
}

Log& Log::operator<<(const std::string& sText)
{
  std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
  
  m_Log_buf << std::endl << "TIME: " 
            << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(current-startTime).count()
            << " [SPECIAL  ] " << sText;
  
  return *this;
}

Log & Log::operator<<(const float & value)
{
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();

	m_Log_buf << std::endl << "TIME: "
		<< std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(current - startTime).count()
		<< " [SPECIAL  ] " << value;

	return *this;
}

void Log::error(const std::string& sText)
{
  std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
  
  m_Log_buf << std::endl << "TIME: " 
            << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(current-startTime).count()
            << " [ERROR    ] " << sText;
}

void Log::info(const std::string& sText)
{
  std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
  
  m_Log_buf << std::endl << "TIME: " 
            << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(current-startTime).count()
            << " [INFO     ] " << sText;
}

void Log::warning(const std::string& sText)
{
  std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
  
  m_Log_buf << std::endl << "TIME: " 
            << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(current-startTime).count()
            << " [WARNING  ] " << sText;
}
