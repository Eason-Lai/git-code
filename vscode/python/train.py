import tensorflow as tf
import data

Epoch = 10
Batch_size = 200
min_queue_examples = 1000
rate = 0.9
k = 5
current = 0
epoch_now = 0

# data_x为各视频文件路径，data_y为转换后的标记
data_x, data_y = data.load_data('/Users/liyixun/Downloads/UCF-101/',k)
data_x, data_y = data.shuffle_data(data_x, data_y)
#划分训练集和测试集
train_x, train_y, test_x, test_y = data.train_test(data_x, data_y, rate)
#转化为Tensor
train_x = tf.cast(train_x, tf.float32)
train_y = tf.cast(train_y, tf.float32)
test_x = tf.cast(test_x, tf.float32)
test_y = tf.cast(test_y, tf.float32)

data_x, data_y = data.shuffle_data(data_x, data_y)
train_x, train_y, test_x, test_y = data.train_test(data_x, data_y, rate)
Size = train_x.shape[0]
Batch = int(Size / Batch_size)
input_queue = tf.train.slice_input_producer([train_x, train_y], shuffle=False)
# 将队列中数据打乱后再读取出来
image_batch, label_batch = tf.train.shuffle_batch(input_queue, batch_size=Batch_size, num_threads=16, capacity=Batch_size *3+5+min_queue_examples, min_after_dequeue=min_queue_examples, enqueue_many=False, allow_smaller_final_batch=False)


def next_test(n,current):
    len = test_x.shape[0]
    if (current+n > len):
        current = 0
    t_x = tf.slice(test_x, [current, 2, 0, 0, 0], [n, 1, 160, 160, 3])
    t_y = tf.slice(test_y, [current, 0], [current+n, 101])
    current = current+n
    return t_x, t_y

# k个段，各段划分图片集
def slice_k(slice_x, ki):
    n = tf.shape(slice_x)[0]
    ret_x = tf.slice(slice_x, [0, ki, 0, 0, 0], [n, 1, 160, 160, 3])
    ret_x = tf.reshape(ret_x, [n, 160, 160, 3])
    return ret_x


def compute_accuracy(v_xs, v_ys):
    global prediction
    y_pre = sess.run(prediction, feed_dict={xs: v_xs, keep_prob: 1})
    correct_prediction = tf.equal(tf.argmax(y_pre, 1), tf.argmax(v_ys, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    result = sess.run(accuracy, feed_dict={xs: v_xs, ys: v_ys, keep_prob: 1})
    return result


def weight_variable(shape):
    initial = tf.random.truncated_normal(shape, stddev=0.01)
    return tf.Variable(initial)


def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)


def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')


def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')


xs = tf.compat.v1.placeholder(tf.float32, [None, 160, 160, 3])  # 160*160
ys = tf.compat.v1.placeholder(tf.float32, [None, 101])
keep_prob = tf.compat.v1.placeholder(tf.float32)
# x_image = tf.reshape(xs,[-1,160,160,3])
## conv1 layer ##
# patch 5*5,insize 1(输入的高度or图片通道数),outsize 32(输出的高度or卷积的层数)
W_conv1 = weight_variable([5, 5, 3, 32])
b_conv1 = bias_variable([32])  #
h_conv1 = tf.nn.relu(conv2d(xs, W_conv1) + b_conv1)  # outputsize 160*160*32
h_pool1 = max_pool_2x2(h_conv1)  # outputsize 80*80*32
## conv2 layer ##
# patch 5*5,insize 32(输入的高度or图片通道数),outsize 64(输出的高度or卷积的层数)
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)  # outputsize 80*80*64
h_pool2 = max_pool_2x2(h_conv2)  # outputsize 40*40*64
## func1 layer ##
W_fc1 = weight_variable([40*40*64, 1024])
b_fc1 = bias_variable([1024])
h_pool2_flat = tf.reshape(h_pool2, [-1, 40*40*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1)+b_fc1)
h_fc1_drop = tf.nn.dropout(h_fc1, 0.5)
## func2 layer ##
W_fc2 = weight_variable([1024, 101])
b_fc2 = bias_variable([101])
prediction = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2)+b_fc2)

cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys *
                               tf.math.log(prediction), reduction_indices=[1]))

train_step = tf.compat.v1.train.AdamOptimizer(0.0001).minimize(cross_entropy)

# sess = tf.compat.v1.Session()
with tf.Session() as sess:
    sess.run(tf.compat.v1.global_variables_initializer())
    # 线程的协调器
    coord = tf.train.Coordinator()
    # 开始在图表中收集队列运行器
    threads = tf.train.start_queue_runners(sess, coord)
    for e in range(Epoch):
        for bs in range(Batch):
            batch_xs, batch_ys = sess.run([image_batch, label_batch])
            for kc in range(k):
                train_xs = slice_k(batch_xs, kc)
                sess.run(train_step, feed_dict={xs: train_xs, ys: batch_ys, keep_prob: 0.8})
            if bs % 10 == 0:
                test_xs, test_ys = next_test(100,current)
                print(compute_accuracy(test.xs, test.ys))
    # 请求线程结束
    coord.request_stop()
    # 等待线程终止
    coord.join(threads)