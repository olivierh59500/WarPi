#WarPi<br />
[![Build Status](http://eberlein.io:8080/buildStatus/icon?job=WarPi)](http://eberlein.io:8080/job/WarPi)
##Status:
New Version is finished. <br />
Just doing some final debugging on different devices. <br />

##Current Task:<br />
Get Encryption Type (looking through airodump-ng)<br />

##Current Problems:
I personally can't compile rapidjson on my Raspberry Pi 2 & 3. Having an open issue. If you get the same problem I will change to some other JSON Library. <br />

###What is it?<br />
Basically a All-in-One Box for your Car.<br />
###Sounds sketchy. Whats exactly in it?<br />
Short description of all files:<br />
#####WarPi/Client:<br />
Client, which shall connect to the main Server to synchronize its logs and get new commands. <br />
#####WarPi/Database:<br />
For the connection with the Eve REST API. (Storage of GPS/WiFi Logs)<br />
#####WarPi/Eve:<br />
Small Python thread, which gets called by the Database Class. It just provides the Eve REST API.<br />
#####WarPi/GPS:<br />
Used for the overall GPS functionality.<br />
#####WarPi/Manager:<br />
Controls the whole thingy.<br />
#####WarPi/WiFi:<br />
Used for the overall WiFi functionality.<br />
###Ok, But what do I need to run it?<br />
Either you use the dependencies.sh script or follow the steps below.<br />
#####Libboost:<br />
apt-get install libboost-all-dev
#####RestClient:<br />
git clone https://github.com/mrtazz/restclient-cpp<br />
cd restclient-cpp/ && ./autogen.sh && ./configure && make && sudo make install<br />
<br />
For connecting with the CouchDB Rest API.<br />
#####RapidJSON:<br />
git clone https://github.com/miloyip/rapidjson<br />
cd rapidjson && mkdir build && cmake .. && make && make install<br />
<br />
For searching data with/in the Database and parsing the configuration file.
#####libiw-dev:<br />
sudo apt-get install libiw-dev<br />
Overall WiFi interaction.<br />
#####gpsd/libgps-dev:<br />
sudo apt-get install gpsd libgps-dev<br />
Overall GPS interaction.<br />
<br />
Uses these devices: (not needed, but recommended)<br />
A WiFi dongle.<br />
A GPS dongle.<br />
(Small) Cameras (numberplate recognition is not yet implemented)<br />

###Heyy, that's pretty good.<br />
#####How can I help?<br />
Report Bugs, open a push request, just any useful contribution should get accepted.<br />
#####What's TODO:<br />
WiFi:<br />
->Get WiFi Encryption Type (maybe via libtins in a thread) <br />
->Karma HotSpot<br />
->Authentication with known & open Networks (first over system(), then maybe over an actual 802.11 implementation)<br />
<br />
Networking: (after connecting to networks is done)<br />
->Host Discovery<br />
->Spoofing<br />
<br />
Client:<br />
->On Internet: Connect to main Node and sync.<br />
->Get cmd's and set switches accordingly.<br />
<br />
GPS:<br />
->Navigation with GPS (Map Rendering & Overlay)<br />
<br />
Camera:<br />
->Parking System (Distance measurement, etc.)<br />
->Number Plate Recognition & Location logging<br />
<br />
Code Documentation<br />
<br />
Whatever else comes to my/your head and seems usable.<br />
<br />

###Errors:
error while loading shared libraries: librestclient-cpp.so.1: cannot open shared object file: No such file or directory:<br />
ln -s /usr/local/lib/librestclient-cpp.so.1 /usr/lib/<br />

// Code is ugly. No h8 pls b0ss.
