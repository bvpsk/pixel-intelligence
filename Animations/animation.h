#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <vector>

class Pixel
{
private:
    /* data */
    int red_value;
    int green_value;
    int blue_value;
public:
    Pixel(){}
    Pixel(int r, int g, int b): red_value(r), green_value(g), blue_value(b) {}
    Pixel(int val) : red_value(val), green_value(val), blue_value(val) {}

    int getFlatPixel(){
        if (red_value == 0 && green_value == 0 && blue_value == 0)
            return 0;
        return 1;
    }

    void set(int val){
        val = val > 0 ? 1 : 0;
        red_value = val;
        green_value = val;
        blue_value = val;
    }

    // ~Pixel();
};

class Frame
{
private:
    /* data */
    std::vector<std::vector<Pixel *>> pixel_matrix;
    std::vector<Pixel *> pixels;
    int duration;
    void initialiseVectors()
    {

        pixel_matrix.resize(numHorizontalPixels);
        for (int x = 0; x < numHorizontalPixels; x++)
        {
            pixel_matrix[x].resize(numVerticalPixels);
        }

        pixels.reserve(numHorizontalPixels * numVerticalPixels);
    }

    void loadPixels()
    {
        for (int i = 0; i < numHorizontalPixels; i++)
        {
            for (int j = 0; j < numVerticalPixels; j++)
            {
                Pixel *pixel = new Pixel(0);
                pixel_matrix[i][j] = pixel;
                pixels.push_back(pixel);
            }
        }
    }

public:
    int numHorizontalPixels, numVerticalPixels;
    int x_position, y_position;
    Frame(/* args */) {}
    Frame(int px, int py, int x_pos, int y_pos, int dur)
        : numHorizontalPixels(px), numVerticalPixels(py), x_position(x_pos), y_position(y_pos), duration(dur)
    {
        initialiseVectors();
        loadPixels();
    }
    Frame(int px, int py, int dur)
        : numHorizontalPixels(px), numVerticalPixels(py), x_position(0), y_position(0), duration(dur)
    {
        initialiseVectors();
        loadPixels();
    }

    int getDuration() {
        return duration;
    }

    Pixel* getPixel(int x, int y){
        return pixel_matrix[x][y];
    }

    void setPixel(int x, int y, Pixel *pixel)
    {
        pixel_matrix[x][y] = pixel;
    }

    void fillWithPixels(std::vector<std::vector<Pixel *>> frame_pixels)
    {
        for (int i = 0; i < frame_pixels.size(); i++)
        {
            std::vector<Pixel *> row = frame_pixels[i];
            for (int j = 0; j < row.size(); j++)
            {
                Pixel *pixel = frame_pixels[i][j];
                pixel_matrix[i][j] = pixel;
                pixels[i * numVerticalPixels + j] = pixel;
            }
        }
    }

    void fillFlat(std::vector<std::string> pixels)
    {
        for (int i = 0; i < numHorizontalPixels; i++)
        {
            std::string row = pixels[i];
            std::vector<int> values;
            for (char val : row)
                values.push_back(val - '0');
            for (int j = 0; j < numVerticalPixels; j++)
            {
                pixel_matrix[i][j]->set(values[j]);
            }
        }
    }

    // ~Frame();
};

class Animation
{
protected:
    std::vector<Frame *> frames;
    int currentFrame = -1, numFrames = 0;
    int numHorizontalPixels, numVerticalPixels;

public:
    Animation(/* args */) {}
    Animation(int px, int py) : numHorizontalPixels(px), numVerticalPixels(py) {}

    void addFrame(Frame *frame)
    {
        frames.push_back(frame);
        numFrames++;
    }

    void addFrame(std::vector<std::string> pixels, int duration)
    {
        Frame *frame = new Frame(numHorizontalPixels, numVerticalPixels, duration);
        frame->fillFlat(pixels);
        addFrame(frame);
    }

    void addFrame(std::vector<std::string> pixels, int x, int y, int duration)
    {
        Frame *frame = new Frame(numHorizontalPixels, numVerticalPixels, x, y, duration);
        frame->fillFlat(pixels);
        addFrame(frame);
    }

    Frame *nextFrame()
    {
        if (numFrames == 0)
            return nullptr;
        currentFrame++;
        if (currentFrame >= numFrames)
            currentFrame = 0;
        return frames[currentFrame];
    }

    virtual void test(std::string msg) {}

    virtual void defineAnimation() {}

    // ~Animation();
};

#endif // ANIMATION_H
