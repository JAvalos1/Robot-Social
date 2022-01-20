##################################################################################
#Robot Social de 3 DOF con detector de emociones
#
#Autor: Julio Fabian Avalos Peralta
#Institucion: Facultad de Ingenieria UNA
#Materia: Robotica 2
#
#Referencias:
# -Facial landmarks with dlib, OpenCV, and Python  [https://www.pyimagesearch.com/2017/04/03/facial-landmarks-dlib-opencv-python/?_ga=2.267746444.321007053.1637623315-444521202.1637623315]
# -Drowsiness detection with OpenCV [https://www.pyimagesearch.com/2017/05/08/drowsiness-detection-opencv/]
# -Real-time facial landmark detection with OpenCV, Python, and dlib [https://www.pyimagesearch.com/2017/04/17/real-time-facial-landmark-detection-opencv-python-dlib/]
# -Real-Time Eye Blink Detection using Facial Landmarks [http://vision.fe.uni-lj.si/cvww2016/proceedings/papers/05.pdf]
##################################################################################

# import the necessary packages
from imutils.video import VideoStream
from imutils import face_utils
import datetime
import argparse
import imutils
import time
import dlib
import cv2
from scipy.spatial import distance as dist
import math
import serial

def eye_aspect_ratio(eye):
	# compute the euclidean distances between the two sets of
	# vertical eye landmarks (x, y)-coordinates
	A = dist.euclidean(eye[1], eye[5])
	B = dist.euclidean(eye[2], eye[4])
	# compute the euclidean distance between the horizontal
	# eye landmark (x, y)-coordinates
	C = dist.euclidean(eye[0], eye[3])
	# compute the eye aspect ratio
	ear = (A + B) / (2.0 * C)
	# return the eye aspect ratio
	return ear

def giro_Z():
	z = round(math.degrees(math.atan((shape[45][1]-shape[36][1])/(shape[45][0]-shape[36][0]))))
	return z

#Para detectar la variacion de angulos se definen los siguientes parametros
angz = 90
prev_angz = 90
fr_cnt = 0   #contador para la cantidad de frames a considerar consecutivos

#Valores dentro de la imagen que representa el centro, puede variar dependiendo del tamaño de la ventana
x_ant = 200
pos_x = 200
ang_x = 0
y_ant = 200
pos_y = 200
ang_y = 0

################################################################################################################
#Se establece la conexion serial
arduino = serial.Serial("COM3", 9600)
time.sleep(2)
################################################################################################################

def arduino_com(ang):
	return

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-p", "--shape-predictor", required=True,
	help="path to facial landmark predictor")
ap.add_argument("-r", "--picamera", type=int, default=-1,
	help="whether or not the Raspberry Pi camera should be used")
args = vars(ap.parse_args())
# initialize dlib's face detector (HOG-based) and then create
# the facial landmark predictor
print("[INFO] loading facial landmark predictor...")
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor(args["shape_predictor"])
# initialize the video stream and allow the cammera sensor to warmup
print("[INFO] camera sensor warming up...")
vs = VideoStream(usePiCamera=args["picamera"] > 0).start()
time.sleep(2.0)

# define two constants, one for the eye aspect ratio to indicate
# blink and then a second constant for the number of consecutive
# frames the eye must be below the threshold for to set off the
# alarm
EYE_AR_THRESH = 0.015
EYE_AR_CONSEC_FRAMES = 10
tolerancia = 0.0028
# initialize the frame counter as well as a boolean used to
# indicate if the alarm is going off
COUNTER = 0

