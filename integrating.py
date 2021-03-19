import numpy as np
import cv2
import random
import os, time
import RPi.GPIO as GPIO
import RPi.GPIO as GPIO
import time
import threading

from smbus2 import SMBus
from mlx90614 import MLX90614

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

ir=18
buzzer=16
pump=22
Motor1A=11
Motor1B=13
#temp_sensor=7

GPIO.setup(ir, GPIO.IN)
#GPIO.setup(temp_sensor, GPIO.IN)
GPIO.setup(pump,GPIO.OUT)
GPIO.setup(buzzer,GPIO.OUT)
GPIO.output(buzzer,GPIO.LOW)
GPIO.setup(Motor1A,GPIO.OUT)  # All pins as Outputs
GPIO.setup(Motor1B,GPIO.OUT)
GPIO.output(Motor1A,GPIO.LOW)
GPIO.output(Motor1B,GPIO.LOW)

# multiple cascades: https://github.com/Itseez/opencv/tree/master/data/haarcascades

face_cascade = cv2.CascadeClassifier('/home/pi/Desktop/IOT based temperature and mask scan entry sysstem/haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('/home/pi/Desktop/IOT based temperature and mask scan entry sysstem/haarcascade_eye.xml')
mouth_cascade = cv2.CascadeClassifier('/home/pi/Desktop/IOT based temperature and mask scan entry sysstem/haarcascade_mcs_mouth.xml')
upper_body = cv2.CascadeClassifier('/home/pi/Desktop/IOT based temperature and mask scan entry sysstem/haarcascade_upperbody.xml')



# Adjust threshold value in range 80 to 105 based on your light.
bw_threshold = 80

# User message
font = cv2.FONT_HERSHEY_SIMPLEX
org = (30, 30)
weared_mask_font_color = (0, 255, 0)
not_weared_mask_font_color = (0, 0, 255)
thickness = 2
font_scale = 1
weared_mask = "Thank You for wearing MASK"
not_weared_mask = "Please wear MASK"

# Read video
cap = cv2.VideoCapture(0)


def Process():
    
    ir_value=GPIO.input(ir)
    if ir_value==0:
        
        print("Hand Detected")
        print("Turn ON Tap")
        GPIO.output(pump,GPIO.HIGH)
        time.sleep(5)
        print("Turn off Tap")
        GPIO.output(pump, GPIO.LOW)
        time.sleep(2)
        print("Door Open")
        GPIO.output(Motor1A,GPIO.HIGH)
        GPIO.output(Motor1B,GPIO.LOW)

       # time.sleep(5)
        time.sleep(0.5)
        print("Close Door")
        GPIO.output(Motor1A,GPIO.LOW)
        GPIO.output(Motor1B,GPIO.LOW)
            
    elif ir_value==1:
        print("No Hand Detected")
        GPIO.output(pump, GPIO.LOW)
        time.sleep(2)


def temp():
    bus = SMBus(1)
    sensor = MLX90614(bus, address=0x5A)
    print ("Ambient Temperature :", sensor.get_ambient())
    print ("Object Temperature :", sensor.get_object_1())
    temp=sensor.get_object_1()
    bus.close()
    if temp>35:
        print("High Temperature")
        GPIO.output(buzzer,GPIO.HIGH)
        print("Buzzer ON")
        time.sleep(5)
    else:
        print("Normal temperature")
        Process()
        time.sleep(5)
        


##
##def thread_function1():
## while True:
##        ir_value=GPIO.input(ir)
##        if ir_value==0:
##            
##            print("Hand Detected")
##            GPIO.output(pump,GPIO.HIGH)
##            time.sleep(5)
##            GPIO.output(pump, GPIO.LOW)
##            time.sleep(2)
##            GPIO.output(Motor1A,GPIO.HIGH)
##            GPIO.output(Motor1B,GPIO.LOW)
##            time.sleep(5)
##            
##        elif ir_value==1:
##            
##            print("No Hand Detected")
##            GPIO.output(pump, GPIO.LOW)
##            time.sleep(2)

##def thread_function2():
##    while True:
##        GPIO.output(Motor1A,GPIO.HIGH)
##        GPIO.output(Motor1B,GPIO.LOW)
##        time.sleep(5)

#thread1= threading.Thread(target=thread_function1)# args=(1,))
#thread2= threading.Thread(target=thread_function2)

while 1:
    # Get individual frame
    ret, img = cap.read()
    img = cv2.flip(img,1)

    # Convert Image into gray
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Convert image in black and white
    (thresh, black_and_white) = cv2.threshold(gray, bw_threshold, 255, cv2.THRESH_BINARY)
    #cv2.imshow('black_and_white', black_and_white)

    # detect face
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)

    # Face prediction for black and white
    faces_bw = face_cascade.detectMultiScale(black_and_white, 1.1, 4)
    GPIO.output(buzzer,GPIO.LOW)
    
    if(len(faces) == 0 and len(faces_bw) == 0):
        cv2.putText(img, "No face found...", org, font, font_scale, weared_mask_font_color, thickness, cv2.LINE_AA)
    elif(len(faces) == 0 and len(faces_bw) == 1):
        # It has been observed that for white mask covering mouth, with gray image face prediction is not happening
        cv2.putText(img, weared_mask, org, font, font_scale, weared_mask_font_color, thickness, cv2.LINE_AA)
        
        
    else:
        # Draw rectangle on gace
        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x + w, y + h), (255, 255, 255), 10)
            roi_gray = gray[y:y + h, x:x + w]
            roi_color = img[y:y + h, x:x + w]


            # Detect lips counters
            mouth_rects = mouth_cascade.detectMultiScale(gray, 1.5, 5)

        # Face detected but Lips not detected which means person is wearing mask
        if(len(mouth_rects) == 0):
            cv2.putText(img, weared_mask, org, font, font_scale, weared_mask_font_color, thickness, cv2.LINE_AA)
            GPIO.output(buzzer,GPIO.LOW)
            temp()
            
            #Process()
           # thread1.start()
            #thread2.start()
            
        else:
            for (mx, my, mw, mh) in mouth_rects:

                if(y < my < y + h):
                    # Face and Lips are detected but lips coordinates are within face cordinates which `means lips prediction is true and
                    # person is not waring mask
                    cv2.putText(img, not_weared_mask, org, font, font_scale, not_weared_mask_font_color, thickness, cv2.LINE_AA)
                    GPIO.output(buzzer,GPIO.HIGH)
                    time.sleep(0.5)
                    #GPIO.output(buzzer,GPIO.LOW)
                    #cv2.rectangle(img, (mx, my), (mx + mw, my + mh), (0, 255, 0), 10)
                    break
                #GPIO.output(buzzer,GPIO.LOW)

    # Show frame with results
    cv2.imshow('Mask Detection', img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break
   

    
            


# Release video
cap.release()
cv2.destroyAllWindows()
