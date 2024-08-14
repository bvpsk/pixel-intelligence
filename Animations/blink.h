#ifndef BLINK_ANIMATION_H
#define BLINK_ANIMATION_H

#include<iostream>
#include<string>

#include "animation.h"

class Blink : public Animation
{
private:
    /* data */
public:
    Blink() : Animation() {
        defineAnimation();
    }
    Blink(int px, int py) : Animation(px, py) {
        defineAnimation();
    }

                  void test(std::string msg) override
    {
        std::cout << "From Blink: " + msg << std::endl;
    }

    void defineAnimation() override{
        addFrame({
            "00000000",
            "00000000",
            "00000000",
            "00000000",
            "00000000",
            "00000000",
            "00000000",
            "00000000",
        }, 1);

        addFrame({
                     "11111111",
                     "11111111",
                     "11111111",
                     "11111111",
                     "11111111",
                     "11111111",
                     "11111111",
                     "11111111",
        },1);
    }

    // ~Blink();
};


#endif // BLINK_ANIMATION_H