import cv2
import numpy as np
import os
from tkinter import messagebox

# Paths and initializations
prototxt_path = cv2.data.haarcascades + "haarcascade_frontalface_default.xml"
face_cascade = cv2.CascadeClassifier(prototxt_path)

recognizer = cv2.face.LBPHFaceRecognizer_create()
KNOWN_FACES_DIR = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\known_faces"
labels = []
faces = []
label_map = {}

def load_known_faces():
    global labels, faces, label_map
    current_label = 0
    for filename in os.listdir(KNOWN_FACES_DIR):
        path = os.path.join(KNOWN_FACES_DIR, filename)
        image = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
        if image is not None:
            faces.append(image)
            labels.append(current_label)
            label_map[current_label] = os.path.splitext(filename)[0]
            current_label += 1
        else:
            print(f"Failed to load {filename}")

    if faces:
        recognizer.train(faces, np.array(labels))

def login():
    video_capture = cv2.VideoCapture(0)

    while True:
        ret, frame = video_capture.read()

        if not ret:
            break

        cv2.putText(frame, "Position yourself for login", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv2.imshow("Login - Face Recognition", frame)

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces_detected = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        if len(faces_detected) > 0:
            for (x, y, w, h) in faces_detected:
                face_roi = gray[y:y+h, x:x+w]
                label, confidence = recognizer.predict(face_roi)
                name = "Inconnu"

                if confidence < 100:
                    name = label_map.get(label, "Inconnu")

                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
                cv2.putText(frame, name, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)

            if name != "Inconnu":
                messagebox.showinfo("Login", f"Welcome {name}!")
                break
            else:
                messagebox.showinfo("Login", "Face not recognized. Please register first.")
                break

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    video_capture.release()
    cv2.destroyAllWindows()

# Initialize
load_known_faces()
login()
