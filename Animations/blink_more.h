#ifndef BLINK_MORE_ANIMATION_H
#define BLINK_MORE_ANIMATION_H

#include<iostream>
#include<string>

#include "animation.h"

class BlinkMore : public Animation
{
private:
    /* data */
public:
    BlinkMore() : Animation() {
        defineAnimation();
    }
    BlinkMore(int px, int py) : Animation(px, py) {
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
                     "10000001",
                     "10000001",
                     "10000001",
                     "10000001",
                     "10000001",
                     "10000001",
                     "11111111",
                 },
                 1);
        addFrame({
                     "11111111",
                     "11000001",
                     "10100001",
                     "10010001",
                     "10001001",
                     "10000101",
                     "10000011",
                     "11111111",
                 },
                 1);
    }

    // ~BlinkMore();
};


#endif // BLINK_MORE_ANIMATION_H