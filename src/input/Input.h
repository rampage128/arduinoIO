#ifndef INPUT_H
#define INPUT_H

class Input {
  public: 
    virtual boolean getState() = 0;
    virtual ~Input() {}
};

class AnalogInput : public Input {
  public:
    AnalogInput(int pinNumber, int compareMin, int compareMax, unsigned int debounceDuration = 20, int mode = INPUT) {
      pinMode(pinNumber, mode);
      this->pinNumber = pinNumber;
      this->compareMin = compareMin;
      this->compareMax = compareMax;
      this->debounceDuration = debounceDuration;
    }
    virtual boolean getState() { 
      boolean newPinValue = analogRead(this->pinNumber);
      if (newPinValue != this->desiredPinValue) {
        this->debounceTime = millis();
        this->desiredPinValue = newPinValue;
      }
    
      if (millis() - this->debounceTime > this->debounceDuration) {
        this->pinValue = this->desiredPinValue;
      }
    
      return this->pinValue >= this->compareMin && this->pinValue <= this->compareMax;
    }
  private:
    int pinNumber;
    int pinValue;
    int desiredPinValue;
    int compareMin;
    int compareMax;
    unsigned int debounceDuration;
    unsigned long debounceTime = 0;
};

class DigitalInput : public Input {
  public:
    DigitalInput(int pinNumber, unsigned int debounceDuration = 20, boolean compareMode = HIGH, int mode = INPUT) {
      pinMode(pinNumber, mode);
      this->pinNumber = pinNumber;
      this->compareMode = compareMode;
      this->debounceDuration = debounceDuration;
    }
    virtual boolean getState() { 
      boolean newPinValue = digitalRead(this->pinNumber);
      if (newPinValue != this->desiredPinValue) {
        this->debounceTime = millis();
        this->desiredPinValue = newPinValue;
      }
    
      if (millis() - this->debounceTime > this->debounceDuration) {
        this->pinValue = this->desiredPinValue;
      }
    
      return this->pinValue == this->compareMode;
    }
  private:
    int pinNumber;
    int pinValue;
    int desiredPinValue;
    boolean compareMode;
    unsigned int debounceDuration;
    unsigned long debounceTime = 0;
};

#endif
