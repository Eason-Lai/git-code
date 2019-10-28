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

def get_file(filePath):
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
            # r = get_image(fp+'/'+j,5) 
            # r = r.reshape(1,5,160,160,3)
            # print(r.shape)
            # print(fp+'/'+j)
            r = fp + '/' + j
            if Flag == True:
                data_x = r
                data_y = y[count]
                Flag = False
            else:
                data_x = np.concatenate((data_x,r),axis=0)
                data_y = np.concatenate((data_y,y[count]),axis=0)
            #print(data_x.shape)
        count = count+1
    #print(data_x.shape)
    return data_x,data_y

def shuffle_data(data_x,data_y):
    state=np.random.get_state()
    data_x = np.random.permutation(data_x)
    np.random.set_state(state)
    data_y = np.random.permutation(data_y)
    return data_x,data_y

def shuffle_batch(image,label,batch_size):
    num_preprocess_threads = 16
    images, label_batch = tf.train.shuffle_batch(
    [image, label],
    batch_size=batch_size,
    num_threads=num_preprocess_threads,
    capacity=min_queue_examples + 3 * batch_size,
    min_after_dequeue=min_queue_examples)

    # Display the training images in the visualizer.
    tf.image_summary('images', images)

    return images, tf.reshape(label_batch, [batch_size])

def train_test(data_x,data_y,rate):
    data_x,data_y = shuffle_data(data_x,data_y)
    train_x = data_x[0:int(rate*data_x.shape[0])]
    test_x = data_x[int(rate*data_x.shape[0]):]
    train_y = data_y[0:int(rate*data_y.shape[0])]
    test_y = data_y[int(rate*data_y.shape[0]):]
    return train_x,train_y,test_x,test_y

def load_data(Files,Labels,k):
    count = 0
    Flag = True
    for i in Files:
        r = get_image(i,k)
        if Flag == True:
                X = r
                Y = Labels[count]
                Flag = False
        else:
            X = np.concatenate((X,r),axis=0)
            Y = np.concatenate((Y,Labels[count]),axis=0)
    count = count + 1
    return X,Y

#load_data('/Users/liyixun/Downloads/UCF-101/')
#load_data('/Users/liyixun/Downloads/ucf/')