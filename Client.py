#import socket to create the UDP socket
import socket
#psutil for get the system related information
import psutil
 
#Greate msg is for initial msg from client to esp8266
# msgFromClient       = "Hello esp8266 I am asus rog"
# bytesToSend         = str.encode(msgFromClient)

#Server ip and port address
serverAddressPort   = ("192.168.206.220", 4210)

#Buffer size for the remote msg value 
# bufferSize          = 1024

 

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

#function to send the data to server
def sendData(msg):
     # Send to server using created UDP socket
    UDPClientSocket.sendto(str.encode(msg), serverAddressPort)


#function to receive the data from the server
# def getReceivedData():
#    #Recevie msg form the server
#     msgFromServer = UDPClientSocket.recvfrom(bufferSize)
#     return msgFromServer[0]

#function to send the instruction to server based on some condition
def instructor():
    #get the battery sensors instance to get the battery information
    battery = psutil.sensors_battery()
    #get the batter level and charge status
    battery_level = int(battery.percent)
    charge_status = battery.power_plugged
    #print the values
    print("Battery percentage : ", battery_level)
    print("Power plugged in : ", charge_status)
    
    #condition for if charge full and the charger is connected
    if((battery_level>=99 and battery_level<=100) and charge_status == True):
        return "FULL\0"
    #condition for if charge is low and the charger is not connected
    elif(battery_level < 40 and charge_status == False):
        return "LOW\0"
    #reverse the above condition
    elif(battery_level < 40 and charge_status == True):
       return "OFF\0"
    #Reverse the above condition
    elif(battery_level < 100 and charge_status == False):
        return "OFF\0"
    else:
        return "N0 Event"
    
#sendData(msgFromClient)
#msg = "Message from Server {}".format(getReceivedData())

#print(msg)

sendData(instructor())


