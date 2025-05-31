#include "DataLogger.h"

DataLogger::DataLogger(std::string& filename) {

    logFile.open(filename, std::ios::out | std::ios::binary);

    if (logFile.is_open() && logFile.tellp() == 0) {
        
        logFile << "MachineX,MachineY,AlphaIdeal,ThetaIdeal,ShootVelocityIdeal,ShakedTime,AlphaShaked,ThetaShaked,ShootVelocityShaked,IsHit\n";

        int type_count = 10;

        for (int i = 0; i < type_count; ++i)
            data[(ShootSlot)i] = -1;
    }
}

DataLogger::~DataLogger() {
   
    if (logFile.is_open()) {
        logFile.close();
    }
}

void DataLogger::InsertSlot(ShootSlot slot, double vel) {

    data[slot] = vel;
}

void DataLogger::LogData() {

    if (!logFile.is_open()) return;

    for (std::map<ShootSlot, double>::iterator it = data.begin(); it != data.end(); ++it) {

        if (it != std::prev(data.end()))
            logFile << it->second << ",";
        else
            logFile << it->second << "\n";

        it->second = -1;
    }
    logFile.flush();
}