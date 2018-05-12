#ifndef OUTPUT_H
#define OUTPUT_H

#include "Output.h"

class IntervalOutput {
  public:
    IntervalOutput(DigitalOutput *output) {
      this->output = output;
    }
    void blink(unsigned int interval, unsigned int duration) {
      if (this->interval == interval && this->duration == duration && this->isActive) {
        return;
      }
      
      this->interval = interval;
      this->duration = duration;
      this->switchTime = 0;
      this->isActive = true;
    }
    void deactivate() {
      this->output->deactivate();
      this->switchTime = 0;
      this->isActive = false;
    }
    unsigned int getInterval() {
      return this->interval;
    }
    unsigned int getDuration() {
      return this->duration;
    }
    void update() {
      if (this->isActive) {
        unsigned int intervalTime = millis() - switchTime;
        if (!isOutputActive && (intervalTime < duration || intervalTime >= interval)) {
          this->output->activate();
          isOutputActive = true;
        }
        else if (isOutputActive && intervalTime >= duration) {
          this->output->deactivate();
          isOutputActive = false;
        }
  
        if (intervalTime >= interval) {
          this->switchTime = millis();
        }
      }
    }
  private:
    DigitalOutput *output;
    
    unsigned long switchTime = 0;
    unsigned int interval    = 0;
    unsigned int duration    = 0;
    bool isOutputActive      = false;
    bool isActive            = false;
};

#endif


