#!/usr/bin/python
# Example using a character LCD connected to a Raspberry Pi
import RPi.GPIO as GPIO
import time
import Adafruit_CharLCD as LCD
import serial
import smtplib
import urllib3
http = urllib3.PoolManager()
from Adafruit_IO import Client, Feed, RequestError
GPIO.setwarnings(False)

######################################################################

LPG_GAS = 26
Buzzer = 5
Motor = 6
####################################################################

# change these as desired - they're the pins connected from the
# SPI port on the ADC to the Cobbler
SPICLK = 7
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

########################################################################

# Raspberry Pi pin setup
lcd_rs = 25
lcd_en = 24
lcd_d4 = 23
lcd_d5 = 17
lcd_d6 = 18
lcd_d7 = 22
lcd_backlight = 2
lcd_columns = 16
lcd_rows = 2
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7, lcd_columns, lcd_rows, lcd_backlight)

########################################################################


ser = serial.Serial ("/dev/ttyS0", 9600)


def setup():
       #GPIO.setmode(GPIO.BOARD)

       
       GPIO.setup(LPG_GAS, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
       GPIO.setup(Buzzer, GPIO.OUT)
       GPIO.setup(Motor, GPIO.OUT)

       GPIO.output(Motor, False)

       # set up the SPI interface pins
       GPIO.setup(SPIMOSI, GPIO.OUT)
       GPIO.setup(SPIMISO, GPIO.IN)
       GPIO.setup(SPICLK, GPIO.OUT)
       GPIO.setup(SPICS, GPIO.OUT)
       lcd.set_cursor(0,0)
       lcd.message('   Welcome to   ')########################
       lcd.set_cursor(0,1)
       lcd.message('LPG GAS Monitor')########################




       
# read SPI data from MCP3008 chip, 8 possible adc's (0 thru 7)
def readadc(adcnum, clockpin, mosipin, misopin, cspin):
        if ((adcnum > 7) or (adcnum < 0)):
                return -1
        GPIO.output(cspin, True)

        GPIO.output(clockpin, False)  # start clock low
        GPIO.output(cspin, False)     # bring CS low

        commandout = adcnum
        commandout |= 0x18  # start bit + single-ended bit
        commandout <<= 3    # we only need to send 5 bits here
        for i in range(5):
                if (commandout & 0x80):
                        GPIO.output(mosipin, True)
                else:
                        GPIO.output(mosipin, False)
                commandout <<= 1
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)

        adcout = 0
        # read in one empty bit, one null bit and 10 ADC bits
        for i in range(14):
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)
                adcout <<= 1
                if (GPIO.input(misopin)):
                        adcout |= 0x1

        GPIO.output(cspin, True)
        
        adcout >>= 1       # first bit is 'null' so drop it
        return adcout




def GSM_SendMSG0():
       ser.write(b'AT'+b'\r\n')
       time.sleep(0.1)
       ser.write(b'ATE0'+b'\r\n')
       time.sleep(0.1)
       ser.write(b'AT'+b'CIMI'+b'\r\n')
       time.sleep(0.1)
       ser.write(b'ATD'+b'+917387389299'+b';'+b'\r\n')
       time.sleep(20)
       ser.write(b'AT+CMGF=1'+b'\r\n')                
       time.sleep(1)
      # ser.write(b'AT+CMGS=\"+917387389299\"' + b'\r\n')                
       #time.sleep(1)
       #ser.write(b'Cylinder Empty'+b'\r\n')                
       #time.sleep(1)
       ser.write(b"\x1A")                 
       time.sleep(1)







def GSM_SendMSG1():
       ser.write(b'AT'+b'\r\n')
       time.sleep(0.1)
       ser.write(b'ATE0'+b'\r\n')
       time.sleep(0.1)
       ser.write(b'AT+CMGF=1'+b'\r\n')                
       time.sleep(1)
       ser.write(b'AT+CMGS=\"+917387389299\"' + b'\r\n')                
       time.sleep(1)
       ser.write(b'GAS Leakage Alert'+b'\r\n')                
       time.sleep(1)
       ser.write(b"\x1A")                 
       time.sleep(1)



def Volv_off():
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)
       GPIO.output(Motor, True)
       time.sleep(0.002)
       GPIO.output(Motor, False)
       time.sleep(0.018)



def Volv_on():
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)
       GPIO.output(Motor, True)
       time.sleep(0.001)
       GPIO.output(Motor, False)
       time.sleep(0.019)      


def Cylinder_Weight():
       global x
       x = readadc(0, SPICLK, SPIMOSI, SPIMISO, SPICS)
       x = x-1000
       x = x/10
       print ((" x %s KG" % (x)))
       return x




       

#set_cursor(1,4)

def loop():
     
     while True:
         global y;
         GAS_state = GPIO.input(LPG_GAS)
         
         y = Cylinder_Weight()
         


         #lcd.set_cursor(0,1)
         #lcd.message(str(y) + ' KG')########################


         baseURL = 'https://api.thingspeak.com/update?api_key=95Y3R2OPTOMT0YAF&field1=0'
         f = baseURL +"&field1=%s" % (x)
         response = http.request('GET', f)
         print (response.read())
         

         if  GAS_state == False:
                         
                      #GPIO.output(Bulb, True)
                      lcd.clear()
                      lcd.message('Alert')
                      
                      GPIO.output(Buzzer, True)
                      Volv_off()

                      print('LPG GAS Detected')
                      GSM_SendMSG1()
                      print('Massage Sent')
                      #sender.sendmail(sendTo, emailSubject, emailContent1)
                      #print('Mail Sent')

                      
                      while GPIO.input(LPG_GAS) == False:
                        time.sleep(0.2)
         else:

                       
                      GPIO.output(Buzzer, False)
                      Volv_on()




         if x <= 2:
                print('GAS Empty')
                lcd.set_cursor(0,0)
                lcd.clear()
                lcd.message('Cylinder Empty')
                lcd.set_cursor(0,1)
                lcd.message(str(y) + ' KG')########################
                
                GPIO.output(Buzzer, True)
                time.sleep(0.5)
                GPIO.output(Buzzer, False)
                time.sleep(0.5)
                GPIO.output(Buzzer, True)
                time.sleep(0.5)
                GPIO.output(Buzzer, False)
                time.sleep(0.5)
                GPIO.output(Buzzer, True)
                time.sleep(0.5)
                GPIO.output(Buzzer, False)
                time.sleep(0.5)
                #GSM_SendMSG1()
                #print('Massage Sent to owner')
                GPIO.output(Buzzer, False)
                GSM_SendMSG0()
                print('Call done')        

         else:
               lcd.set_cursor(0,0)
               lcd.clear()
               lcd.message('LPG GAS Monitor')
               lcd.set_cursor(0,1)
               lcd.message(str(y) + ' KG')########################

         time.sleep(1)     








def endprogram():
         GPIO.output(fire_indicator, False)
         GPIO.cleanup()




if __name__ == '__main__':
          
          setup()
          
          try:
                 loop()
          
          except KeyboardInterrupt:
                 #print 'keyboard interrupt detected' 
                 endprogram()