import cv2
from PIL import Image
import time
import numpy as np


# cv2.namedWindow("Python Webcam Screenshot App --> click escape key to end")
# for x in range(0,1000):

#cv2.imshow("Python Webcam Screenshot App --> click escape key to end", frame)
im = Image.open(r"frame.png")
px = list(im.getdata(1))

'''
array = np.array(px, dtype=np.uint8)
new_image = Image.fromarray(array)
new_image.save(r"new.png")
'''

print(px)

f = open("frame_RGB_values.txt", "w")
f.write("")
f.close()


send = ""

f = open("frame_RGB_values.txt", "a")
for x in range(len(px)):
    if (px[x]<155):
        f.write("0,")
    else:
        f.write("1,")
    #f.write(str(px[x])+",")
    #send += str(px[x])[1:]
    if x%im.width==0 and x!=0:
        f.write("\n")
f.close()
'''
url = "https://livestream.dhyeyb.repl.co/getRGBvals.php"
#url = 'https://livestreamdb23.000webhostapp.com/getRGBvals.php'
myobj = {"rgbVals": send}
# print("Frame Sent")
time.sleep(0.4)
'''
#cv2.destroyAllWindows()
