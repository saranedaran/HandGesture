# import necessary packages for hand gesture recognition project using Python OpenCV

import cv2
import numpy as np
import mediapipe as mp
import tensorflow as tf
from tensorflow.keras.models import load_model
import mqtt
# from joint import *


# initialize mediapipe
mpHands = mp.solutions.hands
hands = mpHands.Hands(max_num_hands=1, min_detection_confidence=0.7)
mpDraw = mp.solutions.drawing_utils
# Load the gesture recognizer model
model = load_model('mp_hand_gesture')

# Load class names
f = open('gesture.names', 'r')
classNames = f.read().split('\n')
f.close()
print(classNames)

# Initialize the webcam for Hand Gesture Recognition Python project
cap = cv2.VideoCapture(0)

while True:
	# Read each frame from the webcam
	_, frame = cap.read()
	x , y, c = frame.shape

	# Flip the frame vertically
	frame = cv2.flip(frame, 1)
	framergb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
	# Get hand landmark prediction
	result = hands.process(framergb)

	className = ''
	count = 0

	# post process the result
	if result.multi_hand_landmarks:
		landmarks = []
		for handslms in result.multi_hand_landmarks:
			for lm in handslms.landmark:
				# print(id, lm)
				lmx = int(lm.x * x)
				lmy = int(lm.y * y)

				landmarks.append([lmx, lmy])

		
		


		# Drawing landmarks on frames
		mpDraw.draw_landmarks(frame, handslms, mpHands.HAND_CONNECTIONS)

		# print(landmarks)
		# Predict gesture in Hand Gesture Recognition project
		prediction = model.predict([landmarks])
		print(prediction)
		classID = np.argmax(prediction)
		className = classNames[classID]

		if className == "thumbs up":
			mqtt.send("robo1", "forward")
		elif className == "thumbs down":
			mqtt.send("robo1", "reverse")
		elif className == "call me":
			mqtt.send("robo1", "left")
		elif className == "rock":
			mqtt.send("robo1", "right")
		elif className == "stop":
			mqtt.send("robo1", "stop")

		# show the prediction on the frame
		cv2.putText(frame, className, (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255), 2, cv2.LINE_AA)
		cv2.putText(frame, mqtt.received, (10, 200), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2, cv2.LINE_AA)
		

	# Show the final output
	cv2.imshow("Output", frame)

	if cv2.waitKey(1) == ord('q'):
		break

# release the webcam and destroy all active windows
cap.release()
cv2.destroyAllWindows()