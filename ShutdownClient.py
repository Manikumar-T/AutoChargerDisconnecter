#!/mnt/FC0457300456ED60/Project/Automation/AutoChargerDisconnecter/venvDisconnecter/bin/python
'''
 1.Rename this file without file Extension 
 2.past the file in /usr/bin for user
 Note:make sure to change the shebang line of your own

'''
#To use the socket to connect UDP Server
import socket
#psutil used to system related information
import psutil
#os is used to do a system related operation
import os
#funciton to shutdown ssytem 
def atShutdown():
    #UDP server IP and port number
    serverAddressPort   = ("192.168.206.220", 4210)
    # Create a UDP socket at client side
    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    #battery instance to get the battery related information
    battery = psutil.sensors_battery()
    #get the battery level and charge status
    battery_level = int(battery.percent)
    charge_status = battery.power_plugged
    #print the value
    print("Battery percentage : ", battery_level)
    print("Power plugged in : ", charge_status)
    #check if battery almost full and the same time charger is connected while shutdown
    if(battery_level >= 90 and charge_status == True):
        # Send to server using created UDP socket
         UDPClientSocket.sendto(str.encode("shutdown\0"), serverAddressPort)
    elif(charge_status == True):
         # Send to server using created UDP socket
         UDPClientSocket.sendto(str.encode("wait&down\0"), serverAddressPort)
    os.system("poweroff")

atShutdown()