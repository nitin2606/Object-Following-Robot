import serial
import time


ser = serial.Serial('/dev/ttyACM0', 9600) 




while True:

    data = input("Data: ")


    if data == 'S':

        data_to_send = 'S' 
        ser.write(str.encode(data_to_send))  


    elif data == 'F':

        data_to_send = 'F' 
        ser.write(str.encode(data_to_send))  


    elif data == 'L':

        data_to_send = 'L' 
        ser.write(data_to_send.encode())

    elif data == 'R':

        data_to_send = 'R' 
        ser.write(data_to_send.encode()) 

    elif data == 'B':

        data_to_send = 'B' 
        ser.write(data_to_send.encode())     


    time.sleep(0.5)




    









