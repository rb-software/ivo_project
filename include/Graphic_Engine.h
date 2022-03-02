#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H


// Customized libraries
#include <System.h>

// Base libraries
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <limits.h>
#include <unistd.h>

class IFace_Graphic
{
public:
    virtual bool    init() const = 0;
    virtual ssize_t ignite() const = 0;
    virtual bool    close() const = 0;

    virtual ~IFace_Graphic() = default;
};

class Linux_Graphic_Engine
        : public IFace_Graphic
{
public:
    Linux_Graphic_Engine();
    ~Linux_Graphic_Engine();
    
    virtual bool    init() const override;
    virtual ssize_t ignite() const override;
    virtual bool    close() const override;

private:
    std :: string   identity_key = "Linux";
};

class Windows_Graphic_Engine
        : public IFace_Graphic
{
public:
    Windows_Graphic_Engine();
    ~Windows_Graphic_Engine();

    virtual bool    init() const override;
    virtual ssize_t ignite() const override;
    virtual bool    close() const override;

private:
    std :: string   identity_key = "Windows";
};

class Android_Graphic_Engine
        : public IFace_Graphic
{
public:
    Android_Graphic_Engine();
    ~Android_Graphic_Engine();

    virtual bool    init() const override;
    virtual ssize_t ignite() const override;
    virtual bool    close() const override;

private:
    std :: string   identity_key = "Android";
};

#endif // GRAPHIC_ENGINE_H
