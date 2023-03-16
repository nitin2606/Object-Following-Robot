import requests
import time

from pynput import keyboard

evenemenr = ""
print("Start")

result = str(0)

url = "http://10.42.0.229"

res = requests.get(url)
if(res.text != None):
    print(res.text)
    print("Connected")


def on_key_release(key):
    global result

    if result !='S':
        result = 'S'
        print(result)
        #result_bytes = result.encode('utf_8')
        requests.post("http://192.168.4.1/?State="+result, data="S")


def on_key_pressed(key):
    global result
    result1 = '%s' % key

    if result == 'S':

        if result1 =='Key.up':
            result = 'F'
            print(result)
        
        if result1 =="Key.down":
            result = 'B'
            print(result)
        

        if result1 =="Key.left":
            result = 'L'
            print(result)

        if result1 =='Key.right':
            result = 'R'
            print(result)
        
        if result1 =='Key.X':
            result = 'S'
            print(result)
        
        if result1 =='Key.G':
            result = 'G'
            print(result)
        
    
        requests.post("http://192.168.4.1/?State="+result, data=None)


with keyboard.Listener(on_release = on_key_release, on_press=on_key_pressed) as listener:
    listener.join()





'''

while True:
    a = input('Enter Command : ')

    res = requests.post("http://192.168.4.1/?State="+a, data='F')


print(res.text)

'''