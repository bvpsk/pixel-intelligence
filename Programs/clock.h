#ifndef CLOCK_PROGRAM_H
#define CLOCK_PROGRAM_H

#include <iostream>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds, etc.
#include <vector>
#include <ctime>

// #include "../raylib/raylib.h" // Include Raylib
#include "program.h"
#include "../ui.h"
#include "../DisplayMonitor.h"

class Clock : public Program
{
private:
    DisplayMonitor *display;
    Number *hours;
    Number *minutes;
    Number *seconds;
    Text *hm_split;
    Text *meridian;
    bool meridian_flag;

public:
    Clock(){}

    std::vector<Element *> GetElements() override{
        std::vector<Element *> elements;

        // Push back the addresses of the member variables
        elements.push_back(hours);
        elements.push_back(minutes);
        elements.push_back(seconds);
        elements.push_back(hm_split);
        elements.push_back(meridian);

        return elements;
    }

    void setTime(){
        std::time_t now = std::time(nullptr);
        std::tm *localTime = std::localtime(&now);

        int hour = localTime->tm_hour;
        int minute = localTime->tm_min;
        int second = localTime->tm_sec;

        meridian_flag = (hour < 12);

        // Convert hour to 12-hour format
        hour = hour % 12;
        if (hour == 0)
            hour = 12; // 12 AM or 12 PM

        // hour = 11, minute = 59, second = 50;

        hours = new Number(hour, true, 1, 1, 12, 2);
        minutes = new Number(minute, true, 1, 0, 59, 2);
        seconds = new Number(second, true, 1, 0, 59, 2);
    }

    void Initialize(DisplayMonitor* disp) override {
        display = disp;
        setTime();
    }
    void Run() override {
        int delay = 1;
        display->Render();

        std::string result = hours->getPaddedValue() + ":" +
                             minutes->getPaddedValue() + ":" +
                             seconds->getPaddedValue() + " " +
                             (meridian_flag ? "AM" : "PM");
        std::cout << result << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(delay));

        if(seconds->increment()){
            if(minutes->increment()){
                if(hours->increment()){
                }
                if (hours->getValue() == 12)
                {
                    meridian_flag = !meridian_flag;
                }
            }
        }

        Run();
    }
    void Shutdown() override {
        delete hours;
        delete minutes;
        delete seconds;
    }
};



#endif // CLOCK_PROGRAM_H