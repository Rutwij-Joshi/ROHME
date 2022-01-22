#!/usr/bin/env python

"""
Trains a simple convnet on the HASY dataset.
Gets to 77.77% test accuracy after 1 epoch.
790 seconds per epoch on a GeForce 940MX GPU.

log : choices for the first dense layer (relu - relu - softmax - cat. crossentropy) 5 epochs
log1 : choices for the second dense layer (relu - relu - softmax - cat. crossentropy) 5 epochs
log2 : changed the activation function(relu/softmax --> sigmoid)
        and loss(categorical_crossentropy --> binary_crossentropy) 5 epochs
log3 : choices for the first dense layer
        choices for the second dense layer
        (relu - relu - softmax - cat. crossentropy) 20 epochs
"""

# import tensorflow as tf
# import numpy as np
# from tensorflow import kerasm
# from keras.models import Sequential
# from keras.layers import Conv2D, Dense, MaxPool2D, Dropout, Flatten
# from keras import callbacks
# from keras.preprocessing.image import ImageDataGenerator
# from keras.models import Sequential
# from keras.optimizers import Adam
# from keras.callbacks import ReduceLROnPlateau
# import matplotlib.pyplot as plt
# import seaborn as sns
# import hasy.hasy_tools as ht
# import pdb
# import keras_tuner as kt
import json

import tensorflow as tf
import numpy as np
from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, Dense, MaxPool2D, Dropout, Flatten
from tensorflow.keras import callbacks
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import ReduceLROnPlateau
import matplotlib.pyplot as plt
import seaborn as sns
import hasy.hasy_tools as ht
import pdb
# import keras_tuner as kt
import kerastuner as kt
from datetime import datetime
from packaging import version
from sklearn.metrics import confusion_matrix
import pandas as pd
import seaborn as sn


np.random.seed(0)  # make sure results are reproducible
tf.random.set_seed(0)  # make sure results are reproducible

