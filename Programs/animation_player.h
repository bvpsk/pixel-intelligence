#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include <iostream>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds, etc.
#include <vector>
#include <ctime>

#include "program.h"
#include "../ui.h"
#include "../DisplayMonitor.h"

#include "../Animations/animation.h"
#include "../Animations/blink.h"
#include "../Animations/blink_more.h"

class AnimationPlayer : public Program
{
private:
    DisplayMonitor *display;
    Animation *animation;
    Frame *frame;

public:
    AnimationPlayer(/* args */){}
    // ~AnimationPlayer();

    std::vector<Element *> GetElements() override
    {
        std::vector<Element *> elements;

        // Push back the addresses of the member variables
        // elements.push_back();

        return elements;
    }

    void Initialize(DisplayMonitor *disp) override {
        display = disp;
        animation = new BlinkMore(8, 8);
    }
    void Run() override {
        frame = animation->nextFrame();
        int duration = frame->getDuration();
        
        display->readFrame(frame);
        display->Render();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        Run();
    }

 /*   void gameLoop()
    {
        const double targetFPS = 60.0;
        const double targetFrameTime = 1.0 / targetFPS;

        double lastTime = getCurrentTime();
        double accumulator = 0.0;

        while (gameIsRunning())
        {
            double currentTime = getCurrentTime();
            double deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            accumulator += deltaTime;

            while (accumulator >= targetFrameTime)
            {
                updateGameLogic(targetFrameTime); // Fixed time step update
                accumulator -= targetFrameTime;
            }

            renderFrame(); // Rendering might occur more frequently

            handleOtherTasks(); // Audio, input, networking, etc.

            double frameTime = getCurrentTime() - currentTime;
            if (frameTime < targetFrameTime)
            {
                sleep(targetFrameTime - frameTime); // Frame rate capping
            }
        }
    }
*/
    void Shutdown() override {}
};

#endif // ANIMATION_PLAYER_H