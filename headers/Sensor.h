#include "State.h"
#include "SensorTypes.h"
#include "Definitions.h"
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

class Sensor {
    private:
        int sensorID;
        State sensorState;
    public:
        Sensor() {};
        Sensor(int sensorID, State sensorState);
        int getSensorID();
        State getSensorState();
        void setSensorID(int sensorID);
        void setSensorState(State state);
        bool isSensorReady();
        virtual list<code> getCodeList() {return list<code>();}
        virtual void writeToFile(ofstream &out);
        virtual string getSensorInfo();
        /*virtual bool isSensorReady();*/
};