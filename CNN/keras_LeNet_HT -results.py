# #!/usr/bin/env python
#
# """
# Trains a simple convnet on the HASY dataset.
# Gets to 77.77% test accuracy after 1 epoch.
# 790 seconds per epoch on a GeForce 940MX GPU.
# """
#
# # import tensorflow as tf
# # import numpy as np
# # from tensorflow import keras
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
# import pandas as pd
# from datetime import datetime
#
# np.random.seed(0)  # make sure results are reproducible
# tf.random.set_seed(0)  # make sure results are reproducible
#
# if __name__ == "__main__":
#     batch_size = 256
#     nb_epoch = 20
#
#     # input image dimensions
#     img_rows, img_cols = ht.img_rows, ht.img_cols
#     dataset_path = "C:/Users/rj7356s/PycharmProjects/HMSR1/HaSy"
#     # Load data
#     fold = 1
#     # hasy_data = ht.load_custom_data(main_dataset_path= main_dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")
#     hasy_data = ht.load_custom_data(main_dataset_path=dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")
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
#     labels_first_row = np.append(cm, labels_row, axis=1)
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
#     logdir = "results/logs3/scalars/" + datetime.now().strftime("%Y%m%d-%H%M%S")
#     tensorboard_callback = keras.callbacks.TensorBoard(log_dir=logdir)
#
#     # Define model
#     def build_model(hp):
#         model = Sequential()
#         model.add(Conv2D(filters=32, kernel_size=(5, 5), padding='same', activation='relu', input_shape=(32, 32, 1)))
#         model.add(MaxPool2D(strides=2))
#         model.add(Conv2D(filters=48, kernel_size=(5, 5), padding='valid', activation='relu'))
#         model.add(MaxPool2D(strides=2))
#         model.add(Flatten())
#         # model.add(Dense(256, activation='relu'))
#         model.add(Dense(
#             # hp.Choice('units', [128, 256, 512, 1024]),
#             hp.Choice('units', [128, 256]),
#             activation='relu'))
#         model.add(Dense(84, activation='relu'))
#         model.add(Dense(85, activation='softmax'))
#         # model.build()
#         # model.summary()
#         # adam1 = Adam(lr=5e-4)
#         # model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer=adam1)
#         model.compile(
#             optimizer= Adam(
#                 # hp.Choice("learning_rate", values=[1e-2, 1e-3, 1e-4])
#                 hp.Choice("learning_rate", values=[1e-2, 1e-3])
#             ),
#             loss="categorical_crossentropy",
#             metrics=["accuracy"],
#         )
#         return model
#
#
#     tuner = kt.RandomSearch(
#         build_model,
#         objective='val_accuracy',
#         overwrite=True,
#         max_trials=12)
#
#     tuner.search_space_summary()
#
#
#     # reduce_lr = ReduceLROnPlateau(monitor='val_accuracy',
#     #                               patience=3,
#     #                               verbose=1,
#     #                               factor=0.2,
#     #                               min_lr=1e-6)
#
#     tuner.search(x_train, y_train, epochs=10, validation_data=(x_test, y_test))
#     # best_model = tuner.get_best_models()[0]
#     tuner.results_summary()
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
#     # model.save("my_keras_model.h5")
#
#     # Evaluate model
#     # score = model.evaluate(x_test, y_test, verbose=0)
#     # print(score)
#     # print(f"Test accuarcy: {score[1] * 100:0.2f}%")
#     # model.metrics_names
#     # for key in history.history.keys():
#     #     print(key)
#     # pdb.set_trace()
#
#     # Plot model train accuracy and validation accuracy vs number of epochs
#     # history = model.fit(train_x, train_y, validation_split=0.1, epochs=50, batch_size=4)
#     # plt.plot(history.history['accuracy'])
#     # plt.plot(history.history['val_accuracy'])
#     # # plt.plot(history.history['loss'])
#     # plt.title('model accuracy')
#     # plt.ylabel('accuracy')
#     # plt.xlabel('epoch')
#     # plt.legend(['train', 'val'], loc='upper left')
#     # plt.legend(['Keras tuner'], loc='upper right')
#     # plt.savefig(f'/results/epoch={nb_epoch}-keras_tuner.png')
#     # plt.show()
#
#
#     # Run the model on one example
#     # prediction = model.predict(x_test[0].reshape(-1, img_rows, img_cols, 1))
#     # # only show first 3 probabilities
#     # print(f"Prediction: {prediction[0][:3]}")


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
import kerastuner as kt
from datetime import datetime
from packaging import version
import pandas as pd

