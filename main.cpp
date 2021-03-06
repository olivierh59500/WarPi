#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "Manager/Manager.h"


using namespace std;

void check_root(){
    if(geteuid() != 0){
        cout << "You need root permissions to do this." << endl;
        exit(0);
    }
}

bool file_exists(const boost::filesystem::path path) {
    return boost::filesystem::is_regular_file(path);
}

void enable(){
    if (file_exists(boost::filesystem::path("/etc/init.d/warpi.sh"))) {
        cout << "WarPi should already run at boot" << endl;
        exit(0);
    }
    ofstream warpi("/etc/init.d/warpi.sh");
    warpi << "#!/bin/bash\n";
    warpi << "screen warpi start\n";
    warpi.close();
}

void disable(){
    if (!file_exists(boost::filesystem::path("/etc/init.d/warpi.sh"))) {
        cout << "WarPi already does not run at boot" << endl;
        exit(0);
    }
    remove("/etc/init.d/warpi.sh");
}

void usage(){
    cout << "Usage: ./warpi {option}" << endl;
    cout << "\tOptions:" << endl;
    cout << "\tstart\t\t-\tStarts the Program" << endl;
    cout << "\tenable\t\t-\tEnable running this program at boot" << endl;
    cout << "\tdisable\t\t-\tDisable running this program at boot" << endl;
    cout << "Got it? Ok. Bye." << endl;
    exit(0);
}

vector<string> get_arguments(char **argv, int argc) {
    vector<string> arguments;
    for (int i = 0; i < argc; i++) {
        arguments.push_back(argv[i]);
    }
    return arguments;
}

int main(int argc, char ** argv) {
    check_root();
    if (argc != 2) {
        usage();
    }
    vector<string> arguments = get_arguments(argv, argc);
    for (unsigned long i = 0; i < arguments.size(); i++) {
        if (arguments.at(i) == "start") {
            if (!file_exists("/etc/WarPi/config.json")) {
                // TODO: Check for --config and use user specified config file
                cout << "Need a config file to function properly." << endl;
                cout << "Creating the configuration file now. Please edit it to your needs." << endl;
                cout << "Config file should be located at: /etc/WarPi/config.json" << endl;
                exit(0);
            }
            Manager *manager = new Manager();
            manager->set_do_run(true);
            manager->run();
        }
        if (arguments.at(i) == "enable") {
            enable();
        }
        if (arguments.at(i) == "disable") {
            disable();
        }
    }
}

/*
 * TODO:
 * Argparsing && Config parsing
 * WiFi Authentication (Get IWLib encryption codes(ieee 802.11))  ---> Maybe result->b.mode == IW_AUTH_WPA_ENABLED
 *
 * Set scanning rate accordingly to moving speed ( eg. walking -> 2 seconds, driving -> 0.2 seconds )
 *
 * Network Object (eg.: Store information about if connected to network and IP ranges)
 * Network Function (eg.: Get Details for above Object, execute scans)
 *
 * Scanning and Spoofing
 *
 * WiFi Karma HotSpot (eg.: get most probed ssid -> open hotspot -> scan & poison)
 * Number Plate recognition (eg.: libpng -> take picture every x seconds -> openalpr -> plate, coords to db)
 *
 * Bluetooth (eg.: get near devices, put mac and services to db, act malicious)
 * GPS Map (eg.: Tangram Library for rendering)
 *
 */