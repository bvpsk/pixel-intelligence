#ifndef UI_H
#define UI_H

class UI
{
private:
    /* data */
public:
    UI(/* args */){}
};

class Grid
{
private:
    /* data */
public:
    Grid(/* args */){}
    // ~Grid();
};


class Element
{
private:
    /* data */
public:
    bool toUpdate = false;
    Element(/* args */){}
};

class Number : public Element
{
private:
    int value;
    int default_value = 0;
    bool isCounter = false;
    int step;
    int range[2];
    bool rangeCap[2] {false, false};
    int padding;
    bool paddingEnabled = false;

    void initializeRange(int min, int max)
    {
        rangeCap[0] = true;
        rangeCap[1] = true;
        range[0] = min;
        range[1] = max;
        if (min > 0)
            default_value = ((max - min) / 2);
    }

    int numDigits(){
        if(value == 0) return 1;
        int count = 0, val = value;
        while(val > 0){
            count ++;
            val /= 10;
        }
        return count;
    }

public:
    Number(): value(0) {}
    Number(int val): value(val){}
    Number(int val, bool counter): value(val), isCounter(counter){}
    Number(int val, bool counter, int stepVal, int min, int max) 
    : value(val), isCounter(counter), step(stepVal) {
        initializeRange(min, max);
    }
    Number(int val, bool counter, int stepVal, int min, int max, int padding_count)
        : value(val), isCounter(counter), step(stepVal) ,padding(padding_count)
    {
        initializeRange(min, max);
        paddingEnabled = true;
    }

    void setValue(int val)
    {
        value = val;
    }

    int getValue() { return value; }

    std::string getPaddedValue(){
        std::string strVal = "";

        int numZeroesToPad = padding - numDigits();

        for(int i = 0; i < numZeroesToPad; i++) strVal.append("0");
        strVal.append(std::to_string(value));

        return strVal;
    }

    void setStep(int val){step = val;}

    bool increment(){
        if(!isCounter) return false;
        value += step;
        if (rangeCap[1] && value > range[1])
        {
            value = range[0] + (value - range[1] - 1);
            return true;
        }
        return false;
    }

    bool decrement()
    {
        if (!isCounter)
            return false;
        value -= step;
        if (rangeCap[0] && value < range[0])
        {
            value = range[1] - (range[0] - value - 1);
            return true;
        }
        return false;
    }

    void reset()
    {
        if (!isCounter)
            return;
        value = default_value;
    }
};

class Text : public Element
{
private:
    
public:
    Text(/* args */){}
};



#endif // UI_H