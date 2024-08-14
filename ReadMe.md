g++ -std=c++11 -o DMD main.cpp -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib

export LIBRARY_PATH=/opt/homebrew/Cellar/raylib/5.0/lib:$LIBRARY_PATH


g++ -std=c++11 -o DMD main.cpp -lraylib

## Ideas

[] Add functionality in Animation class to repeat frames
[] enhance readFrame method in RaylibMonitor to dynamically determine
    the pixel to led converter, use frame (x, y) coordinates as well
[] RGB LED
[] PWM support for Animations 
[] PWM support for LEDs
[] On Demand Pixel rendering in RaylibMonitor
[] Pixel Upscaling and Downscaling
[] Async runner for looping with frame capping
[] Animation loader from text file
[] Frame arithmetics(Addition of two frames e.t.c..)
[] Loading to MCUs directly from desktop application
[]
[]