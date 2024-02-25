mqtt.py


import paho.mqtt.client as mqtt
import json, time

inTopic = "psna/robo/kit"
outTopic = "psna/robo/app"
received = ""

def send(device, command):
    doc = {}
    doc["device"] = device
    doc["command"] = command
    js = json.dumps(doc) 
    print(js)
    client.publish(outTopic,js)

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(inTopic)
    client.publish(outTopic,"Hello world")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    received = str(msg.payload)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("broker.mqtt-dashboard.com", 1883, 120)

send ("robo1","stop")

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.

print("hello")
client.loop_start()

# while True:
#     time.sleep(1000)