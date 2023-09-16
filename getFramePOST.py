import cv2
from PIL import Image
import time
import requests

cam = cv2.VideoCapture(0, cv2.CAP_DSHOW)
cam.set(3, 176)  # 3 is width
cam.set(4, 144)  # 4 is height

# cv2.namedWindow("Python Webcam Screenshot App --> click escape key to end")
# for x in range(0,1000):

while True:
    ret, frame = cam.read()

    if not ret:
        print("failed to grab frame")
        break
    #cv2.imshow("Python Webcam Screenshot App --> click escape key to end", frame)

    k = cv2.waitKey(1)
    if k % 256 == 27:  # ESC pressed
        print("Escape hit, closing...")
        break
    # elif k % 256 == 13:  # 13 is enter pressed
    cv2.imwrite("frame.png", frame)
    #print("Image Updated!")
    time.sleep(0.1)

    im = Image.open(r"frame.png")
    px = list(im.getdata())
    print(px)

    f = open("frame_RGB_values.txt", "w")
    f.write("")
    f.close()

    send = ""

    f = open("frame_RGB_values.txt", "a")
    for x in px:
        f.write(str(x)+"\n")
        send += str(x)[1:]
    f.close()

    url = "https://livestream.dhyeyb.repl.co/getRGBvals.php"
    #url = 'https://livestreamdb23.000webhostapp.com/getRGBvals.php'
    myobj = {"rgbVals": send}

    x = requests.post(url, data=myobj)
    # print("Frame Sent")
    time.sleep(0.4)

cam.release()
cv2.destroyAllWindows()
