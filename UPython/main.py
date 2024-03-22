# Objet du script :
# Connexion d'un module LoRa-E5 à un réseau LoRaWAN privé sur TTN,
# préalablement configuré.
# Publication de données de température, humidité et pression sur TTN au
# format Cayenne LPP
# Cet exemple est obtenu à partir des ressources mises à disposition par
# Vittascience :
# https://github.com/vittascience/stm32-libraries/tree/main/grove_modules
 
# Importation des différents pilotes
import machine
from stm32_LoRa import *
from utime import sleep_ms
from machine import I2C,Pin # Bibliothèque pour le bus I2C
from machine import Pin
import VL53L0X # Bibliothèque pour le VL53L0X
#import smbus

# Initialisation de l'I2C sans spécifier les broches SDA et SCL

# Affichage des données lues
#print("Données lues depuis le périphérique I2C:", data)
# Port série de la NUCLEO_WB55
UART_WB55 = const(2)
 
# Identifiants sur le réseau LoRaWAN
devAddr = '42 00 65 91'
appEui	= '00 00 00 00 00 00 00 00'
appKey	= '8B9DE6DCF1640B607DE0966980AAA5FC'
 
# Temporisations diverses
DelayRebootLostConnection = 300 # Exprimé en minutes
DelayTryJoin = 10 # Exprimé en secondes
MaxTryJoin = int((DelayRebootLostConnection * 60) / DelayTryJoin)
DelaySend = 30 # Exprimé en secondes
from time import sleep_ms # Pour temporiser
import gc # Ramasse miettes, pour éviter de saturer la mémoire
 
# Fréquence du timer, en hertz
MIN_FREQUENCY_HZ = 0.25
MAX_FREQUENCY_HZ = 10.
 
# Bornage de l'intervalle de mesures du capteur, valeurs en mm
MIN_DIST_MM = const(1)
MAX_DIST_MM = const(1700)
 
frequency = MIN_FREQUENCY_HZ # Fréquence initiale du timer
distance = MAX_DIST_MM # distance initiale d'un supposé obstacle
 
# Initialisation de la broche du buzzer
buzzer_pin = pyb.Pin('D6', pyb.Pin.OUT_PP)
 
timer_id = 1 # Timer sur D6
 
 
# Fonction de callback chargée de traiter et réagir aux messages envoyés par le serveur
# LoRaWAN au module LoRa-E5 
def DataReceived(Port = 0, DataReceived = b''):
	print("#### = Data received")
	print("Data received on PORT: " + str(Port) +
				", Size = "+ str(len(DataReceived)) +
				", Data = "+str([hex(x) for x in list(DataReceived)]))
 
 
# Initialisation du module LoRa-E5 
loRa = LoRa(9600, UART_WB55, DataReceiveCallback = DataReceived)
 
# Paramètres d'identification du module pour sa connexion au réseau LoRaWAN
status = loRa.setIdentify(DevAddr = devAddr,AppEui	= appEui,AppKey	= appKey)
 
# Affichage des différents paramètres du réseau LoRaWAN
def PrintLoRaParameters():
	identify = loRa.getIdentify()
	if(identify != -1):
		print("#####################################################################")
		print("########## INITIALIZE                                        ########")
		print("#####################################################################")
		print("LORA_DRIVER_VERSION : " + loRa.getDriverVersion())
		print("#### " + loRa.getMode() + " ####")
		print("#### AppKey: " + identify['AppKey'])
		print("#### DevEUI: " + identify['DevEui'])
		print("#### AppEUI: " + identify['AppEui'])
		print("#### DevAddr: " + identify['DevAddr'])
	else:
		print("#### = Read identify fail.\nReboot!")
		sleep_ms(2000)
		machine.reset()
	if status == -1:
		print("#### = Initialize fail.\nReboot!")
		sleep_ms(2000)
		machine.reset()
	else:
		print("#### = Initialize success.")
 
