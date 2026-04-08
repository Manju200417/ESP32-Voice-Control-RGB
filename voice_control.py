import queue
import sounddevice as sd
import json
import requests
from vosk import Model, KaldiRecognizer

ESP_IP = "10.179.129.206"

q = queue.Queue()

def callback(indata, frames, time, status):
    q.put(bytes(indata))

model = Model("/Users/manjunathalagawadi/Documents/PlatformIO/voice_model")

recognizer = KaldiRecognizer(
    model, 16000,
    '["green on","green off","blue on","blue off","red on","red off","all on","all off","blink","stop"]'
)

with sd.RawInputStream(samplerate=16000, blocksize=8000,
                       dtype='int16', channels=1, callback=callback):

    print("🎤 Speak commands")

    while True:
        data = q.get()

        if recognizer.AcceptWaveform(data):
            result = json.loads(recognizer.Result())
            text = result.get("text", "")

            print("You said:", text)

            try:
                if "green on" in text:
                    requests.get(f"http://{ESP_IP}/green_on")

                elif "green off" in text:
                    requests.get(f"http://{ESP_IP}/green_off")

                elif "blue on" in text:
                    requests.get(f"http://{ESP_IP}/blue_on")

                elif "blue off" in text:
                    requests.get(f"http://{ESP_IP}/blue_off")

                elif "red on" in text:
                    requests.get(f"http://{ESP_IP}/red_on")

                elif "red off" in text:
                    requests.get(f"http://{ESP_IP}/red_off")

                elif "all on" in text:
                    requests.get(f"http://{ESP_IP}/all_on")

                elif "all off" in text:
                    requests.get(f"http://{ESP_IP}/all_off")

                elif "blink" in text:
                    requests.get(f"http://{ESP_IP}/blink_all")

                elif "stop" in text:
                    requests.get(f"http://{ESP_IP}/stop_blink")

            except:
                print("ESP32 not reachable")