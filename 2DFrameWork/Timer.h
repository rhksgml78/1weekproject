#pragma once
class Timer : public Singleton<Timer>
{
private:

    chrono::steady_clock::time_point    currentTime;
    chrono::steady_clock::time_point    lastTime;
    UINT                                framePerSecond;
    UINT                                framePerSecondCount;
    float                               framePerSecondTimeElapsed;
    float                               worldTime;
   
public:
    float                               deltaTime;
    float                               deltaScaleTime;
    Timer();
    bool    GetTick(float& time, float interval);
    void    Chronometry(UINT lock = 60);
    float   GetDeltaScaleTime() { return deltaScaleTime; }
    float   GetDeltaTime()      { return deltaTime; }
    UINT    GetFramePerSecond() { return framePerSecond; }
    float   GetWorldTime()      { return worldTime; }
};