# Etablissement de la connexion ("join") LoRaWAN
def JoinNetwork():
 
	# Try to join network
	joinStatus = False
	tryJoin = 0
	while joinStatus == False:
		# Join LoRaWAN
		print("#### = Try join n°" + str(tryJoin + 1))
		status = loRa.join()
		if status == -1:
			print("#### = Join Fail, retry in " + str(DelayTryJoin) + " seconds.")
			tryJoin += 1
			if tryJoin > MaxTryJoin:
				# Reboot board
				print("Reboot!")
				machine.reset()
				sleep_ms(DelayTryJoin * 1000)
		else:
				joinStatus = True
				print("#### = Join sucess.")
# Emission de trames au format Cayenne LPP contenant les mesures du BME280
def GetSendData():
    #Initialisation du bus I2C numéro 1 du STM32WB55 
 #   i2c1 = I2C(1)
 
    # Pause d'une seconde pour laisser à l'I2C le temps de s'initialiser
 #   sleep_ms(1000)
 
 #   tof = VL53L0X.VL53L0X(i2c=i2c1)
    while True:
			# Lecture des valeurs mesurées
			# distance = min(max(tof.read(), MIN_DIST_MM), MAX_DIST_MM)
			# print ("Distance : "+str(distance))
			# # Convertir la distance en un entier non signé sur 16 bits
			# distance_int = int(distance)
			# # Extraire les octets de poids fort et faible
			# distance_high_byte = (distance_int >> 8) & 0xFF
			# distance_low_byte = distance_int & 0xFF
			# # Affichage des mesures
			# print('=' * 40)  # Imprime une ligne de séparation
			# print("Distance : %.1f mm" % distance)
			# # Construction de la trame LoRaWAN au format Cayenne LPP
			# loRaFrame = bytearray([distance_high_byte, distance_low_byte])
			Temp = Pin('D4', Pin.IN)  # Temp
			Hum = Pin('D5', Pin.IN)	# Hum

			# Lire la valeur de la broche
			Temp_status = Temp.value()
			Hum_status = Hum.value()
			print(Temp_status)
			print(Hum_status)
			# Afficher la valeur
			if Temp_status == 1:
				print("Temp High")
				Temp_status_high_byte = 0xFF
			else:
				print("Temp Normal")
				Temp_status_high_byte = 0x00
			if Hum_status == 1:
				print("Humidity High")
				Hum_satus_low_byte = 0xFF
			else:
				print("Humidity Normal")
				Hum_satus_low_byte = 0x00
			# Emission de la trame LoRaWAN
			print("#### = Send data.")
			#Temp_status_high_byte = (Temp_status >> 8) & 0xFF
			#Hum_satus_low_byte = Hum_status & 0xFF
			loRaFrame = bytearray([Temp_status_high_byte, Hum_satus_low_byte])
			sendStatus = loRa.sendData(loRaFrame, Port=1, NeedAck= False)
 
			if sendStatus == -1:
				print("#### = Send fail.")
			else:
				print("#### = Send success.")
 
			# Place le module LoRa-E5 en mode veille
			print("#### = LoRa module enter low power mode.")
			loRa.enterLowPowerMode()
			# Temporisation jusqu'à l'envoi de la prochaine trame (10 secondes)
			sleep_ms(10000)
 
# Exécution des fonctions
PrintLoRaParameters() # Affichage des paramètres
JoinNetwork() # Connexion à TTN
GetSendData() # Emission de trames au format Cayenne LPP


"""
def read_data_from_i2c():
    # Lecture des données depuis le capteur via I2C
    data = bus.read_i2c_block_data(DEVICE_ADDRESS, 0, 4)  # 4 octets de données sont envoyés
    
    # Les données sont lues en tant qu'entiers non signés sur 16 bits (big-endian)
    temp = (data[0] << 8 | data[1]) / 100.0
    hum = (data[2] << 8 | data[3]) / 100.0
    
    return temp, hum"""

# Définir la broche que vous voulez lire
