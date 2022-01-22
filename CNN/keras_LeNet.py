#!/usr/bin/env python

"""
Trains a simple convnet on the HASY dataset.
Gets to 77.77% test accuracy after 1 epoch.
790 seconds per epoch on a GeForce 940MX GPU.
"""

#%%

import tensorflow as tf
import numpy as np
import keras
from keras.models import Sequential
from keras.layers import Conv2D, Dense, MaxPool2D, Dropout, Flatten
from keras import callbacks
from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential
from keras.optimizers import adam_v2
from keras.callbacks import ReduceLROnPlateau
import matplotlib.pyplot as plt
import seaborn as sns
import hasy.hasy_tools as ht
import pdb
import keras_tuner as kt


#%%
np.random.seed(0)  # make sure results are reproducible
tf.random.set_seed(0)  # make sure results are reproducible

if __name__ == "__main__":
    batch_size = 256
    nb_epoch = 10

    # input image dimensions
    img_rows, img_cols = ht.img_rows, ht.img_cols

    # Load data
    fold = 1
    hasy_data = ht.load_data(mode=f"fold-{fold}", image_dim_ordering="tf")

    x_train = hasy_data["x_train"]
    y_train = hasy_data["y_train"]
    x_test = hasy_data["x_test"]
    y_test = hasy_data["y_test"]

    # One-Hot encoding
    y_train = np.eye(ht.n_classes)[y_train.squeeze()]
    y_test = np.eye(ht.n_classes)[y_test.squeeze()]

    # Preprocessing
    x_train = ht.preprocess(x_train)
    x_test = ht.preprocess(x_test)

    # Define model
    # def build_model(hp):
    model = Sequential()
    model.add(Conv2D(filters=32, kernel_size=(5, 5), padding='same', activation='relu', input_shape=(32, 32, 1)))
    model.add(MaxPool2D(strides=2))
    model.add(Conv2D(filters=48, kernel_size=(5, 5), padding='valid', activation='relu'))
    model.add(MaxPool2D(strides=2))
    model.add(Flatten())
    # model.add(Dense(256, activation='relu'))
    # model.add(Dense(
    #     hp.Choice('units', [128, 256, 512]),
    #     activation='relu'))
    model.add(Dense(84, activation='relu'))
    model.add(Dense(369, activation='softmax'))
    # model.build()
    # model.summary()
    # adam1 = adam_v2(lr=5e-4)
    model.compile(loss='categorical_crossentropy', metrics=['accuracy'])

        # return model


    # tuner = kt.RandomSearch(
    #     build_model,
    #     objective='val_accuracy',
    #     max_trials=5)


    # reduce_lr = ReduceLROnPlateau(monitor='val_accuracy',
    #                               patience=3,
    #                               verbose=1,
    #                               factor=0.2,
    #                               min_lr=1e-6)

    # tuner.search(x_train, y_train, epochs=5, validation_data=(x_test, y_test))
    # best_model = tuner.get_best_models()[0]

    history = model.fit(
        x_train,
        y_train,
        batch_size=batch_size,
        epochs=nb_epoch,
        verbose=1,
        validation_data=(x_test, y_test),
        # callbacks=[reduce_lr],
    )
#%%


    # Serialize model
    model.save("my_keras_model.h5")

    # Evaluate model
    score = model.evaluate(x_test, y_test, verbose=0)
    print(score)
    print(f"Test accuarcy: {score[1] * 100:0.2f}%")
    model.metrics_names
    for key in history.history.keys():
        print(key)
    pdb.set_trace()

    # Plot model train accuracy and validation accuracy vs number of epochs
    # history = model.fit(train_x, train_y, validation_split=0.1, epochs=50, batch_size=4)
    plt.plot(history.history['accuracy'])
    plt.plot(history.history['val_accuracy'])
    # plt.plot(history.history['loss'])
    plt.title('model accuracy')
    plt.ylabel('accuracy')
    plt.xlabel('epoch')
    plt.legend(['train', 'val'], loc='upper left')
    plt.legend(['Keras tuner'], loc='upper right')
    plt.savefig(f'epoch={nb_epoch}-keras_tuner.png')
    plt.show()


    # Run the model on one example
    prediction = model.predict(x_test[0].reshape(-1, img_rows, img_cols, 1))
    # only show first 3 probabilities
    print(f"Prediction: {prediction[0][:3]}")