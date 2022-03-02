#ifndef SYSTEM_H
#define SYSTEM_H

// Specialized modules
#include <Core_Managers.h>

// Common modules
#include <iostream>
#include <memory>
#include <string>
#include <vector>

//*** Main Singleton ***//
class IFace_Manager;

class System // IPC management
{
public:
    System();
    ~System();

    static System* getInstance();
    static std :: unique_ptr<System>& getInstance(bool& status);

    bool run();

private:
    constexpr static System* system = nullptr;

    // Main system module managers
    std :: vector<std :: unique_ptr<IFace_Manager>>module;
};


#endif // SYSTEM_H
