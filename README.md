MQTTalk
=======

It's an MQTT and QT based talk app.  Well if Facebook can do it why not make a free one?

This is just for fun, I'm not suggesting you use it.

Building this source
--------------------

Building on Ubuntu 18.04:

    sudo apt install qt4-qmake libqt4-dev libqjson-dev libmosquitto-dev
    cd mqttalk
    qmake
    make

It's not publishing messages itself, to test functionality so far I used:

    mosquitto_pub -t test -m "{\"message_id\": 123, \"time\": \"2019-10-20 14:33:14 +0100\", \"sender\": \"tester\", \"message\": \"one two three...\"}"
