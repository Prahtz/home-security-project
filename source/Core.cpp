
#include "Core.h"
#include <stdlib.h>

Core::Core(list <Sensor> activeSensorList, list<Sensor> knownSensorList) {
    this->activeSensorList = activeSensorList;
    this->knownSensorList = knownSensorList;
};

//Return true if sensor added, false otherwise
bool Core::addSensorToList(Sensor s, list<Sensor> sensorList) {
    list<Sensor>::iterator it = std::find_if(sensorList.begin(), sensorList.end(), [&s](Sensor sensor) {return sensor.getSensorID() == s.getSensorID();});
    if(it == sensorList.end()) {
        sensorList.push_back(s);
        return true;
    }
    return false;
};

//Return true if sensor removed, false otherwise
bool Core::removeSensorFromList(Sensor s, list<Sensor> sensorList) {
    int listSize = sensorList.size();
    sensorList.remove_if([&s](Sensor sensor) {return sensor.getSensorID() == s.getSensorID();});
    if(listSize != sensorList.size()) 
        return true;
    return false;
};

//TEST
//Return true if alarm is activatable, false otherwise
bool Core::isAlarmReady(AlarmType at) {
    switch(at) {
        case COMPLETE:
            list<Sensor>::iterator it = std::find_if(activeSensorList.begin(), activeSensorList.end(), [](Sensor s) {return !s.isSensorReady();});
            if(it == activeSensorList.end())
                return true;
            break;
    }
    return false;
}

void Core::registerNewSensor() {
    Receiver receiver(PIN);
    thread newSensorThread(&Receiver::startReceiving, &receiver);
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    chrono::duration<double> elapsedSeconds = chrono::duration<double>(0);
    chrono::duration<double> secondsLimit = chrono::duration<double>(30);
    while(!receiver.isCodeAvailable() && elapsedSeconds < secondsLimit) {
        end = chrono::system_clock::now();
        elapsedSeconds = end - start;
    }
    if(elapsedSeconds < secondsLimit) {
        receiver.stopReceiving();
        newSensorThread.join();
        int codeReceived = receiver.getLastCodeReceived();
        cout<<codeReceived<<endl;
    }
    else {
        throw "No signals received";
    }

}

