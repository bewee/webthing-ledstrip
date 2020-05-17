#include "state.h"

#include <Arduino.h>
#include <EEPROM.h>
#include "ledstrip.h"

namespace state {

    struct { 
        uint64_t initialized;
        bool on;
        float brightness;
        uint8_t mode;
        ModeState modeState[ledstrip::numberModes];
    } s;

    bool &on = s.on;
    float &brightness = s.brightness;
    uint8_t &mode = s.mode;
    ModeState *modeState = s.modeState;

    void begin() {
        EEPROM.begin(sizeof(s));
        EEPROM.get(0, s);
        if (s.initialized != 0x7a5b89f04e651c6e) {
            s.initialized = 0x7a5b89f04e651c6e;
            s.on = true;
            s.brightness = 1;
            s.mode = 0;
            for (uint8_t i = 0; i < ledstrip::numberModes; i++)
                modeState[i] = {0xff0000, false, 0.9};
            save();
        }
    }

    void save() {
        EEPROM.put(0, s);
        EEPROM.commit();  
    }

    uint32_t colour() {
        return modeState[mode].colour;
    }

    bool random() {
        return modeState[mode].random;
    }

    float speed() {
        return modeState[mode].speed;
    }

    void colour(uint32_t c) {
        modeState[mode].colour = c;
    }

    void random(bool r) {
        modeState[mode].random = r;
    }

    void speed(float s) {
        modeState[mode].speed = s;
    }

}