import cv2
from PIL import Image
import time
import numpy as np

im = Image.open(r"frame.png")
px = list(im.getdata(1))

'''
array = np.array(px, dtype=np.uint8)
new_image = Image.fromarray(array)
new_image.save(r"new.png")
'''

print(px)

f = open("frame_values.txt", "w")
f.write("")
f.close()


f = open("frame_values.txt", "a")
for x in range(len(px)):
    if x%im.width == 0:
        f.write("{")

    if x%im.width == (im.width-1):
        if (px[x]<155):
            f.write("1},\n")
        else:
            f.write("0},\n")

    else:
        if (px[x]<155):
            f.write("1,")
        elif x%im.width != (im.width-1):
            f.write("0,")
f.close()
