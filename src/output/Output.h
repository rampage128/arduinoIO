#ifndef OUTPUT_H
#define OUTPUT_H

class Output {
  public:
    Output(int pinNumber, int normally = LOW) {
      this->pinNumber = pinNumber;
      this->normally = normally;
      pinMode(this->pinNumber, OUTPUT);
    }
    void deactivate() {
      this->set(this->normally);
    }
    boolean isActive() {
      return this->getState() != this->normally;
    }
    virtual int getState() = 0;
    virtual void set(int value) = 0;
    virtual ~Output() {};
  protected:
    int pinNumber;
    int normally;
};

class DigitalOutput : public Output {
  public:
    DigitalOutput(int pinNumber, int active = HIGH) : Output(pinNumber, !active) {
      // cannot call this in the base class :-(
      this->deactivate();
    }
    int getState() {
      return digitalRead(this->pinNumber);
    }
    void toggle(boolean state) {
      if (state && !this->isActive()) {
        this->activate();
      } 
      else if (!state && this->isActive()) {
        this->deactivate();
      }
    }
    void set(int value) {
      digitalWrite(this->pinNumber, value);
    }
    void activate() {
      this->set(!this->normally);
    }
};

class AnalogOutput : public Output {
  public:
    AnalogOutput(int pinNumber, int normally = LOW) : Output(pinNumber, normally) {
      // cannot call this in the base class :-(
      this->deactivate();
    }
    int getState() {
      return analogRead(this->pinNumber);
    }
    void set(int value) {
      analogWrite(this->pinNumber, value);
    }
};

#endif


