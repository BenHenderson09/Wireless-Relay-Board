#ifndef RELAY_HPP
#define RELAY_HPP

class Relay {
    public:
        Relay(int pin);

        bool isTurnedOn();
        void turnOn();
        void turnOff();

    private:
        const int ON_STATE{LOW};
        const int OFF_STATE{HIGH};
        const int pin;
        int state{OFF_STATE};
};

#endif