# import pdb
# # import keras_tuner as kt
# import kerastuner as kt
# import pandas as pd
# from datetime import datetime

np.random.seed(0)  # make sure results are reproducible
tf.random.set_seed(0)  # make sure results are reproducible


if __name__ == "__main__":
    batch_size = 256
    nb_epoch = 5

    # input image dimensions
    img_rows, img_cols = ht.img_rows, ht.img_cols
    dataset_path = "C:/Users/rj7356s/PycharmProjects/HMSR1/HaSy"
    # Load data
    fold = 1
    # hasy_data = ht.load_custom_data(main_dataset_path= main_dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")
    hasy_data = ht.load_custom_data(main_dataset_path=dataset_path, mode=f"fold-{fold}", image_dim_ordering="tf")

    data_latex = pd.read_csv("HaSy\symbols.csv")

    labels = data_latex['latex'].values
    labels_first_column = labels.reshape((85, 1))
    labels_row = labels_first_column.T

    cm = np.array(['CM'])
    cm = cm.reshape((1, 1))
    print("size cm", cm.shape)

    labels_first_row = np.append(cm, labels_row, axis=1)

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

    logdir = "results\\logs3\\scalars\\" + datetime.now().strftime("%Y%m%d-%H%M%S")
    tensorboard_callback = keras.callbacks.TensorBoard(log_dir=logdir)
    # tensorboard_callback = keras.callbacks.TensorBoard(
    #     log_dir='logdir', histogram_freq=0, write_graph=True,
    #     write_images=False, update_freq='epoch',
    #     profile_batch=0, embeddings_freq=0, embeddings_metadata=None
    # )

    # Define model
    def build_model(hp):
        model = Sequential()
        model.add(Conv2D(filters=32, kernel_size=(5, 5), padding='same', activation='relu', input_shape=(32, 32, 1)))
        model.add(MaxPool2D(strides=2))
        model.add(Conv2D(filters=48, kernel_size=(5, 5), padding='valid', activation='relu'))
        model.add(MaxPool2D(strides=2))
        model.add(Flatten())
        # model.add(Dense(256, activation='relu'))
        model.add(Dense(
            # hp.Choice('units', [128, 256, 512, 1024]),
            hp.Choice('units', [256, 512, 1024]),
            activation='relu'))
        model.add(Dense(84, activation='relu'))
        model.add(Dense(85, activation='softmax'))
        # model.build()
        # model.summary()
        # adam1 = Adam(lr=5e-4)
        # model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer=adam1)
        model.compile(
            optimizer=Adam(
                hp.Choice("learning_rate", values=[1e-2, 1e-3, 1e-4])
                # hp.Choice("learning_rate", values=[1e-2])
            ),
            loss="categorical_crossentropy",
            metrics=["accuracy"],
        )
        return model


    tuner = kt.RandomSearch(
        build_model,
        objective='val_accuracy',
        overwrite=True,
        max_trials=48)

    tuner.search_space_summary()


    # reduce_lr = ReduceLROnPlateau(monitor='val_accuracy',
    #                               patience=3,
    #                               verbose=1,
    #                               factor=0.2,
    #                               min_lr=1e-6)

    tuner.search(x_train, y_train, epochs=nb_epoch, validation_data=(x_test, y_test),
                 callbacks=[tensorboard_callback])
    # best_model = tuner.get_best_models()[0]
    tuner.results_summary()

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
    # model.save("my_keras_model.h5")

    # Evaluate model
    # score = model.evaluate(x_test, y_test, verbose=0)
    # print(score)
    # print(f"Test accuarcy: {score[1] * 100:0.2f}%")
    # model.metrics_names
    # for key in history.history.keys():
    #     print(key)
    # pdb.set_trace()

    # Plot model train accuracy and validation accuracy vs number of epochs
    # history = model.fit(train_x, train_y, validation_split=0.1, epochs=50, batch_size=4)
    # plt.plot(history.history['accuracy'])
    # plt.plot(history.history['val_accuracy'])
    # # plt.plot(history.history['loss'])
    # plt.title('model accuracy')
    # plt.ylabel('accuracy')
    # plt.xlabel('epoch')
    # plt.legend(['train', 'val'], loc='upper left')
    # plt.legend(['Keras tuner'], loc='upper right')
    # plt.savefig(f'epoch={nb_epoch}-keras_tuner.png')
    # plt.show()


    # Run the model on one example
    # prediction = model.predict(x_test[0].reshape(-1, img_rows, img_cols, 1))
    # # only show first 3 probabilities
    # print(f"Prediction: {prediction[0][:3]}")