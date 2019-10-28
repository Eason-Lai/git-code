import tensorflow as tf
import data
x_k = np.zero()

Epoch = 10
Batch_size = 200
Batch = int(Y.shape[0] / Batch_size)
rate = 0.9

#data_x为各视频文件路径，data_y为转换后的标记
data_x,data_y = data.get_file('/Users/liyixun/Downloads/UCF-101/')
current = 0
epoch_now = 0
k = 5
data_x,data_y = shuffle_data(data_x,data_y)
train_x,train_y,test_x,test_y = train_test(data_x,data_y,rate)
Size = train_x.shape[0]

# def next_batch(n):
#     num_preprocess_threads = 16
#     images, label_batch = tf.train.shuffle_batch(
#         [image, label],
#         batch_size=Batch_size,
#         num_threads=num_preprocess_threads,
#         capacity=min_queue_examples + 3 * batch_size,
#         min_after_dequeue=min_queue_examples)
#     # Display the training images in the visualizer.
#     tf.image_summary('images', images)
#     return images, tf.reshape(label_batch, [batch_size])
def next_batch(n):
    if (n+current>=Size):
        current = 0
        data_x,data_y = shuffle_data(data_x,data_y)
        train_x,train_y,test_x,test_y = train_test(data_x,data_y,rate)
        epoch_now = epoch_now + 1 
    current = current + n
    return  data.load_data(train_x[current-n:current],train_y[current-n:current],k)

def next_test(n):
    if (n >= test_x.shape[0]):
        print('Error,n>test_size')
    test_x,test_y = shuffle_data(test_x,test_y)
    return data.load_data(test_x[0:n],test[0:y],k)

#k个段，各段划分图片集
def slice_k(slice_x,slice_y,ki):
    n = tf.shape(data_x)[0]
    ret_x = tf.slice(data_x,[0,ki,0,0,0],[n,1,160,160,3])
    ret_x = tf.reshape(ret_x,[-1,160,160,3])
    return ret_x

def compute_accuracy(v_xs,v_ys):
    global prediction
    y_pre = sess.run(prediction,feed_dict={xs:v_xs,keep_prob:1})
    correct_prediction = tf.equal(tf.argmax(y_pre,1),tf.argmax(v_ys,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction,tf.float32))
    result = sess.run(accuracy,feed_dict={xs:v_xs,ys:v_ys,keep_prob:1})
    return result
 
def weight_variable(shape):
    initial = tf.random.truncated_normal(shape,stddev=0.01)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1,shape=shape)
    return tf.Variable(initial)
 
def conv2d(x,W):
    return tf.nn.conv2d(x,W,strides=[1,1,1,1],padding='SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x,ksize=[1,2,2,1],strides=[1,2,2,1],padding='SAME')

xs = tf.compat.v1.placeholder(tf.float32,[None,160,160,3]) #160*160
ys = tf.compat.v1.placeholder(tf.float32,[None,101])
keep_prob = tf.compat.v1.placeholder(tf.float32) 
#x_image = tf.reshape(xs,[-1,160,160,3])
## conv1 layer ##
W_conv1 = weight_variable([5,5,3,32]) # patch 5*5,insize 1(输入的高度or图片通道数),outsize 32(输出的高度or卷积的层数)
b_conv1 = bias_variable([32])  # 
h_conv1 = tf.nn.relu(conv2d(xs,W_conv1) + b_conv1) # outputsize 160*160*32
h_pool1 = max_pool_2x2(h_conv1) # outputsize 80*80*32
## conv2 layer ##
W_conv2 = weight_variable([5,5,32,64]) # patch 5*5,insize 32(输入的高度or图片通道数),outsize 64(输出的高度or卷积的层数)
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1,W_conv2) + b_conv2) # outputsize 80*80*64
h_pool2 = max_pool_2x2(h_conv2) # outputsize 40*40*64
## func1 layer ## 
W_fc1 = weight_variable([40*40*64,1024]) 
b_fc1 = bias_variable([1024])
h_pool2_flat = tf.reshape(h_pool2,[-1,40*40*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat,W_fc1)+b_fc1)
h_fc1_drop = tf.nn.dropout(h_fc1,0.5)
## func2 layer ##
W_fc2 = weight_variable([1024,101]) 
b_fc2 = bias_variable([101])
prediction = tf.nn.softmax(tf.matmul(h_fc1_drop,W_fc2)+b_fc2)

cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys*tf.math.log(prediction),reduction_indices=[1]))

train_step = tf.compat.v1.train.AdamOptimizer(0.0001).minimize(cross_entropy)

sess = tf.compat.v1.Session()
 
sess.run(tf.compat.v1.global_variables_initializer())

for e in range(Epoch):
    for bs in range(Batch):
            batch_xs,batch_ys = next_batch(Batch_size)
        for kc in range(k):
            train_xs = slice_k(batch_xs,kc)
            sess.run(train_step,feed_dict={xs:train_xs,ys:batch_ys,keep_prob:0.8})
        if bs % 10 == 0:
            test_xs,test_ys = next_batch(100)
            print(compute_accuracy(test.x,test.y)