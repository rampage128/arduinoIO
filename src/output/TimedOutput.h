#ifndef OUTPUT_H
#define OUTPUT_H

#include "Output.h"

class TimedOutput {
  public:
    TimedOutput(Output *output) {
      this->output = output;
    }
    void set(int value, unsigned int duration) {
      this->switchTime = millis();
      this->switchDuration = duration;
      this->output->set(value);
    }
    boolean isActive() {
      return this->output->isActive();
    }
    boolean getState() {
      return this->output->getState();
    }
    void update() {
      if (millis() - switchTime >= this->switchDuration) {
        this->output->deactivate();
      }
    }
  private:
    Output *output;
    
    unsigned long switchTime = 0;
    unsigned int switchDuration = 0;
};

#endif


