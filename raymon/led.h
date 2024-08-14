#ifndef LED_H
#define LED_H

#include "../raylib/raylib.h" // Include Raylib

class LED
{
protected:
    Vector2 position;
    bool toggleState = false;

public:
    LED() {}
    LED(Vector2 pos) : position(pos) {}

    virtual void display() {}
    virtual void toggle()
    {
        toggleState = !toggleState;
    }
    virtual void off()
    {
        toggleState = false;
    }
    virtual void on()
    {
        toggleState = true;
    }

    virtual float ledLength()
    {
        return 0;
    };
};

class MonoLED : public LED
{
private:
    int radius = 9;
    int glare_step = 3;
    Color ON_COLOR;
    Color FADE_COLOR;

public:
    MonoLED() : LED() {
        ON_COLOR = RAYWHITE;
        FADE_COLOR = Fade(ON_COLOR, 0.3f);
    }
    MonoLED(Vector2 pos)
        : LED(pos) {
            ON_COLOR = RAYWHITE;
            FADE_COLOR = Fade(ON_COLOR, 0.3f);
        }
    MonoLED(Vector2 pos, Color led_color)
        : LED(pos), ON_COLOR(led_color) {
            FADE_COLOR = Fade(ON_COLOR, 0.3f);
        }

    void display() override
    {
        if (toggleState)
            DrawCircleV(position, radius, ON_COLOR);
        DrawCircleV(position, radius + glare_step, FADE_COLOR);
    }

    float ledLength() override {
        return 2 * (radius + glare_step);
    }
};

class MonoSquareLED : public LED
{
private:
    int radius = 15;
    int glare_step = 5;
    Color ON_COLOR;
    Color FADE_COLOR;

public:
    MonoSquareLED() : LED() {
        ON_COLOR = Fade(RAYWHITE, 0.8f);
        FADE_COLOR = Fade(ON_COLOR, 0.3f);
    }
    MonoSquareLED(Vector2 pos)
        : LED(pos) {
            ON_COLOR = Fade(RAYWHITE, 0.8f);
            FADE_COLOR = Fade(ON_COLOR, 0.3f);
        }
    MonoSquareLED(Vector2 pos, Color led_color)
        : LED(pos), ON_COLOR(Fade(led_color, 0.8f)) {
            FADE_COLOR = Fade(ON_COLOR, 0.3f);
        }

    void display() override
    {
        if(toggleState)
            DrawPoly(position, 4, radius, 45, ON_COLOR);
        DrawPoly(position, 4, radius + glare_step, 45, FADE_COLOR);
    }

    float ledLength() override {
        return (2*(radius + glare_step)) / 1.414;
    }
};

#endif // LED_H