# loop over the frames from the video stream
while True:
	# grab the frame from the threaded video stream, resize it to
	# have a maximum width of 400 pixels, and convert it to
	# grayscale
	frame = vs.read()
	frame = imutils.resize(frame, width=800)
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	# detect faces in the grayscale frame
	rects = detector(gray, 0)
    	# loop over the face detections
	for rect in rects:
		# determine the facial landmarks for the face region, then
		# convert the facial landmark (x, y)-coordinates to a NumPy
		# array
		shape = predictor(gray, rect)
		shape = face_utils.shape_to_np(shape)

		# convert dlib's rectangle to a OpenCV-style bounding box
		# [i.e., (x, y, w, h)], then draw the face bounding box
		(x, y, w, h) = face_utils.rect_to_bb(rect)
		#cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
		# show the face number
		#cv2.putText(frame, "Face #{}".format(1), (x - 10, y - 10),
		#	cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
		# loop over the (x, y)-coordinates for the facial landmarks
		# and draw them on the image
		for (x, y) in shape:
			cv2.circle(frame, (x, y), 0, (0, 0, 255), -1)

		#Para calibrar ligeramente las distancias se usara la relacion pixel por centimetro con una distancia conocida, en este caso la distancia
		#en los extremos de los ojos, o puede ser cualquiera como la nariz, etc
		#Aproximadamente esta distancia es de: 10 cm
		pixel_cm_ratio = dist.euclidean(shape[45], shape[36]) / 10

		# Se trazan los labios
		boca1 = face_utils.FACIAL_LANDMARKS_IDXS['mouth']
		boca1 = shape[boca1[0]:boca1[-1]]
		boca1Hull = cv2.convexHull(boca1)
		cv2.drawContours(frame, [boca1Hull], -1, (0, 0, 255), 1)

		# Se trazan los labios (interior)
		boca2 = face_utils.FACIAL_LANDMARKS_IDXS['inner_mouth']
		boca2 = shape[boca2[0]:boca2[-1]]
		boca2Hull = cv2.convexHull(boca2)
		cv2.drawContours(frame, [boca2Hull], -1, (0, 0, 255), 1)
		
		# Se traza la ceja derecha
		cejaD = face_utils.FACIAL_LANDMARKS_IDXS['right_eyebrow']
		cejaD = shape[cejaD[0]:cejaD[-1]]
		cejaDHull = cv2.convexHull(cejaD)
		cv2.drawContours(frame, [cejaDHull], -1, (0, 0, 255), 1)
		
		# Se traza la ceja izquierda
		cejaI = face_utils.FACIAL_LANDMARKS_IDXS['left_eyebrow']
		cejaI = shape[cejaI[0]:cejaI[-1]]
		cejaIHull = cv2.convexHull(cejaI)
		cv2.drawContours(frame, [cejaIHull], -1, (0, 0, 255), 1)
		
		# Se traza el ojo derecho
		ojoD = face_utils.FACIAL_LANDMARKS_IDXS['right_eye']
		ojoD = shape[ojoD[0]:ojoD[-1]]
		ojoDHull = cv2.convexHull(ojoD)
		cv2.drawContours(frame, [ojoDHull], -1, (0, 0, 255), 1)
		
		# Se trazan el ojo izquierdo
		ojoI = face_utils.FACIAL_LANDMARKS_IDXS['left_eye']
		ojoI = shape[ojoI[0]:ojoI[-1]]
		ojoIHull = cv2.convexHull(ojoI)
		cv2.drawContours(frame, [ojoIHull], -1, (0, 0, 255), 1)
		
		# Se traza la nariz
		nariz = face_utils.FACIAL_LANDMARKS_IDXS['nose']
		nariz1 = shape[nariz[0]:nariz[-1]-5]
		nariz2 = shape[nariz[-1]-6:nariz[-1]]
		nariz1Hull = cv2.convexHull(nariz1)
		nariz2Hull = cv2.convexHull(nariz2)
		cv2.drawContours(frame, [nariz1Hull], -1, (0, 0, 255), 1)
		cv2.drawContours(frame, [nariz2Hull], -1, (0, 0, 255), 1)

		#Para el contacto visual se utilizara un punto de la nariz ubicado entre los ojos
		pos_x = shape[28][0]
		pos_y = shape[28][1]

		#Se calcula la inclinacion de la cabeza considerando dos puntos de los ojos
		angz = 90 + round(math.degrees(math.atan((shape[45][1]-shape[36][1])/(shape[45][0]-shape[36][0]))))
		#print(angz)

		if fr_cnt == 3:
			if abs(angz-prev_angz)>1:
				#print('entra if')
				arduino.write(('z'+str(angz)).encode())
				#flag=0
				#while flag==0:
				#	rawString = arduino.readline()
				#	print(rawString)
				#	if rawString=='Completado\r\n'.encode():
				#		flag=1
				prev_angz = angz

			if abs(pos_x-x_ant) > 3:
				ang_x = int(round(pos_x*0.45))
				arduino.write(('x'+str(ang_x)).encode())
				print(ang_x)
				x_ant = pos_x

			if abs(pos_y-y_ant) > 3:
				ang_y = int(round(pos_y*0.45))
				print(ang_y)	
				arduino.write(('y'+str(ang_y)).encode())
				x_ant = pos_x	
				
			fr_cnt = 0
		else:
			fr_cnt+=1
		

		#Se traza el menton
		#menton = face_utils.FACIAL_LANDMARKS_IDXS['jaw']
		#menton = shape[menton[0]:menton[-1]]
		#mentonHull = cv2.convexHull(menton)
		#cv2.drawContours(frame, [menton], -1, (0, 0, 255), 1)
		
		#print(ojoD)
		## Para detectar sonrisas
		dist_smile = ((shape[48][0]-shape[54][0])**2+(shape[48][0]-shape[54][1])**2)**0.5
		dist_smile = dist_smile / pixel_cm_ratio
		#print(dist_smile)
		#diff_smile = dist_smile - dist_smile0
		if dist_smile>7:
			cv2.putText(frame, "Sonrisa", (x - 100, y - 50),
				cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 255, 0), 2)
		
		## Para detectar movimiento de las cejas
		dist_cejaD = ((shape[19][0]-shape[27][0])**2+(shape[19][1]-shape[27][1])**2)**0.5
		dist_cejaD = dist_cejaD / pixel_cm_ratio

		dist_cejaI = ((shape[24][0]-shape[27][0])**2+(shape[24][1]-shape[27][1])**2)**0.5
		dist_cejaI = dist_cejaI / pixel_cm_ratio
		#print(dist_cejaD)
		#print(dist_cejaI)

		if dist_cejaD>5 and dist_cejaI>5:
			cv2.putText(frame, "Ambas cejas levantadas", (x - 200, y - 250),
				cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		elif dist_cejaD>5:
			cv2.putText(frame, "ceja derecha levantada", (x - 200, y - 250),
				cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		elif dist_cejaI>5:
			cv2.putText(frame, "ceja izquierda levantada", (x - 200, y - 250),
				cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

		## Para detectar un beso
		dist_labios = ((shape[62][0]-shape[66][0])**2+(shape[62][1]-shape[66][1])**2)**0.5
		dist_labios = dist_labios / pixel_cm_ratio
		#print(dist_labios)
		if dist_smile<5.5 and dist_labios<1:
			cv2.putText(frame, "Beso", (x - 60, y - 50),
				cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 255, 0), 2)

		## Para detectar ojos cerrados
		#dist_ojoD = ((shape[37][0]-shape[41][0])**2+(shape[37][1]-shape[41][1])**2)**0.5
		#dist_ojoI = ((shape[44][0]-shape[46][0])**2+(shape[44][1]-shape[46][1])**2)**0.5
		
		leftEAR = eye_aspect_ratio(ojoI)
		leftEAR = leftEAR / pixel_cm_ratio

		rightEAR = eye_aspect_ratio(ojoD)
		rightEAR = rightEAR / pixel_cm_ratio

		print(leftEAR)
		print(rightEAR)
		#print(dist_ojoD)
		#print(dist_ojoI)

		if leftEAR < EYE_AR_THRESH and leftEAR - rightEAR < -tolerancia:
			COUNTER += 1
			# if the eyes were closed for a sufficient number of
			# then sound the alarm
			if COUNTER >= EYE_AR_CONSEC_FRAMES:
				cv2.putText(frame, "Guiño izquierda", (x+100, y - 150),
					cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		elif rightEAR < EYE_AR_THRESH and leftEAR - rightEAR > tolerancia:
			COUNTER += 1
			# if the eyes were closed for a sufficient number of
			# then sound the alarm
			if COUNTER >= EYE_AR_CONSEC_FRAMES:
				cv2.putText(frame, "Guiño derecha", (x-300, y - 150),
					cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		elif leftEAR < EYE_AR_THRESH and rightEAR < EYE_AR_THRESH:
			COUNTER += 1
			# if the eyes were closed for a sufficient number of
			# then sound the alarm
			if COUNTER >= EYE_AR_CONSEC_FRAMES:
				cv2.putText(frame, "Ambos ojos cerrados", (x, y - 150),
					cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		else:
			COUNTER = 0

		#if dist_ojoD<15 and dist_ojoI<15:
		#	cv2.putText(frame, "Ambas ojos cerrados", (x - 150, y - 150),
		#		cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		#elif dist_ojoD<15:
		#	cv2.putText(frame, "ojo derecho cerrado", (x + 50, y - 150),
		#		cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
		#elif dist_ojoI<15:
		#	cv2.putText(frame, "ojo izquierdo cerrado", (x-250, y - 150),
		#		cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

		#cv2.circle(frame, (shape[54][0], shape[54][1]), 5, (0, 255, 0), -1)
		#cv2.circle(frame, (shape[48][0], shape[48][1]), 5, (0, 255, 0), -1)  
		#print(shape[50][1])
		# show the frame
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF
 
	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break
# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()

## Para ejecutar: python video_facial_landmarks.py --shape-predictor shape_predictor_68_face_landmarks.dat

## Posibles mejoras a implementar: 
## -agregarle una relacion pixel cm PPC o PPI para que las distancias sean mas representativas
## -buscar la forma de que el sistema de coordenadas se centre en un punto, por ej de la nariz
##	de esta forma se consigue mas generalidad en las coordenadas de los puntos del rostro
## -implementar la deteccion de expresiones para mas de una persona a la vez