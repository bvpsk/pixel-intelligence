#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include "../DisplayMonitor.h"
#include "../ui.h"

class Program
{
public:
    virtual ~Program() {}

    virtual std::vector<Element *> GetElements() { return std::vector<Element *>(); }

    // Pure virtual methods that need to be implemented by derived classes
    virtual void Initialize(DisplayMonitor* display){}
    virtual void Run(){}
    virtual void Shutdown(){}
};

#endif // PROGRAM_H
