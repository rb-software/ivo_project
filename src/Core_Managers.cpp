#include "Core_Managers.h"
#include "Log.h"
#include "Graphic_Engine.h"
#include "Customization.h"

Manager_Payments::Manager_Payments()
{
    DBG_PRINTF(INFO, "Manager_Payments constructor() ...");
}
Manager_Payments::~Manager_Payments()
{
    DBG_PRINTF(INFO, "~Manager_Payments destructor() ...");
}

bool Manager_Payments::init() const
{
    DBG_PRINTF(WARNING, std::string("Manager_Payments ") +
            std::string( __func__) +
            std::string("() ... ") +
            std::to_string(value));
}
ssize_t Manager_Payments::ignite() const
{
    DBG_PRINTF(WARNING, std::string("Manager_Payments ") +
            std::string( __func__) +
            std::string("() ... ") +
            std::to_string(value));
}
bool Manager_Payments::close() const
{
    DBG_PRINTF(WARNING, std::string("Manager_Payments ") +
            std::string( __func__) +
            std::string("() ... ") +
            std::to_string(value));
}

Manager_GraphicEngine::Manager_GraphicEngine()
{
    DBG_PRINTF(INFO, "Manager_GraphicEngine constructor() ...");

#ifdef OPERATING_SYSTEM
    if      ( OPERATING_SYSTEM == SYS_LINUX )
        gpuEngine = std :: make_unique<Linux_Graphic_Engine>();
    else if ( OPERATING_SYSTEM == SYS_X32 )
        gpuEngine = std :: make_unique<Linux_Graphic_Engine>();
        //gpuEngine = std :: make_unique<Windows_Graphic_Engine>();
    else if ( OPERATING_SYSTEM == SYS_X64 )
        gpuEngine = std :: make_unique<Linux_Graphic_Engine>();
        //gpuEngine = std :: make_unique<Windows_Graphic_Engine>();
    else
    {
        DBG_PRINTF(ERROR, "Invalid operation system.");
        gpuEngine = nullptr;
        exit(1);
    }
#else
    DBG_PRINTF(ERROR, "System not defined.");
#endif
}

Manager_GraphicEngine::~Manager_GraphicEngine()
{
    DBG_PRINTF(INFO, "~Manager_GraphicEngine destructor() ...");
}

bool Manager_GraphicEngine::init() const
{
    DBG_PRINTF(WARNING, std::string("Manager_GraphicEngine ") +
            std::string( __func__) +
            std::string("() ... ") +
            std::to_string(value));
        
    if ( SUCCEED != gpuEngine.get()->init() )
    {
        return FAIL;
    }
    
    if ( SUCCEED != gpuEngine.get()->ignite() )
    {
        return FAIL;
    }
    
    return true;
}
ssize_t Manager_GraphicEngine::ignite() const
{
    DBG_PRINTF(WARNING, std::string("Manager_GraphicEngine ") +
            std::string( __func__) +
            std::string("() ... ") +
            std::to_string(value));
}
bool Manager_GraphicEngine::close() const
{
    DBG_PRINTF(WARNING, std::string("Manager_GraphicEngine ") +
            std::string( __func__) +
            std::string("() ... ") +
            std::to_string(value));   
}