import cv2 as cv
import time
from threading import Thread
import numpy as np
import requests


class webCamStream :

    def __init__(self, stream_id=0):

        self.stream_id = stream_id

        self.vCap = cv.VideoCapture(self.stream_id)
        
        if self.vCap.isOpened() is False:
            print("[Exiting]: Error accessing webcam stream.")
            exit(0)
        
        fps_input_stream = int(self.vCap.get(5))
        print("FPS of input stream: {}".format(fps_input_stream))

        self.grabbed, self.frame = self.vCap.read()
        
        if self.grabbed is False:
            print("[Exiting] No more frames to read")
            exit(0)
        
        self.stopped = True

        self.t = Thread(target = self.update, args=())
        self.t.daemon = True # daemon thread runs in background



    # Method to start thread 
    def start(self):
        self.stopped = False
        self.t.start()
    
    # Method passed to thread to read next available frame


    def update(self):

        while True:
            if self.stopped is True:
                break

            self.grabbed, self.frame = self.vCap.read()
            if self.grabbed is False:
                print("[Exiting] No more frames to read")
                self.stopped = True
                break
        
        self.vCap.release()
    
    # Method to return latest read frame
    def read(self):
        return self.frame
    
    # Method to stop reading frames
    def stop(self):
        self.stopped = True
    


node_url = "http://10.42.0.229/?State="
kernel = np.ones((7,7), np.uint8)

webcam_stream = webCamStream(stream_id="http://10.42.0.95:4747/video")
webcam_stream.start()

num_frames_processed = 0
start = time.time()

while True:
    if webcam_stream.stopped is True:
        break

    else:
        frame = webcam_stream.read()

        
        hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
        frame = cv.line(frame, (320,0), (320,480), (255,0,0), 2)
        frame = cv.line(frame, (640,375), (0,375), (255,0,0), 2)

        lower_bound = np.array([20, 80, 80])      # for yellow color  
        upper_bound = np.array([30, 255, 255])     # for 

        #lower_bound = np.array([136, 87, 111], np.uint8)      # for red color  
        #upper_bound = np.array([180, 255, 255], np.uint8)    # for red color

        mask = cv.inRange(hsv, lower_bound, upper_bound)

        mask = cv.morphologyEx(mask, cv.MORPH_CLOSE, kernel)
        mask = cv.morphologyEx(mask, cv.MORPH_OPEN, kernel)

        segmented_img = cv.bitwise_and(frame, frame, mask=mask)

        contours, hierarchy = cv.findContours(mask.copy(), cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)


        for contour in contours:

            area = cv.contourArea(contour)
            #print(area)

            if area>400:

                x,y,w,h = cv.boundingRect(contour)

                frame = cv.rectangle(frame, (x,y), (x+w, y+h), (0,255,255), 2)

                print("X = ",(x + (x+w))/2,"   ", "Y = ",(y + (y+h))/2)

                getX = (x + (x+w))/2
                getY = (y + (y+h))/2

                if (getX < 180):
                    print("LEFT")
                    requests.post(node_url+"L", timeout=10)
                    break
                
                if (getX > 440):
                    print("RIGHT")
                    requests.post(node_url+"R", timeout=10)
                    break
                
                if (440>getX>180 and  getY<350):
                    print("FORWARD")
                    requests.post(node_url+"F", timeout=10)
                    break
                
                if(440>getX>180 and getY>350):
                    print("STOP")
                    requests.post(node_url+"S", timeout=10)
                    break


                
            else:
                print("STOP")
                requests.post(node_url+"S", timeout=10)
                break

        num_frames_processed +=1

        # displaying frame
        cv.imshow('Frame', frame)
        cv.imshow('Mask',segmented_img)
        key = cv.waitKey(1)
        if key==ord('q'):
            requests.post(node_url+"S", timeout=10)
            break

end = time.time()
webcam_stream.stop()



elapsed = end-start
fps = num_frames_processed/elapsed 
print("FPS: {} , Elapsed Time: {} ".format(fps, elapsed))
# closing all windows 
cv.destroyAllWindows()



