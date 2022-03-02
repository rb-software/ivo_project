#ifndef CORE_MANGER_H
#define CORE_MANGER_H

// Base libraries
#include <iostream>
#include <memory>
#include <vector>

// Customized libraries
#include <Graphic_Engine.h>

class IFace_Graphic;

// General classes

class IFace_Manager
{
public:
    virtual bool init() const = 0;
    virtual ssize_t ignite() const = 0;
    virtual bool close() const = 0;
    virtual ~IFace_Manager() = default;
};

class Manager_Payments : public IFace_Manager
{
public:
    Manager_Payments();
    ~Manager_Payments();

    virtual bool init() const override;
    virtual ssize_t ignite() const override;
    virtual bool close() const override;

private:
    size_t value = 1;
};

class Manager_GraphicEngine : public IFace_Manager
{
public:
    Manager_GraphicEngine();
    ~Manager_GraphicEngine();

    virtual bool init() const override;
    virtual ssize_t ignite()  const override;
    virtual bool close() const override;

private:
    size_t value = 2;
    std :: unique_ptr<IFace_Graphic> gpuEngine = nullptr;
};

#endif // CORE_MANGER_H
