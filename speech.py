import speech_recognition as sr

def capture_speech():
    recognizer = sr.Recognizer()

    with sr.Microphone() as source:
        print("Say something:")
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

    try:
        text = recognizer.recognize_google(audio)
        print(f"You said: {text}")
        with open("speech_output.txt", "w") as f:
            f.write(text)
        return text
    except sr.UnknownValueError:
        print("Sorry, I could not understand your speech.")
        with open("speech_output.txt", "w") as f:
            f.write("Error: Could not understand speech.")
        return ""
    except sr.RequestError:
        print("Sorry, the service is down.")
        with open("speech_output.txt", "w") as f:
            f.write("Error: Service down.")
        return ""

if __name__ == "__main__":
    capture_speech()
