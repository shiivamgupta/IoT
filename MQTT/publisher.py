#install phao-mqtt module
#pip install paho-mqtt
import time
import paho.mqtt.client as mqtt
#constructor

client = mqtt.Client()
client1 = mqtt.Client()
client.connect("localhost",1883,60)
client1.connect("localhost",1883,60)
#connect to Broker
#brokeraddress,portnumber,keepaliveinterval
	#time.sleep(10)
	#time.sleep(10)
#payload = raw_input("Enter the payload : ")
#payload1 = raw_input("Enter the new Pyaload : ")
#payload = "Hello"

while True:
    topic_name = "cdac/acts/acpm"
    topic_name_new = "cdac/acts/pune"
    payload = input("Enter the payload : ")
    client.publish(topic_name,payload)

	#topic_name_new = "cdac/acts/pune" 
	#payload =input("Enter the payload : ")
    payload_new = input("Enter the new Pyaload : ")
	#client.publish(topic_name,payload)
    client1.publish(topic_name_new,payload_new)
#client.disconnect()
