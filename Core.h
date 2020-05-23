#include <iostream>
#include <list>
#include <algorithm>
#include "SensorEvent.h"
#include "AlarmType.h"

using namespace std;

class Core{
    private:
        bool alarmActivated;
        list<Sensor> activeSensorList;
        list<Sensor> knownSensorList;
        bool isAlarmReady();
    public:
        Core() {this->alarmActivated = false;};
        Core(list <Sensor> activeSensorList, list<Sensor> knownSensorList);
        bool addSensorToList(Sensor s, list<Sensor> sensorList);
        bool removeSensorFromList(Sensor s, list<Sensor> sensorList);
        void sensorEventHandler(SensorEvent se);
        void activateAlarm(AlarmType at);
        
};