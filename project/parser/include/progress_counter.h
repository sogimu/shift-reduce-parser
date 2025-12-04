#pragma once

#include <cstdint>

class ProgressCounter
{
public:
  ProgressCounter(size_t max_steps)
    : mMaxSteps{ max_steps }
  {
  }
  void Step()
  {
    if( mMadeSteps < mMaxSteps )
        ++mMadeSteps;
  }

  void Reset()
  {
    mMadeSteps = 0;
  }
  double Status() const
  {
    if( mMaxSteps == 0 )
      return 0;
    double result = static_cast<double>(mMadeSteps) / static_cast<double>(mMaxSteps);
    return result;
  }
private:
  size_t mMadeSteps = 0;
  size_t mMaxSteps = 0;
};

