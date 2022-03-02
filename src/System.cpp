#include "System.h"
#include "Log.h"

#include <cassert>

System::System()
{
    DBG_PRINTF(INFO, "constructor() ...");

    module.push_back(std::make_unique<Manager_Payments>());
    module.push_back(std::make_unique<Manager_GraphicEngine>());
}

System::~System()
{
    DBG_PRINTF(INFO, "destructor() ...");
}

bool System::run()
{
    DBG_PRINTF(INFO, "System started ...");

    for(auto& it : module)
        it->init();

    return true;
}

std :: unique_ptr<System>& System::getInstance(bool& status)
{
    static std::unique_ptr<System> sys = nullptr;
    static bool flag = false;
    status = flag;
    
    if(!flag)
    {
        DBG_PRINTF(INFO, "Created ...");
        flag = true;
        sys = std::make_unique<System>();

        if(!sys)
        {
            std::string error(__func__);
            error += " error";
            throw error;
        }
        status = flag;
        return sys;
    }
    else
    {
        DBG_PRINTF(ERROR, "Returned ...");

        if(!sys)
        {
            std::string error(__func__);
            error += " error";
            throw error;
        }

        return sys;
    }
}

System* System::getInstance()
{
    if(!system)
    {   
        DBG_PRINTF(INFO, "System instance created ...");
        return new System;
    }
    else
    {
        DBG_PRINTF(INFO, "System instance created ...");
        return system;
    }
}