if __name__ == "__main__":
    batch_size = 128
    nb_epoch = 10

    # input image dimensions
    img_rows, img_cols = ht.img_rows, ht.img_cols
    dataset_path = "C:/Users/rj7356s/PycharmProjects/HMSR1/HaSy"
    # Load data
    fold = 1
    # hasy_data = ht.load_custom_data(main_dataset_path= main_dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")
    hasy_data = ht.load_custom_data(main_dataset_path= dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")

    data_latex = pd.read_csv("HaSy\symbols.csv")

    labels = data_latex['latex'].values
    labels_first_column = labels.reshape((85, 1))
    labels_row = labels_first_column.T

    cm = np.array(['CM'])
    cm = cm.reshape((1, 1))
    print("size cm", cm.shape)

    labels_first_row = np.append(cm, labels_row, axis= 1)

    print("size column", labels_first_column.shape)
    print("size row", labels_first_row.shape)

    print(labels_first_column)
    print(labels_first_row)

    x_train = hasy_data["x_train"]
    y_train = hasy_data["y_train"]
    x_test = hasy_data["x_test"]
    y_test = hasy_data["y_test"]
    print("x train shape", x_train.shape)

    x_train_non_OHE = x_train
    y_train_non_OHE = y_train
    x_test_non_OHE = x_test
    y_test_non_OHE = y_test

    # One-Hot encoding
    y_train = np.eye(ht.n_classes)[y_train.squeeze()]
    y_test = np.eye(ht.n_classes)[y_test.squeeze()]

    # Preprocessing
    x_train = ht.preprocess(x_train)
    x_test = ht.preprocess(x_test)

    # symbol_id2index, label_list = ht.generate_index('HaSy/hasyv2/classification-task/fold-1/train.csv')
    #
    # print("labels",label_list)
    # print("id2index",symbol_id2index)

    # pdb.set_trace()

    # logdir = "logs3/scalars/" + datetime.now().strftime("%Y%m%d-%H%M%S")
    # tensorboard_callback = keras.callbacks.TensorBoard(log_dir=logdir)
    units1 = 1024       #256
    dense1 = [256, 512, 1024]
    lr = [1e-2, 1e-3, 1e-4]

    for i in range(3):
        for j in range(3):
            # Define model
            print("dense1 = ", dense1[i])
            print("lr = ", lr[j])
            model = Sequential()
            model.add(
                Conv2D(filters=32, kernel_size=(5, 5), padding='same', activation='relu', input_shape=(32, 32, 1)))
            model.add(MaxPool2D(strides=2))
            model.add(Conv2D(filters=48, kernel_size=(5, 5), padding='valid', activation='relu'))
            model.add(MaxPool2D(strides=2))
            model.add(Flatten())
            # model.add(Dense(units1, activation='relu'))
            model.add(Dense(dense1[i], activation='relu'))
            model.add(Dense(84, activation='relu'))
            model.add(Dense(85, activation='softmax'))
            model.build()
            model.summary()
            # adam1 = Adam(lr=0.001)  # 5e-4
            adam1 = Adam(lr[j])  # 5e-4
            model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer=adam1)

            # reduce_lr = ReduceLROnPlateau(monitor='val_accuracy',
            #                               patience=3,
            #                               verbose=1,
            #                               factor=0.2,
            #                               min_lr=1e-6)

            history = model.fit(
                x_train,
                y_train,
                batch_size=batch_size,
                epochs=nb_epoch,
                verbose=1,
                validation_data=(x_test, y_test),
                # callbacks=[reduce_lr],
            )

            # Serialize model
            model.save("my_keras_model_cm1.h5")

            # Evaluate model
            score = model.evaluate(x_test, y_test, verbose=0)
            print("score = ", score)
            print(f"Test accuarcy: {score[1] * 100:0.2f}%")
            model.metrics_names
            for key in history.history.keys():
                print(key)
            # pdb.set_trace()

            # Print confusion matrix
            test_predictions = model.predict(x_test_non_OHE)

            # print("x-test non ohe", x_test_non_OHE)
            # print("Test predictions:", test_predictions)
            arg_max = np.argmax(test_predictions, axis=1)
            # print("np-argmax:", arg_max)
            # print("y_test_non_OHE:", y_test_non_OHE)
            confusion_raw = confusion_matrix(y_test_non_OHE, np.argmax(test_predictions, axis=1))
            # print("confusion_raw: ", confusion_raw)
            confusion = np.append(labels_first_column, confusion_raw, axis=1)
            confusion = np.append(labels_first_row, confusion, axis=0)
            # print(confusion)
            # np.savetxt('confusion.csv', confusion, fmt="%d", delimiter=",")
            np.savetxt('confusion_labeled_1.csv', confusion, fmt="%s", delimiter=",")

            confusion_raw_list = confusion_raw.tolist()
            cm_json = json.dumps(confusion_raw_list)
            jsonFile = open("cm.json", "w")
            jsonFile.write(cm_json)
            jsonFile.close()

            # df_cm = pd.DataFrame(confusion_raw, index=[i for i in range(1,86)],
            #                      columns=[i for i in range(1,86)])
            # plt.figure(figsize=(10, 7))
            # sn.heatmap(df_cm, annot=True, cmap="OrRd")

            # cm_df = pd.DataFrame(data = confusion_raw, index = None, columns = None)
            # results = [{'confusionmatrix': cm_df}]
            # cm = pd.Series(results).to_json(orient = 'records')
            # print("cm = ", cm)
            # jsonFile = open("cm.json", "w")
            # jsonFile.write(cm)
            # jsonFile.close()

            # ht._analyze_cm("cm.json", total_symbols= 369)

            # Plot model train accuracy and validation accuracy vs number of epochs
            plt.plot(history.history['accuracy'])
            plt.plot(history.history['val_accuracy'])
            # plt.plot(history.history['loss'])
            plt.title('model accuracy')
            plt.ylabel('accuracy')
            plt.xlabel('epoch')
            plt.xlim([0, 10])
            plt.ylim([0, 1])
            # plt.legend(['train', 'val'], loc='upper left')
            plt.legend(['train', 'val'], loc='upper right')
            plt.text(6.5, 0.13, f"learning rate={lr[j]}")
            plt.text(6.5, 0.07, f"units={dense1[i]}")
            # plt.legend(['Keras tuner'], loc='upper right')
            plt.savefig(f'lr={lr[j]}_units={dense1[i]}-results.png')
            plt.show()

            print("***********************************************************************")





    # # Define model
    # model = Sequential()
    # model.add(Conv2D(filters=32, kernel_size=(5, 5), padding='same', activation='relu', input_shape=(32, 32, 1)))
    # model.add(MaxPool2D(strides=2))
    # model.add(Conv2D(filters=48, kernel_size=(5, 5), padding='valid', activation='relu'))
    # model.add(MaxPool2D(strides=2))
    # model.add(Flatten())
    # model.add(Dense(units1, activation='relu'))
    # model.add(Dense(84, activation='relu'))
    # model.add(Dense(85, activation='softmax'))
    # model.build()
    # model.summary()
    # adam1 = Adam(lr=0.001)      #5e-4
    # model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer=adam1)
    #
    #
    # # reduce_lr = ReduceLROnPlateau(monitor='val_accuracy',
    # #                               patience=3,
    # #                               verbose=1,
    # #                               factor=0.2,
    # #                               min_lr=1e-6)
    #
    # history = model.fit(
    #     x_train,
    #     y_train,
    #     batch_size=batch_size,
    #     epochs=nb_epoch,
    #     verbose=1,
    #     validation_data=(x_test, y_test),
    #     # callbacks=[reduce_lr],
    # )
    #
    # # Serialize model
    # model.save("my_keras_model_cm1.h5")
    #
    # # Evaluate model
    # score = model.evaluate(x_test, y_test, verbose=0)
    # print("score = ",score)
    # print(f"Test accuarcy: {score[1] * 100:0.2f}%")
    # model.metrics_names
    # for key in history.history.keys():
    #     print(key)
    # # pdb.set_trace()
    #
    # # Print confusion matrix
    # test_predictions = model.predict(x_test_non_OHE)
    #
    # # print("x-test non ohe", x_test_non_OHE)
    # print("Test predictions:", test_predictions)
    # arg_max = np.argmax(test_predictions, axis=1)
    # print("np-argmax:", arg_max)
    # print("y_test_non_OHE:", y_test_non_OHE)
    # confusion_raw = confusion_matrix(y_test_non_OHE, np.argmax(test_predictions, axis=1))
    # print("confusion_raw: ", confusion_raw)
    # confusion = np.append(labels_first_column, confusion_raw, axis= 1)
    # confusion = np.append(labels_first_row, confusion, axis= 0)
    # print(confusion)
    # # np.savetxt('confusion.csv', confusion, fmt="%d", delimiter=",")
    # np.savetxt('confusion_labeled_1.csv', confusion, fmt="%s", delimiter=",")
    #
    # confusion_raw_list = confusion_raw.tolist()
    # cm_json = json.dumps(confusion_raw_list)
    # jsonFile = open("cm.json", "w")
    # jsonFile.write(cm_json)
    # jsonFile.close()
    #
    # # df_cm = pd.DataFrame(confusion_raw, index=[i for i in range(1,86)],
    # #                      columns=[i for i in range(1,86)])
    # # plt.figure(figsize=(10, 7))
    # # sn.heatmap(df_cm, annot=True, cmap="OrRd")
    #
    #
    # # cm_df = pd.DataFrame(data = confusion_raw, index = None, columns = None)
    # # results = [{'confusionmatrix': cm_df}]
    # # cm = pd.Series(results).to_json(orient = 'records')
    # # print("cm = ", cm)
    # # jsonFile = open("cm.json", "w")
    # # jsonFile.write(cm)
    # # jsonFile.close()
    #
    # # ht._analyze_cm("cm.json", total_symbols= 369)
    #
    # # Plot model train accuracy and validation accuracy vs number of epochs
    # plt.plot(history.history['accuracy'])
    # plt.plot(history.history['val_accuracy'])
    # # plt.plot(history.history['loss'])
    # plt.title('model accuracy')
    # plt.ylabel('accuracy')
    # plt.xlabel('epoch')
    # # plt.legend(['train', 'val'], loc='upper left')
    # plt.legend(['train', 'val'], loc='upper right')
    # # plt.legend(['Keras tuner'], loc='upper right')
    # plt.savefig(f'lr={lr(j)}_units={dense1(i)}-results.png')
    # plt.show()


    # Run the model on one example
    # prediction = model.predict(x_test[0].reshape(-1, img_rows, img_cols, 1))
    # # only show first 3 probabilities
    # print(f"Prediction: {prediction[0][:3]}")



