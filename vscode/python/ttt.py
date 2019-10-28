import os 
import cv2 as cv
import numpy as np
from sklearn.preprocessing import LabelBinarizer


filePath = '/Users/liyixun/Downloads/UCF-101/'
l = os.listdir(filePath)
l.sort()
n = np.array(l)
n.reshape((1,len(l))
#n = LabelBinarizer().fit_transform(n)
# print(n,n.shape)
# print(y,y.shape)
for i in l:
    fp = filePath + i
    document = os.listdir(fp)
    print(fp)
    print(document)

def vist_doc(filePath):
    doc = os.listdir(filePath)
    l.sort()
    n = np.array(l)
    n.reshape((1,101))
    y = LabelBinarizer().fit_transform(n)
    for i in l:
        fp = filePath + i
        document = os.listdir(fp)
        print(fp)
        print(document)
    return y