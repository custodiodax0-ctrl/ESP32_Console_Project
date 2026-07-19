#include "bluetooth_mgr.h"

static bool g_btEnabled = false;

void initBluetoothManager() {
    g_btEnabled = false;
}

bool isBluetoothEnabled() {
    return g_btEnabled;
}

void toggleBluetooth() {
    g_btEnabled = !g_btEnabled;
}