# #!/usr/bin/env python
#
# """
# Trains a simple convnet on the HASY dataset.
# Gets to 77.77% test accuracy after 1 epoch.
# 790 seconds per epoch on a GeForce 940MX GPU.
#
# log : choices for the first dense layer (relu - relu - softmax - cat. crossentropy) 5 epochs
# log1 : choices for the second dense layer (relu - relu - softmax - cat. crossentropy) 5 epochs
# log2 : changed the activation function(relu/softmax --> sigmoid)
#         and loss(categorical_crossentropy --> binary_crossentropy) 5 epochs
# log3 : choices for the first dense layer
#         choices for the second dense layer
#         (relu - relu - softmax - cat. crossentropy) 20 epochs
# """
#
# # import tensorflow as tf
# # import numpy as np
# # from tensorflow import kerasm
# # from keras.models import Sequential
# # from keras.layers import Conv2D, Dense, MaxPool2D, Dropout, Flatten
# # from keras import callbacks
# # from keras.preprocessing.image import ImageDataGenerator
# # from keras.models import Sequential
# # from keras.optimizers import Adam
# # from keras.callbacks import ReduceLROnPlateau
# # import matplotlib.pyplot as plt
# # import seaborn as sns
# # import hasy.hasy_tools as ht
# # import pdb
# # import keras_tuner as kt
# import json
#
# import tensorflow as tf
# import numpy as np
# from tensorflow import keras
# from tensorflow.keras.models import Sequential
# from tensorflow.keras.layers import Conv2D, Dense, MaxPool2D, Dropout, Flatten
# from tensorflow.keras import callbacks
# from tensorflow.keras.preprocessing.image import ImageDataGenerator
# from tensorflow.keras.models import Sequential
# from tensorflow.keras.optimizers import Adam
# from tensorflow.keras.callbacks import ReduceLROnPlateau
# import matplotlib.pyplot as plt
# import seaborn as sns
# import hasy.hasy_tools as ht
# import pdb
# # import keras_tuner as kt
# import kerastuner as kt
# from datetime import datetime
# from packaging import version
# from sklearn.metrics import confusion_matrix
# import pandas as pd
#
#
# np.random.seed(0)  # make sure results are reproducible
# tf.random.set_seed(0)  # make sure results are reproducible
#
# if __name__ == "__main__":
#     batch_size = 128
#     nb_epoch = 10
#
#     # input image dimensions
#     img_rows, img_cols = ht.img_rows, ht.img_cols
#     dataset_path = "C:/Users/rj7356s/PycharmProjects/HMSR1/HaSy"
#     # Load data
#     fold = 1
#     # hasy_data = ht.load_custom_data(main_dataset_path= main_dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")
#     hasy_data = ht.load_custom_data(main_dataset_path= dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")
#
#     data_latex = pd.read_csv("HaSy\symbols.csv")
#
#     labels = data_latex['latex'].values
#     labels_first_column = labels.reshape((85, 1))
#     labels_row = labels_first_column.T
#
#     cm = np.array(['CM'])
#     cm = cm.reshape((1, 1))
#     print("size cm", cm.shape)
#
#     labels_first_row = np.append(cm, labels_row, axis= 1)
#
#     print("size column", labels_first_column.shape)
#     print("size row", labels_first_row.shape)
#
#     print(labels_first_column)
#     print(labels_first_row)
#
#     x_train = hasy_data["x_train"]
#     y_train = hasy_data["y_train"]
#     x_test = hasy_data["x_test"]
#     y_test = hasy_data["y_test"]
#     print("x train shape", x_train.shape)
#
#     x_train_non_OHE = x_train
#     y_train_non_OHE = y_train
#     x_test_non_OHE = x_test
#     y_test_non_OHE = y_test
#
#     # One-Hot encoding
#     y_train = np.eye(ht.n_classes)[y_train.squeeze()]
#     y_test = np.eye(ht.n_classes)[y_test.squeeze()]
#
#     # Preprocessing
#     x_train = ht.preprocess(x_train)
#     x_test = ht.preprocess(x_test)
#
#     # symbol_id2index, label_list = ht.generate_index('HaSy/hasyv2/classification-task/fold-1/train.csv')
#     #
#     # print("labels",label_list)
#     # print("id2index",symbol_id2index)
#
#     # pdb.set_trace()
#
#     # logdir = "logs3/scalars/" + datetime.now().strftime("%Y%m%d-%H%M%S")
#     # tensorboard_callback = keras.callbacks.TensorBoard(log_dir=logdir)
#     units1 = 1024       #256
#     # Define model
#     model = Sequential()
#     model.add(Conv2D(filters=32, kernel_size=(5, 5), padding='same', activation='relu', input_shape=(32, 32, 1)))
#     model.add(MaxPool2D(strides=2))
#     model.add(Conv2D(filters=48, kernel_size=(5, 5), padding='valid', activation='relu'))
#     model.add(MaxPool2D(strides=2))
#     model.add(Flatten())
#     model.add(Dense(units1, activation='relu'))
#     model.add(Dense(84, activation='relu'))
#     model.add(Dense(85, activation='softmax'))
#     model.build()
#     model.summary()
#     adam1 = Adam(lr=0.001)      #5e-4
#     model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer=adam1)
#
#
#     # reduce_lr = ReduceLROnPlateau(monitor='val_accuracy',
#     #                               patience=3,
#     #                               verbose=1,
#     #                               factor=0.2,
#     #                               min_lr=1e-6)
#
#     history = model.fit(
#         x_train,
#         y_train,
#         batch_size=batch_size,
#         epochs=nb_epoch,
#         verbose=1,
#         validation_data=(x_test, y_test),
#         # callbacks=[reduce_lr],
#     )
#
#     # Serialize model
#     model.save("my_keras_model_cm1.h5")
#
#     # Evaluate model
#     score = model.evaluate(x_test, y_test, verbose=0)
#     print("score = ",score)
#     print(f"Test accuarcy: {score[1] * 100:0.2f}%")
#     model.metrics_names
#     for key in history.history.keys():
#         print(key)
#     # pdb.set_trace()
#
#     # Print confusion matrix
#     test_predictions = model.predict(x_test_non_OHE)
#
#     # print("x-test non ohe", x_test_non_OHE)
#     print("Test predictions:", test_predictions)
#     arg_max = np.argmax(test_predictions, axis=1)
#     print("np-argmax:", arg_max)
#     print("y_test_non_OHE:", y_test_non_OHE)
#     confusion_raw = confusion_matrix(y_test_non_OHE, np.argmax(test_predictions, axis=1))
#     print("confusion_raw: ", confusion_raw)
#     confusion = np.append(labels_first_column, confusion_raw, axis= 1)
#     confusion = np.append(labels_first_row, confusion, axis= 0)
#     print(confusion)
#     # np.savetxt('confusion.csv', confusion, fmt="%d", delimiter=",")
#     np.savetxt('confusion_labeled_1.csv', confusion, fmt="%s", delimiter=",")
#
#     confusion_raw_list = confusion_raw.tolist()
#     cm_json = json.dumps(confusion_raw_list)
#     jsonFile = open("cm.json", "w")
#     jsonFile.write(cm_json)
#     jsonFile.close()
#
#
#     # cm_df = pd.DataFrame(data = confusion_raw, index = None, columns = None)
#     # results = [{'confusionmatrix': cm_df}]
#     # cm = pd.Series(results).to_json(orient = 'records')
#     # print("cm = ", cm)
#     # jsonFile = open("cm.json", "w")
#     # jsonFile.write(cm)
#     # jsonFile.close()
#
#     # ht._analyze_cm("cm.json", total_symbols= 369)
#
#     # Plot model train accuracy and validation accuracy vs number of epochs
#     plt.plot(history.history['accuracy'])
#     plt.plot(history.history['val_accuracy'])
#     # plt.plot(history.history['loss'])
#     plt.title('model accuracy')
#     plt.ylabel('accuracy')
#     plt.xlabel('epoch')
#     plt.legend(['train', 'val'], loc='upper left')
#     plt.legend(['Keras tuner'], loc='upper right')
#     plt.savefig(f'lr=0.0001_units=1024-keras_tuner-cm.png')
#     plt.show()
#
#
#     # Run the model on one example
#     # prediction = model.predict(x_test[0].reshape(-1, img_rows, img_cols, 1))
#     # # only show first 3 probabilities
#     # print(f"Prediction: {prediction[0][:3]}")