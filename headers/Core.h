#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>
#include <algorithm>
#include <thread>
#include <future>
#include <stdlib.h>
#include <sstream>
#include <map>
#include "EventHandler.h"
#include "SensorTypes.h"
#include "Action.h"
#include "Exceptions.h"
#include "TCPComm.h"
#include "FirebaseOperation.h"
#include "ClientUpdater.h"
#include "Logger.h"

using namespace std;

class Core{
    private:
        atomic<bool> abortProcedure;
        list<Sensor*> knownSensorList;
        map<code, pair<Action, Sensor*>*> codeMap;
        Receiver receiver;
        Transmitter transmitter;
        FirebaseMessagesHandler firebaseMessagesHandler;
        EventHandler eventHandler;
        thread receiverThread, eventHandlerThread, transmitterThread, firebaseMessagesHandlerThread;
        list<string> messageBuffer;



        void setupKnownSensors();
        void setupTokenList();
        void updateTokenList();
        void updateCodeMap(DoorSensor* ds);
        int getNewSensorID();

        void registerCloseCode(TCPComm* tcpComm, DoorSensor *ds);
        void registerOpenCode(TCPComm* tcpComm, DoorSensor *ds);
        void registerSensorName(TCPComm* tcpComm, DoorSensor *ds);

    public:
        Core(); 
        static list<string> tokenList;
        bool addSensorToList(Sensor* s);
        bool removeSensorFromList(Sensor* s);
        void activateAlarm(TCPComm* tcpComm);
        void deactivateAlarm(TCPComm* tcpComm);
        void sensorList(TCPComm* tcpComm);
        void updateBattery(TCPComm* tcpComm, string message);
        void removeSensor(TCPComm* tcpComm, string message);
        void deactivateSensor(TCPComm* tcpComm, string message);
        void activateSensor(TCPComm* tcpComm, string message);
        bool isAlarmReady();
        void registerNewDoorSensor(TCPComm* tcpComm);
        void writeSensorToFile(Sensor* s);
        void handleFirebaseToken(string token);
};