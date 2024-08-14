#ifndef DISPLAY_MONITOR_H
#define DISPLAY_MONITOR_H

#include <iostream>

#include "Animations/animation.h"

class DisplayMonitor
{
public:
    virtual ~DisplayMonitor() {}

    // Pure virtual methods that need to be implemented by derived classes
    virtual void Initialize(){}
    virtual void Update(){}
    virtual void Render(){}
    virtual void Shutdown(){}
    virtual void off() {}
    virtual void on() {}
    virtual void readFrame(Frame*) {}
    virtual void test(std::string) {}
};

#endif // DISPLAY_MONITOR_H
