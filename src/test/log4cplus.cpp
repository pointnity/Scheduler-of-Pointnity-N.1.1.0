#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <iomanip>
using namespace std;
using namespace log4cplus;
int
main()
{
BasicConfigurator config;
config.configure();
Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("logger"));
LOG4CPLUS_WARN(logger, "This is"
<< " a reall"
<< "y long message." << endl
<< "Just testing it out" << endl
<< "What do you think?");
LOG4CPLUS_WARN(logger, "This is a bool: " << true);
LOG4CPLUS_WARN(logger, "This is a char: " << 'x');
