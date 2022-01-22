# Recognition of Offline Handwritten Mathematical Expressions


'Recognition of Offline Handwritten Mathematical Expressions using embedded-AI Technology' is a master thesis project done by Rutwij Joshi at FH Aachen University. 


## Dataset

This project uses 'HASY' dataset created by Mr. Martin Thoma. For further information (or to download the dataset), please visit [HASY dataset](https://github.com/MartinThoma/HASY).
In addition to this, a support package is made available to handle the dataset, viz. [hasy_tools](https://github.com/MartinThoma/hasy_tools).


## Dataset Customization

The HASY dataset contains 369 symbols (label classes). For this project, only 85 symbols are used. These customizations are explained in the [HASY customization](https://github.com/Rutwij-Joshi/ROHME/blob/main/HASY%20Customization/hasy_customization.py).
Note that the code is cluttered and could be automated further.


## CNN - LeNet

For this project, LeNet-5 is used. The core structure of LeNet-5 is maintained, while some hyperparameter tuning is done to get an optimal testing accuracy.

[CNN](https://github.com/Rutwij-Joshi/ROHME/tree/main/CNN) folder contains different experimentations performed with the aforementioned CNN.

Please note that only specific versions of python packages are allowed to use in conjunction with Renesas's e-AI translator (or the TFLite converter libraries). 


## C codes - e2 studio (Project Structure Renesas)

This project structure folder was taken as-is from [simple application package](https://www.renesas.com/us/en/software-tool/rza2m-freertos-software-package) of Renesas. The image processing pieline is realised in the file 'rza2m_drp_dynamic_sample2_freertos_gcc/src/renesas/application/r_bcd_main.c'. Some functionalities/operations which were not used are commented out.

