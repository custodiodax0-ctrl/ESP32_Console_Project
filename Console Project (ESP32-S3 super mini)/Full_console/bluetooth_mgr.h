#ifndef BLUETOOTH_MGR_H
#define BLUETOOTH_MGR_H

#include <Arduino.h>

void initBluetoothManager();
bool isBluetoothEnabled();
void toggleBluetooth();

#endif // BLUETOOTH_MGR_H
