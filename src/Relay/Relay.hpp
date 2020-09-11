#ifndef RELAY_HPP
#define RELAY_HPP

class Relay {
    public:
        Relay(int pin);

        bool isTurnedOn();
        void turnOn();
        void turnOff();

    private: 
        // Relays on the board are activated with a LOW signal, deactivated with HIGH
        const int ON_STATE{LOW};
        const int OFF_STATE{HIGH};
        const int pin;
        int state{OFF_STATE};
};

#endif