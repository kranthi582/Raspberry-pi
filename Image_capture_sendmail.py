import cv2
import RPi.GPIO as GPIO
import sys
import cv2 
import smtplib
import os.path
from time import sleep
from email.mime.text import MIMEText#email.mime.text.MIMEText(_text[, _subtype[, _charset]])
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase#email.mime.base.MIMEBase(_maintype(e.g. text or image), _subtype(e.g. plain or gif), **_params(e.g.key/value dictionary))
from email import encoders

sys.path.append('/home/pi/pi-rfid/Write.py')
from mfrc522 import SimpleMFRC522

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
reader = SimpleMFRC522()

print("Hold a tag near the reader")

key = cv2. waitKey(1)
webcam = cv2.VideoCapture(0)
frame_width = int(webcam.get(3)) 
frame_height = int(webcam.get(4))
size = (frame_width, frame_height)

email = 'ymtstraining2020@gmail.com'
password = 'Ymts@Takeoff'
send_to_email = 'jijugracebabu10@gmail.com'
subject = 'This is the subject'
message = 'This is my message from home'
file_location = '/home/pi/Desktop/New/Jiju/NewPicture.jpg'
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
msg.attach(MIMEText(message, 'plain'))



while True:
        id, text = reader.read()
        #  print(id)
        print(text)
        #GPS_Info()

        if "Park" in text:
            print("with in cemara")
            ret,frame = webcam.read()
            cv2.imwrite("NewPicture.jpg",frame)
            webcam.release()
            break
        print("released camera")

    
filename = os.path.basename(file_location)#function returns the tail of the path
attachment = open(file_location, "rb") #“rb” (read binary)
part = MIMEBase('application', 'octet-stream')#Content-Type: application/octet-stream , image/png, application/pdf
part.set_payload((attachment).read())
encoders.encode_base64(part)
part.add_header('Content-Disposition', "attachment; filename= %s" % filename)#Content-Disposition: attachment; filename="takeoff.png"
msg.attach(part)
server = smtplib.SMTP('smtp.gmail.com', 587)# Send the message via local SMTP server.
print("with in msg")
server.starttls()# sendmail function takes 3 arguments: sender's address, recipient's address and message to send 
server.login(email, password)
text = msg.as_string()
server.sendmail(email, send_to_email, text)
print("mail sended")
server.quit()


cv2.destroyAllWindows()
