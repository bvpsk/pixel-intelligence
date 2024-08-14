#include "DisplayMonitor.h"
#include "raymon/RaylibMonitor.h"
#include "Programs/program.h"
#include "Programs/clock.h"
#include "Programs/animation_player.h"

int main()
{

    Program *program = new AnimationPlayer();

    // Instantiate RaylibMonitor using DisplayMonitor interface type
    DisplayMonitor *monitor = new RaylibMonitor(8, 8, LEDType::RedSquareLED);
    monitor->Initialize();

    program->Initialize(monitor);
    // std::cout << "Program Initialised" << std::endl;

    program->Run();
    // std::cout << "Program Ran" << std::endl;

    // Main loop
    // while (!WindowShouldClose())
    // {
    //     monitor->Update();
    //     monitor->Render();
    // }

    // Shutdown the display monitor
    monitor->Shutdown();

    // Clean up
    delete monitor;

    return 0;
}
