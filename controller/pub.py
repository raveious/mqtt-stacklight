import paho.mqtt.publish as publish

publish.single("tester", "payload", hostname="jupiter.solar-system.universe")