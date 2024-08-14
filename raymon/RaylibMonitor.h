#ifndef RAYLIB_MONITOR_H
#define RAYLIB_MONITOR_H

#include <iostream>
#include <vector>

#include "../DisplayMonitor.h"
#include "../raylib/raylib.h" // Include Raylib
#include "led.h"
#include "../Animations/animation.h"

enum class LEDType
{
    WhiteLED,
    RedLED,
    BlueLED,
    GreenLED,
    RedSquareLED
};

class RaylibMonitor : public DisplayMonitor
{
private:
    int numHorizontalPixels;
    int numVerticalPixels;
    int screenWidth;
    int screenHeight;
    // LED ***led_matrix; // [32][16];
    std::vector<std::vector<LED *>> led_matrix;
    std::vector<LED *> leds;
    // LED **leds; // [32 * 16];
    int padding = 2;
    LEDType ledType;

    LED *CreateLED(LEDType type, Vector2 pos)
    {
        switch (type)
        {
        case LEDType::WhiteLED:
            return new MonoLED(pos);
        case LEDType::RedLED:
            return new MonoLED(pos, RED);
        case LEDType::BlueLED:
            return new MonoLED(pos, BLUE);
        case LEDType::GreenLED:
            return new MonoLED(pos, GREEN);
        case LEDType::RedSquareLED:
            return new MonoSquareLED(pos, RED);
        default:
            return new MonoLED(pos); // Or throw an exception if needed
        }
    }

    void initialiseArrays(){
        // // Dynamically allocate memory for the 2D LED matrix
        // led_matrix = new LED **[numHorizontalPixels];
        // for (int i = 0; i < numHorizontalPixels; i++)
        // {
        //     led_matrix[i] = new LED *[numVerticalPixels];
        // }

        // // Dynamically allocate memory for the 1D LED array
        // leds = new LED *[numHorizontalPixels * numVerticalPixels];

        led_matrix.resize(numHorizontalPixels);
        for (int x = 0; x < numHorizontalPixels; x++)
        {
            led_matrix[x].resize(numVerticalPixels);
        }

        leds.reserve(numHorizontalPixels * numVerticalPixels);
    }

public:
    // RaylibMonitor() : screenWidth(830), screenHeight(600) {}
    RaylibMonitor(int px, int py) : numHorizontalPixels(px), numVerticalPixels(py), ledType(LEDType::WhiteLED){
        initialiseArrays();
    }
    RaylibMonitor(int px, int py, LEDType lt) : numHorizontalPixels(px), numVerticalPixels(py), ledType(lt) {
        initialiseArrays();
    }

    void Initialize() override
    {

        LED *sampleLED = CreateLED(ledType, Vector2{0, 0});
        int ledLength = sampleLED->ledLength();
        delete sampleLED;

        screenWidth = 0;
        screenHeight = 0;
        // Setup LEDs
        int starting_point = 20;
        float x = starting_point, y = starting_point;
        for(int i = 0; i < numHorizontalPixels; i++){
            y = starting_point;
            for(int j = 0; j < numVerticalPixels; j++){
                Vector2 pos = Vector2{x, y};
                LED *led = CreateLED(ledType, pos);
                led_matrix[i][j] = led;
                // leds[j + (i * numVerticalPixels)] = led_matrix[i][j];
                leds.push_back(led);
                y = y + padding + ledLength;
            }
            x = x + padding + ledLength;
            screenWidth = x;
            screenHeight = y;
        }

        SetTraceLogLevel(LOG_WARNING);
        std::string windowTitle = std::to_string(numHorizontalPixels) + " x " + std::to_string(numVerticalPixels) + " DOT DISPLAY MODULE";
        screenWidth -= (starting_point / 2);
        screenHeight -= (starting_point / 2);
        InitWindow(screenWidth, screenHeight, windowTitle.c_str());

        SetWindowPosition(100, 100);
        // SetTargetFPS(2);
    }

    void Update() override
    {
        // Handle updates (e.g., input handling)
        on();
        // for (LED *led : leds) led->toggle();
    }

    void Render() override
    {
        Color BG_COLOR = Fade(Color{10, 10, 10, 10}, 0.9);

        BeginDrawing();

        ClearBackground(BG_COLOR);
        for (LED *led : leds)
        {
            led->display();
        }

        EndDrawing();
    }

    void Shutdown() override
    {
        CloseWindow(); // Close the window and OpenGL context
    }

    void off() override{
        for (LED *led : leds)
        {
            led->off();
            // led.display();
        }
    }

    void on() override
    {
        for (LED *led : leds)
        {
            led->on();
            // led.display();
        }
    }

    void readFrame(Frame* frame) override{
        for(int i = 0; i < frame->numHorizontalPixels; i++){
            for (int j = 0; j < frame->numHorizontalPixels; j++)
            {
                Pixel *pixel = frame->getPixel(i, j);
                LED *led = led_matrix[i][j];
                pixel->getFlatPixel() == 1 ? led->on() : led->off();
            }
        }
    }

    void test(std::string msg) override {
        std::cout << "Able to Access: " + msg << std::endl;
    }
};

#endif // RAYLIB_MONITOR_H
