// Main modules
#include "Log.h"
#include "System.h"

// Common modules
#include <iostream>
#include <memory>

#include <stdlib.h>

int main(void)
{
#ifdef OPERATING_SYSTEM
    DBG_PRINTF(INFO, "Compilation system defined.");
#else
    DBG_PRINTF(ERROR, "System not defined.");
    return -1;
#endif

    DBG_PRINTF(INFO, "Process started ...");

    // Modern solution
    bool status = false;
    std::unique_ptr<System> system = nullptr;

    try
    {
         system = std :: move(System::getInstance(status));
         
         DBG_PRINTF(INFO, "Object status: " + std::to_string(int(status)));
    }
    catch(std::string error)
    {
        DBG_PRINTF(INFO, "System issue: " + error);
        exit(1);
    }

    if(!system->run())
    {
        DBG_PRINTF(INFO, "Fatal error: ");
        exit(1);
    }

    DBG_PRINTF(INFO, "Process completed() ...");

    return 0;
}