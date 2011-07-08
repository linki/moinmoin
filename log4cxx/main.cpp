// http://www.yolinux.com/TUTORIALS/Log4cxx.html
#include <stdlib.h>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

// Define static logger variable
log4cxx::LoggerPtr loggerMyMain(log4cxx::Logger::getLogger("main"));
log4cxx::LoggerPtr loggerFunctionA(log4cxx::Logger::getLogger("functionA"));

void functionA()
{
   LOG4CXX_INFO(loggerFunctionA, "Executing functionA.");
}

int main(int argc, const char **argv)
{
   // Load configuration file
   log4cxx::xml::DOMConfigurator::configure("Log4cxxConfig.xml");

   LOG4CXX_TRACE(loggerMyMain, "this is a debug message for detailed code discovery.");
   LOG4CXX_DEBUG(loggerMyMain, "this is a debug message.");
   LOG4CXX_INFO(loggerMyMain, "this is a info message, ignore.");
   LOG4CXX_WARN(loggerMyMain, "this is a warn message, not too bad.");
   LOG4CXX_ERROR(loggerMyMain, "this is a error message, something serious is happening.");
   LOG4CXX_FATAL(loggerMyMain, "this is a fatal message!!!");

   functionA();

   return EXIT_SUCCESS;
}
