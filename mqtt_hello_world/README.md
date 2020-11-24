Make sure you have an MQTT broker running. I used https://github.com/SensorsIot/IOTstack to setup Mosquitto.

Setup ```YourMQTTBrokerUsername``` and ```YourMQTTBrokerPassword``` following the steps in the Security section: https://github.com/SensorsIot/IOTstack/blob/master/docs/Containers/Mosquitto.md

To test the MQTT broker, launch a shell in the Mosquitto container in two separate terminal windows:
``` bash
docker exec -it mosquitto sh
```
From one terminal subscribe to ```YourTopic```:
``` bash
mosquitto_sub -u YourMQTTBrokerUsername -P YourMQTTBrokerPassword -v -t YourTopic
```
Make sure to add quotes ```' '``` to YourTopic if it contains ```/``` for example.

From the second terminal publish a message to the YourTopic:
```bash
mosquitto_pub -t YourTopic -m 'helloWorld' -u YourMQTTBrokerUsername -P YourMQTTBrokerPassword -v
```

If everything is ok, you will see ```helloWorld``` in the terminal you used the ```mosquitto_sub``` command.

If the previous steps are successfull, the ESP32 will publish the message to ```YourTopic``` and you will be able to see it in the terminal. You may also use the node-red flow provided.
