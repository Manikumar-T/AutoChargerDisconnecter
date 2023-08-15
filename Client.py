import socket
import psutil
 

msgFromClient       = "Hello esp8266 I am asus rog"

bytesToSend         = str.encode(msgFromClient)

serverAddressPort   = ("192.168.206.220", 4210)

bufferSize          = 1024

 

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 
def sendData(msg):
     # Send to server using created UDP socket
    UDPClientSocket.sendto(str.encode(msg), serverAddressPort)



def getReceivedData():
   #Recevie msg form the server
    msgFromServer = UDPClientSocket.recvfrom(bufferSize)
    return msgFromServer[0]

def instructor():
    battery = psutil.sensors_battery()

    battery_level = int(battery.percent)
    charge_status = battery.power_plugged

    print("Battery percentage : ", battery_level)
    print("Power plugged in : ", charge_status)
    if(battery_level ==100 and charge_status == True):
        return "FULL\0"
    elif(battery_level <40 and charge_status == False):
        return "LOW\0"
    else:
       return "FULL\0"
    
sendData(msgFromClient)
msg = "Message from Server {}".format(getReceivedData())

print(msg)


sendData("LOW\0")
print(instructor())

