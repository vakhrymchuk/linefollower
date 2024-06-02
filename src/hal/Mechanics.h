#pragma once


class Mechanics
{
public:

protected:
public:
    virtual void run(int leftSpeed, int rightSpeed) = 0;

protected:
    int getMaxPwm() const
    {
        return 255;
    }

private:
};
