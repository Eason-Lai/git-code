import cv2 as cv
import numpy as np
import random 
import os
from sklearn.preprocessing import LabelBinarizer

#随机截取固定大小图片（160*160）
def crop(img,ch,cw,h,w):
    y = random.randint(1, h-ch)
    x = random.randint(1, w-cw)
    cropImg = img[(y):(y + ch), (x):(x + cw)]
    return cropImg

#从视频数据中随机获取k张图片并转化为数组
def get_image(filename,k):
    cap = cv.VideoCapture(filename)
    isOpened = cap.isOpened()  ##判断视频是否打开
    width = int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))
    frame_num = int(cap.get(cv.CAP_PROP_FRAME_COUNT))
    n = int(frame_num / k)
    s = np.arange(k)*n + np.random.randint(n,size=k)
    r = np.ndarray(shape=[k,160,160,3])
    j = 0
    for i in s:
        cap.set(cv.CAP_PROP_POS_FRAMES,i)
        (flag,frame)=cap.read()
        if flag == True :
            frame = crop(frame,160,160,240,320)
            img = frame.astype(np.float32)
            r[j] = img
            j = j + 1
            #cv.imwrite("/Users/liyixun/Desktop/Images/image"+str(i)+".jpg",frame,[cv.IMWRITE_JPEG_CHROMA_QUALITY,100])  ##命名 图片 图片质量
    cap.release()
    return r

def load_data(filePath):
    l = os.listdir(filePath)
    l.sort()
    n = np.array(l)
    n.reshape((1,len(l)))
    y = LabelBinarizer().fit_transform(n)
    count = 0
    Flag = True
    for i in l:
        fp = filePath + i
        document = os.listdir(fp)
        document.sort()
        for j in document: 
            r = get_image(fp+'/'+j,5) 
            print(fp+'/'+j)
            if Flag == True:
                data_x = r
                data_y = y[count]
                Flag = False
            else:
                data_x = np.concatenate((data_x,r),axis=0)
                data_y = np.concatenate((data_y,y[count]),axis=0)
            print(data_x.shape)
        count = count+1
    print(data_x.shape)
    return data_x,data_y



#load_data('/Users/liyixun/Downloads/UCF-101/')
load_data('/Users/liyixun/Downloads/ucf/')