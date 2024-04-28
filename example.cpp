#include "coologger.hpp"

Coolog::Logger mainLogger("App");

#define DEBUG

#ifdef  DEBUG
#define APP_LOG_ERROR(x) \
        mainLogger.log(Coolog::LogLevel::error, x);         \
        std::cout << " | " << __FILE_NAME__ << ":" << __LINE__ << std::endl
#else
#define APP_LOG_ERROR(x)
#endif

int main() {
    Coolog::Logger subLogger("SubLogger");
    Coolog::Logger subLogger1;

    APP_LOG_ERROR("errr");

    mainLogger.log(Coolog::LogLevel::info, "This is info {}\n", 1);
    subLogger1.logln(Coolog::LogLevel::warning, "This is warning");
    subLogger.logBold(Coolog::LogLevel::error, "This {} + {}", "is an error", "bold");


    Coolog::quickLog("this is a {}", "quick log");

    return 0;
}
