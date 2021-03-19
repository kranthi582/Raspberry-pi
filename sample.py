import RPi.GPIO as GPIO
import blynklib
import time
from urllib.request 
import urlopen
import sys
import Adafruit_DHT
import urllib3
import os
import cv2
import smtplib
from Adafruit_IO import Client, Feed, RequestError
import os.path
from email.mime.text import MIMEText#email.mime.text.MIMEText(_text[, _subtype[, _charset]])
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase#email.mime.base.MIMEBase(_maintype(e.g. text or image), _subtype(e.g. plain or gif), **_params(e.g.key/value dictionary))
from email import encoders




m11=2
m12=3
m21=4
m22=17
dt=14
moisture=15
seeder=21
weeder=23
pump=16

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)


GPIO.setup(m11, GPIO.OUT)
GPIO.setup(m12, GPIO.OUT)
GPIO.setup(m21, GPIO.OUT)
GPIO.setup(m22, GPIO.OUT)
GPIO.setup(seeder, GPIO.OUT)
GPIO.setup(weeder, GPIO.OUT)
GPIO.setup(pump, GPIO.OUT)

GPIO.setup(dt, GPIO.IN)
GPIO.setup(moisture, GPIO.IN)





sensor=Adafruit_DHT.DHT11

GPIO.output(m11 , 0)
GPIO.output(m12 , 0)
GPIO.output(m21, 0)
GPIO.output(m22, 0)
GPIO.output(seeder , 0)
GPIO.output(weeder, 0)
GPIO.output(pump, 0)


BASE_URL = "http://embagribot.dbandroid.online/save_values.php?"







email = 's8897576332@gmail.com'
password = 'surya8897'
send_to_email = 'matlab@takeoffprojects.com'
subject = 'msg from agribot'
message = 'location image received'
file_location = '/home/pi/AGRI0.png'
msg = MIMEMultipart()#Create the container (outer) email message.
msg['From'] = email
msg['To'] = send_to_email
msg['Subject'] = subject
'''as.string() 
|
+------------MIMEMultipart 
              |                                                |---content-type 
              |                                   +---header---+---content disposition 
              +----.attach()-----+----MIMEBase----| 
                                 |                +---payload (to be encoded in Base64)
                                 +----MIMEText'''
msg.attach(MIMEText(message, 'plain'))#attach new  message by using the Message.attach

auth_token = 'w553_l9AXt0rSvDSkcH4ssNm9rcs4SaS'

# Initialize Blynk

blynk = blynklib.Blynk(auth_token)

@blynk.handle_event('write V0')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo =="1":
        print ("LEFT")
        GPIO.output(m21 , 0)
        GPIO.output(m22 , 0)
        GPIO.output(m11 , 1)
        GPIO.output(m12 , 0)
    else:
        GPIO.output(m11 , 0)
        GPIO.output(m12 , 0)
        GPIO.output(m21 , 0)
        GPIO.output(m22 , 0)
    
@blynk.handle_event('write V1')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo =="1":
        print ("RIGHT")
        GPIO.output(m21 , 1)
        GPIO.output(m22 , 0)
        GPIO.output(m11 , 0)
        GPIO.output(m12 , 0)
    else:
        GPIO.output(m11 , 0)
        GPIO.output(m12 , 0)
        GPIO.output(m21 , 0)
        GPIO.output(m22 , 0)
        

        
@blynk.handle_event('write V2')
def write_handler_pin_handler(pin, value):
    Doorlock = (format(value[0]))
    if Doorlock =="1":
        print ("STOP")
        GPIO.output(m11 , 0)
        GPIO.output(m12 , 0)
        GPIO.output(m21 , 0)
        GPIO.output(m22 , 0)

        
@blynk.handle_event('write V3')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo  =="1":
        print ("FORWARD")
        GPIO.output(m21 , 1)
        GPIO.output(m22 , 0)
        GPIO.output(m11 , 1)
        GPIO.output(m12 , 0)

@blynk.handle_event('write V4')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo =="1":
        print ("BACK")
        GPIO.output(m21 , 0)
        GPIO.output(m22 , 1)
        GPIO.output(m11 , 0)
        GPIO.output(m12 , 1)
@blynk.handle_event('write V5')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo =="1":
        humidity, temperature = Adafruit_DHT.read_retry(sensor,dt )
        water=GPIO.input(moisture)
        soil=water
        y = int(temperature)
        x = int(humidity)
        z = int(water)

        print('Temp={0:0.1f}*C Humidity={1:0.1f}%'.format(temperature, humidity))
            
        print("MOISTURE VALUE(I.E DRY=1,WET=0)=",water)
        soil=water

        hom = 'http://embagribot.dbandroid.online/save_values.php?'+'tmp='+str(y)+'&&humidity='+ str(x)+'&&soil='+str(z)+'&&id=user1'
        http = urllib3.PoolManager()
        resp = http.request('GET', hom)
        print(resp.status)
        print(hom)
        
        print("sent")
        print("Response: {}".format(conn.read()))
        conn.close()

@blynk.handle_event('write V6')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo =="1":
        print ("IMAGE UPLOADING")
        print("with in cemara")
        camera = cv2.VideoCapture(0)
        for i in range(10):
            return_value, image = camera.read()
            cv2.imwrite('AGRI'+str(i)+'.png', image)
            print('AGRI IMG captured')
            time.sleep(2)
            break
        del(camera)
        
        
        filename = os.path.basename(file_location)#function returns the tail of the path
        attachment = open(file_location, "rb") #“rb” (read binary)
        part = MIMEBase('application', 'octet-stream')#Content-Type: application/octet-stream , image/png, application/pdf
        part.set_payload((attachment).read())
        encoders.encode_base64(part)
        part.add_header('Content-Disposition', "attachment; filename= %s" % filename)#Content-Disposition: attachment; filename="takeoff.png"
        msg.attach(part)
        server = smtplib.SMTP('smtp.gmail.com', 587)# Send the message via local SMTP server.
        print("SENDING MAIL")
        server.starttls()# sendmail function takes 3 arguments: sender's address, recipient's address and message to send
        server.login(email, password)
        text = msg.as_string()
        server.sendmail(email, send_to_email, text)
        print("mail sent")
        server.quit()
@blynk.handle_event('write V7')
def write_handler_pin_handler(pin, value):
    robo = (format(value[0]))
    if robo =="1":
        print ("pump ON")
        GPIO.output(pump , 1)
    else:
        print ("pump OFF")
        GPIO.output(pump , 0)
        


@blynk.handle_event('write V9')
def write_handler_pin_handler(pin, value):
    robo  = (format(value[0]))
    if robo =="1":
        print ("seder ON")
        GPIO.output(seeder , 1)
    else:
        print ("seder OFF")
        GPIO.output(seeder , 0)


try:
    while True:
        blynk.run()

        
                    



except KeyboardInterrupt:
    print("Quit")

# Reset GPIO settings
GPIO.cleanup()
