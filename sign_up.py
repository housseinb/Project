import cv2
import os
from tkinter import simpledialog, messagebox

# Paths and initializations
prototxt_path = cv2.data.haarcascades + "haarcascade_frontalface_default.xml"
face_cascade = cv2.CascadeClassifier(prototxt_path)

KNOWN_FACES_DIR = "C:\\Users\\hbarb\\Documents\\2eme\\Houssein Work\\Nova_Up\\known_faces"

def capture_and_save_photo():
    video_capture = cv2.VideoCapture(0)

    while True:
        ret, frame = video_capture.read()

        if not ret:
            break

        cv2.putText(frame, "Position yourself and press c", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        cv2.imshow("Capture - Face Position", frame)

        if cv2.waitKey(1) & 0xFF == ord('c'):
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            faces_detected = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

            for (x, y, w, h) in faces_detected:
                face_roi = gray[y:y+h, x:x+w]
                name = simpledialog.askstring("Enter Your Name", "Please enter your name:")

                if name:
                    img_name = os.path.join(KNOWN_FACES_DIR, f"{name}.jpg")
                    cv2.imwrite(img_name, frame)
                    messagebox.showinfo("Success", f"Photo captured and saved as {name}.jpg!")
                    break
                else:
                    messagebox.showwarning("Input Error", "Name is required to save the photo!")

        if cv2.waitKey(1) & 0xFF == ord("q"): 
            break

    video_capture.release()
    cv2.destroyAllWindows()

# Initialize Sign Up
capture_and_save_photo()