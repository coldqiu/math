# 电影评论文本分类
# https://tensorflow.google.cn/tutorials/keras/text_classification?hl=zh-cn
# 此笔记本（notebook）使用评论文本将影评分为积极（positive）或消极（nagetive）两类。
# 这是一个二元（binary）或者二分类问题，一种重要且应用广泛的机器学习问题。
import tensorflow as tf
from tensorflow import keras
import matplotlib.pyplot as plt
import numpy as np

# 下载数据集 该数据已经经过预处理，评论（单词序列）已经被转换为整数序列，其中每个整数表示字典中的特定单词。
imdb = keras.datasets.imdb

(train_data, train_labels), (test_data,
                             test_labels) = imdb.load_data(num_words=10000)
# 参数 num_words=10000 保留了训练数据中最常出现的 10,000 个单词。为了保持数据规模的可管理性，低频词将被丢弃。
#

# 探索数据
# 让我们花一点时间来了解数据格式。该数据集是经过预处理的：每个样本都是一个表示影评中词汇的整数数组。每个标签都是一个值为 0 或 1 的整数值，其中 0 代表消极评论，1 代表积极评论。
print("Training entries: {}, labels: {}".format(
    len(train_data), len(train_labels)))
# print(train_data[0])
# print("train_labels[0]:{}".format(train_labels[0]))
print("x1{}, x2{}".format(len(train_data[0]), len(train_data[1])))


# 将整数转换会单词
# 一个映射单词到整数索引的词典
word_index = imdb.get_word_index()

# 保留第一个索引
word_index = {k: (v+3) for k, v in word_index.items()}
word_index["<PAD>"] = 0
word_index["<START>"] = 1
word_index["<UNK>"] = 2  # unknown
word_index["<UNUSED>"] = 3

reverse_word_index = dict([(value, key)
                          for (key, value) in word_index.items()])


def decode_review(text):
    return ' '.join([reverse_word_index.get(i, '?') for i in text])

# 解释下tensorflow 教程中 “电影评论文本分类” 章节里的 上面这段代码

# print(decode_review(train_data[0]))

# 准备数据
# 影评——即整数数组必须在输入神经网络之前转换为张量。(神经网络的输入必须是统一的长度)这种转换可以通过以下两种方式来完成：


print(tf.__version__)
train_data = keras.preprocessing.sequence.pad_sequences(train_data,
                                                        value=word_index["<PAD>"],
                                                        padding='post',
                                                        maxlen=256)

test_data = keras.preprocessing.sequence.pad_sequences(test_data,
                                                       value=word_index["<PAD>"],
                                                       padding='post',
                                                       maxlen=256)

print(len(train_data[0]), len(train_data[1]))
print(train_data[0])


# 构建模型
# 输入形状是用于电影评论的词汇数目（10,000 词）
vocab_size = 10000

model = keras.Sequential()
model.add(keras.layers.Embedding(vocab_size, 16))
model.add(keras.layers.GlobalAveragePooling1D())
model.add(keras.layers.Dense(16, activation='relu'))
model.add(keras.layers.Dense(1, activation='sigmoid'))

model.summary()

# 隐层单元 损失函数与优化器 不理解

# 配置模型来使用优化器和损失函数：
model.compile(optimizer='adam',
              loss='binary_crossentropy',
              metrics=['accuracy'])

# 分离训练和验证的数据
x_val = train_data[:10000]
partial_x_train = train_data[10000:]

y_val = train_labels[:10000]
partial_y_train = train_labels[10000:]


# 训练模型
history = model.fit(partial_x_train,
                    partial_y_train,
                    # epochs=40
                    epochs=20,
                    batch_size=512,
                    validation_data=(x_val, y_val),
                    verbose=1)


# 评估模型
results = model.evaluate(test_data,  test_labels, verbose=2)

print(results)

# 创建图表，一个准确率（accuracy）和损失值（loss）随时间变化的图表
history_dict = history.history
history_dict.keys()

acc = history_dict['accuracy']
val_acc = history_dict['val_accuracy']
loss = history_dict['loss']
val_loss = history_dict['val_loss']

epochs = range(1, len(acc) + 1)

# “bo”代表 "蓝点"
plt.plot(epochs, loss, 'bo', label='Training loss')
# b代表“蓝色实线”
plt.plot(epochs, val_loss, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()

plt.show()

# news : 商家反馈 误导性的AI产品评论会影响产品在亚马逊上的销售
# 在亚马逊平台上销售的商家们称误导性的人工智能产品评论摘要可能会对他们的销售造成威胁。
# 该平台最近开始使用人工智能将数十亿条评论转换成简短的摘要，以减轻客户反馈页面的冗余和滚动浏览页面的任务。
