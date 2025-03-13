import cv2
import numpy as np
import os
import tkinter as tk
from tkinter import messagebox
from tkinter import simpledialog

# Paths and initializations
prototxt_path = cv2.data.haarcascades + "haarcascade_frontalface_default.xml"
face_cascade = cv2.CascadeClassifier(prototxt_path)

recognizer = cv2.face.LBPHFaceRecognizer_create()
KNOWN_FACES_DIR = "C:\\Users\\hbarb\\Documents\\programming\\reconassance facial\\known_faces"
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
        print(f"Training with {len(faces)} faces...") 
        recognizer.train(faces, np.array(labels))

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

        if cv2.waitKey(1) & 0xFF == ord('q'): 
            break

    video_capture.release()
    cv2.destroyAllWindows()

def login():
    video_capture = cv2.VideoCapture(0)

    while True:
        ret, frame = video_capture.read()

        if not ret:
            break

        # Display the camera feed for the user to position themselves
        cv2.putText(frame, "Position yourself for login", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        # Show the live feed to the user
        cv2.imshow("Login - Face Recognition", frame)

        # Wait for the user to position themselves
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

            # Display result after recognition
            if name != "Inconnu":
                messagebox.showinfo("Login", f"Welcome {name}!")
                break
            else:
                messagebox.showinfo("Login", "Face not recognized. Please register first.")
                break

        # Press 'q' to quit the login attempt
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    video_capture.release()
    cv2.destroyAllWindows()

# Tkinter GUI for the buttons
def create_gui():
    window = tk.Tk()
    window.title("Face Registration and Login")
    window.configure(bg="#f0f0f0")

    # Set window size and position to center it on the screen
    window.geometry("1293x771")
    window.eval('tk::PlaceWindow %s center' % window.winfo_toplevel())

    # Title label with customized style
    title_label = tk.Label(window, text="Face Recognition", font=("Arial", 16, "bold"), bg="#f0f0f0")
    title_label.pack(pady=20)

    # Sign up button with styling
    capture_button = tk.Button(window, text="Sign Up", command=capture_and_save_photo, width=20, height=2, bg="#4CAF50", fg="white", font=("Arial", 12))
    capture_button.pack(pady=10)

    # Sign in button with styling
    login_button = tk.Button(window, text="Sign In", command=login, width=20, height=2, bg="#2196F3", fg="white", font=("Arial", 12))
    login_button.pack(pady=10)

    window.mainloop()

# Initialize
load_known_faces()
create_gui()
