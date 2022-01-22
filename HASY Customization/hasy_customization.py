import csv
import fileinput
import sys

# Get the path of current working directory
# path = os.getcwd()
# path = path + '\HaSy'
# Get the list of all files and directories
# in current working directory

# print("Files and directories in '", path, "' :")
# dir_list = os.listdir(path)
# # print the list
# print(dir_list)
# pdb.set_trace()
#
# def get_num_lines(file_name):
#     """ Counts the number of lines in the file. """
#     f = open(file_name, 'r')
#     counter = 0;
#     for i in f:
#         counter += 1
#     return counter

accepted_symbols = ['\\ast', '\\div', '\\infty', '\\pm', '\\propto', '\\sqrt{}', '\\times', '\\{',
                    '\\}', '\\%', '+', '-', '/', '0', '1', '2',
                    '3', '4', '5', '6', '7', '8', '9', '<',
                    '>', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                    'Y', 'Z', '[', ']', 'a', 'b', 'c', 'd',
                    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 'u',
                    'v', 'w', 'x', 'y', 'z', '\\equiv', '\\geq', '\\leq',
                    '\\leqslant', '\\geqslant', '\\neq', '\\sim']



# reader = csv.reader(open("HaSy/symbols.csv", "r"), delimiter=',')
#
# total_symbols = []
# for row in reader:
#     print(row[1])
#     total_symbols.append(row[1])
#
# total_symbols.pop(0)
# print(total_symbols)


# myfilepath = "HaSy/symbols.csv"
# with open(myfilepath, 'r') as f:
#     mycsv = csv.reader(f)
#     mycsv = list(mycsv)
#     for i in range(1, 370):
#         text = mycsv[i][1]
#         print(text)

# counter = 0
# myfilepath = "HaSy/symbols.csv"
# with open(myfilepath, 'r') as f:
#     mycsv = csv.reader(f)
#     mycsv = list(mycsv)
#     for i in range(1, 370):
#         for j in range (85):
#             if accepted_symbols[j] == mycsv[i][1]:
#                 counter += 1
#                 print("mycsv = ", mycsv[i][1])
#                 print("i", i)



# counter = 0
# myfilepath = "HaSy/symbols.csv"
# with open(myfilepath, 'r') as f:
#     mycsv = csv.reader(f)
#     mycsv1 = list(mycsv)
#     seen = {(row[0], row[2]) for row in mycsv}
#     print("seen", seen)
#     # print("mycsv1", mycsv1[1])
#     f1 = fileinput.input('myfilepath', inplace=True)
#     w = csv.writer(sys.stdout)
#     for row in csv.reader(f1):
#         for j in range (85):
#             if accepted_symbols[j] == mycsv1[i][1]:
#                 counter += 1
#                 print("mycsv1 = ", mycsv1[i][1])
#                 print("i", i)
#                 w.writerow(row)

############################symbols#####################################
myfilepath = "HaSy/hasyv2/symbols.csv"
with open(myfilepath, 'r') as file_b:
    r = csv.reader(file_b)
    # next(r)
    seen = accepted_symbols
    print("accept", accepted_symbols)
    print("seen", seen)
    print("len", len(seen))

f = fileinput.input(myfilepath, inplace=True)       # sys.stdout is redirected to the file
print(next(f), end='')                                      # write header as first line
w = csv.writer(sys.stdout, lineterminator='\n')
for row in csv.reader(f):
   if (row[1]) in seen:                             # write it if it's accepted
       w.writerow(row)
#########################################################################


#############################data-labels#################################
myfilepath1 = "HaSy/hasyv2/hasy-data-labels.csv"
with open(myfilepath1, 'r') as file_b1:
    r1 = csv.reader(file_b1)
    # next(r)
    seen1 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen", seen1)
    print("len", len(seen1))

f1 = fileinput.input(myfilepath1, inplace=True)       # sys.stdout is redirected to the file
print(next(f1), end='')                                      # write header as first line
w1 = csv.writer(sys.stdout, lineterminator='\n')
for row1 in csv.reader(f1):
   if (row1[2]) in seen1:                             # write it if it's accepted
       w1.writerow(row1)
#############################################################################



####################################fold-1###################################
myfilepath11 = "HaSy/hasyv2/classification-task/fold-1/test.csv"
with open(myfilepath11, 'r') as file_b11:
    r11 = csv.reader(file_b11)
    # next(r)
    seen11 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen11", seen11)
    print("len11", len(seen11))

f11 = fileinput.input(myfilepath11, inplace=True)       # sys.stdout is redirected to the file
print(next(f11), end='')                                      # write header as first line
w11 = csv.writer(sys.stdout, lineterminator='\n')
for row11 in csv.reader(f11):
   if (row11[2]) in seen11:                             # write it if it's accepted
       w11.writerow(row11)



myfilepath12 = "HaSy/hasyv2/classification-task/fold-1/train.csv"
with open(myfilepath12, 'r') as file_b12:
    r12 = csv.reader(file_b12)
    # next(r)
    seen12 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen12", seen12)
    print("len12", len(seen12))

f12 = fileinput.input(myfilepath12, inplace=True)       # sys.stdout is redirected to the file
print(next(f12), end='')                                      # write header as first line
w12 = csv.writer(sys.stdout, lineterminator='\n')
for row12 in csv.reader(f12):
   if (row12[2]) in seen12:                             # write it if it's accepted
       w12.writerow(row12)
################################################################################



###################################fold-2########################################
myfilepath21 = "HaSy/hasyv2/classification-task/fold-2/test.csv"
with open(myfilepath21, 'r') as file_b21:
    r21 = csv.reader(file_b21)
    # next(r)
    seen21 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen21", seen21)
    print("len21", len(seen21))

f21 = fileinput.input(myfilepath21, inplace=True)       # sys.stdout is redirected to the file
print(next(f21), end='')                                      # write header as first line
w21 = csv.writer(sys.stdout, lineterminator='\n')
for row21 in csv.reader(f21):
   if (row21[2]) in seen21:                             # write it if it's accepted
       w21.writerow(row21)



myfilepath22 = "HaSy/hasyv2/classification-task/fold-2/train.csv"
with open(myfilepath22, 'r') as file_b22:
    r22 = csv.reader(file_b22)
    # next(r)
    seen22 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen22", seen22)
    print("len22", len(seen22))

f22 = fileinput.input(myfilepath22, inplace=True)       # sys.stdout is redirected to the file
print(next(f22), end='')                                      # write header as first line
w22 = csv.writer(sys.stdout, lineterminator='\n')
for row22 in csv.reader(f22):
   if (row22[2]) in seen22:                             # write it if it's accepted
       w22.writerow(row22)
#################################################################################



###################################fold-3########################################
myfilepath31 = "HaSy/hasyv2/classification-task/fold-3/test.csv"
with open(myfilepath31, 'r') as file_b31:
    r31 = csv.reader(file_b31)
    # next(r)
    seen31 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen31", seen31)
    print("len31", len(seen31))

f31 = fileinput.input(myfilepath31, inplace=True)       # sys.stdout is redirected to the file
print(next(f31), end='')                                      # write header as first line
w31 = csv.writer(sys.stdout, lineterminator='\n')
for row31 in csv.reader(f31):
   if (row31[2]) in seen31:                             # write it if it's accepted
       w31.writerow(row31)



myfilepath32 = "HaSy/hasyv2/classification-task/fold-3/train.csv"
with open(myfilepath32, 'r') as file_b32:
    r32 = csv.reader(file_b32)
    # next(r)
    seen32 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen32", seen32)
    print("len32", len(seen32))

f32 = fileinput.input(myfilepath32, inplace=True)       # sys.stdout is redirected to the file
print(next(f32), end='')                                      # write header as first line
w32 = csv.writer(sys.stdout, lineterminator='\n')
for row32 in csv.reader(f32):
   if (row32[2]) in seen32:                             # write it if it's accepted
       w32.writerow(row32)
#################################################################################



###################################fold-4########################################
myfilepath41 = "HaSy/hasyv2/classification-task/fold-4/test.csv"
with open(myfilepath41, 'r') as file_b41:
    r41 = csv.reader(file_b41)
    # next(r)
    seen41 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen41", seen41)
    print("len41", len(seen41))

f41 = fileinput.input(myfilepath41, inplace=True)       # sys.stdout is redirected to the file
print(next(f41), end='')                                      # write header as first line
w41 = csv.writer(sys.stdout, lineterminator='\n')
for row41 in csv.reader(f41):
   if (row41[2]) in seen41:                             # write it if it's accepted
       w41.writerow(row41)



myfilepath42 = "HaSy/hasyv2/classification-task/fold-4/train.csv"
with open(myfilepath42, 'r') as file_b42:
    r42 = csv.reader(file_b42)
    # next(r)
    seen42 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen42", seen42)
    print("len42", len(seen42))

f42 = fileinput.input(myfilepath42, inplace=True)       # sys.stdout is redirected to the file
print(next(f42), end='')                                      # write header as first line
w42 = csv.writer(sys.stdout, lineterminator='\n')
for row42 in csv.reader(f42):
   if (row42[2]) in seen42:                             # write it if it's accepted
       w42.writerow(row42)
#################################################################################



###################################fold-5########################################
myfilepath51 = "HaSy/hasyv2/classification-task/fold-5/test.csv"
with open(myfilepath51, 'r') as file_b51:
    r51 = csv.reader(file_b51)
    # next(r)
    seen51 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen51", seen51)
    print("len51", len(seen51))

f51 = fileinput.input(myfilepath51, inplace=True)       # sys.stdout is redirected to the file
print(next(f51), end='')                                      # write header as first line
w51 = csv.writer(sys.stdout, lineterminator='\n')
for row51 in csv.reader(f51):
   if (row51[2]) in seen51:                             # write it if it's accepted
       w51.writerow(row51)



myfilepath52 = "HaSy/hasyv2/classification-task/fold-5/train.csv"
with open(myfilepath52, 'r') as file_b52:
    r52 = csv.reader(file_b52)
    # next(r)
    seen52 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen52", seen52)
    print("len52", len(seen52))

f52 = fileinput.input(myfilepath52, inplace=True)       # sys.stdout is redirected to the file
print(next(f52), end='')                                      # write header as first line
w52 = csv.writer(sys.stdout, lineterminator='\n')
for row52 in csv.reader(f52):
   if (row52[2]) in seen52:                             # write it if it's accepted
       w52.writerow(row52)
#################################################################################



###################################fold-6########################################
myfilepath61 = "HaSy/hasyv2/classification-task/fold-6/test.csv"
with open(myfilepath61, 'r') as file_b61:
    r61 = csv.reader(file_b61)
    # next(r)
    seen61 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen61", seen61)
    print("len61", len(seen61))

f61 = fileinput.input(myfilepath61, inplace=True)       # sys.stdout is redirected to the file
print(next(f61), end='')                                      # write header as first line
w61 = csv.writer(sys.stdout, lineterminator='\n')
for row61 in csv.reader(f61):
   if (row61[2]) in seen61:                             # write it if it's accepted
       w61.writerow(row61)



myfilepath62 = "HaSy/hasyv2/classification-task/fold-6/train.csv"
with open(myfilepath62, 'r') as file_b62:
    r62 = csv.reader(file_b62)
    # next(r)
    seen62 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen62", seen62)
    print("len62", len(seen62))

f62 = fileinput.input(myfilepath62, inplace=True)       # sys.stdout is redirected to the file
print(next(f62), end='')                                      # write header as first line
w62 = csv.writer(sys.stdout, lineterminator='\n')
for row62 in csv.reader(f62):
   if (row62[2]) in seen62:                             # write it if it's accepted
       w62.writerow(row62)
#################################################################################



###################################fold-7########################################
myfilepath71 = "HaSy/hasyv2/classification-task/fold-7/test.csv"
with open(myfilepath71, 'r') as file_b71:
    r71 = csv.reader(file_b71)
    # next(r)
    seen71 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen71", seen71)
    print("len71", len(seen71))

f71 = fileinput.input(myfilepath71, inplace=True)       # sys.stdout is redirected to the file
print(next(f71), end='')                                      # write header as first line
w71 = csv.writer(sys.stdout, lineterminator='\n')
for row71 in csv.reader(f71):
   if (row71[2]) in seen71:                             # write it if it's accepted
       w71.writerow(row71)



myfilepath72 = "HaSy/hasyv2/classification-task/fold-7/train.csv"
with open(myfilepath72, 'r') as file_b72:
    r72 = csv.reader(file_b72)
    # next(r)
    seen72 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen72", seen72)
    print("len72", len(seen72))

f72 = fileinput.input(myfilepath72, inplace=True)       # sys.stdout is redirected to the file
print(next(f72), end='')                                      # write header as first line
w72 = csv.writer(sys.stdout, lineterminator='\n')
for row72 in csv.reader(f72):
   if (row72[2]) in seen72:                             # write it if it's accepted
       w72.writerow(row72)
#################################################################################



###################################fold-8########################################
myfilepath81 = "HaSy/hasyv2/classification-task/fold-8/test.csv"
with open(myfilepath81, 'r') as file_b81:
    r81 = csv.reader(file_b81)
    # next(r)
    seen81 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen81", seen81)
    print("len81", len(seen81))

f81 = fileinput.input(myfilepath81, inplace=True)       # sys.stdout is redirected to the file
print(next(f81), end='')                                      # write header as first line
w81 = csv.writer(sys.stdout, lineterminator='\n')
for row81 in csv.reader(f81):
   if (row81[2]) in seen81:                             # write it if it's accepted
       w81.writerow(row81)



myfilepath82 = "HaSy/hasyv2/classification-task/fold-8/train.csv"
with open(myfilepath82, 'r') as file_b82:
    r82 = csv.reader(file_b82)
    # next(r)
    seen82 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen82", seen82)
    print("len82", len(seen82))

f82 = fileinput.input(myfilepath82, inplace=True)       # sys.stdout is redirected to the file
print(next(f82), end='')                                      # write header as first line
w82 = csv.writer(sys.stdout, lineterminator='\n')
for row82 in csv.reader(f82):
   if (row82[2]) in seen82:                             # write it if it's accepted
       w82.writerow(row82)
#################################################################################



###################################fold-9########################################
myfilepath91 = "HaSy/hasyv2/classification-task/fold-9/test.csv"
with open(myfilepath91, 'r') as file_b91:
    r91 = csv.reader(file_b91)
    # next(r)
    seen91 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen91", seen91)
    print("len91", len(seen91))

f91 = fileinput.input(myfilepath91, inplace=True)       # sys.stdout is redirected to the file
print(next(f91), end='')                                      # write header as first line
w91 = csv.writer(sys.stdout, lineterminator='\n')
for row91 in csv.reader(f91):
   if (row91[2]) in seen91:                             # write it if it's accepted
       w91.writerow(row91)



myfilepath92 = "HaSy/hasyv2/classification-task/fold-9/train.csv"
with open(myfilepath92, 'r') as file_b92:
    r92 = csv.reader(file_b92)
    # next(r)
    seen92 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen92", seen92)
    print("len92", len(seen92))

f92 = fileinput.input(myfilepath92, inplace=True)       # sys.stdout is redirected to the file
print(next(f92), end='')                                      # write header as first line
w92 = csv.writer(sys.stdout, lineterminator='\n')
for row92 in csv.reader(f92):
   if (row92[2]) in seen92:                             # write it if it's accepted
       w92.writerow(row92)
#################################################################################



###################################fold-10########################################
myfilepath101 = "HaSy/hasyv2/classification-task/fold-10/test.csv"
with open(myfilepath101, 'r') as file_b101:
    r101 = csv.reader(file_b101)
    # next(r)
    seen101 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen101", seen101)
    print("len101", len(seen101))

f101 = fileinput.input(myfilepath101, inplace=True)       # sys.stdout is redirected to the file
print(next(f101), end='')                                      # write header as first line
w101 = csv.writer(sys.stdout, lineterminator='\n')
for row101 in csv.reader(f101):
   if (row101[2]) in seen101:                             # write it if it's accepted
       w101.writerow(row101)



myfilepath102 = "HaSy/hasyv2/classification-task/fold-10/train.csv"
with open(myfilepath102, 'r') as file_b102:
    r102 = csv.reader(file_b102)
    # next(r)
    seen102 = accepted_symbols
    # print("accept", accepted_symbols)
    print("seen102", seen102)
    print("len102", len(seen102))

f102 = fileinput.input(myfilepath102, inplace=True)       # sys.stdout is redirected to the file
print(next(f102), end='')                                      # write header as first line
w102 = csv.writer(sys.stdout, lineterminator='\n')
for row102 in csv.reader(f102):
   if (row102[2]) in seen102:                             # write it if it's accepted
       w102.writerow(row102)
#################################################################################




####################################################################
# inputfile = csv.reader(open('HaSy/symbols.csv','r'))
# # inputfile = list(inputfile)
#
#
# # row_count = sum(1 for row in inputfile)
# # row_count -= 1
# # # row_count = row_count - 1
# # print(row_count)
#
# # addition = 0
# total_symbols = []
# for row in inputfile:
#     # print(row[1])
#     total_symbols.append(row[1])
#
# total_symbols.pop(0)
# print("total symbols",total_symbols)
# print("accepted symbols",accepted_symbols)
#
# length_accepted_symbols = len(accepted_symbols)
# print(length_accepted_symbols)
#
# length_all_symbols = len(total_symbols)
# print(length_all_symbols)
#
#
# for i in range(length_all_symbols)
#     for j in range(length_accepted_symbols)
####################################################################


# for row in inputfile:
#     for column in inputfile:
#         print(row,column)

# for column in inputfile:
#     print(column)

# for row in inputfile:
#     # print(', '.join(row))
#     print(row[1])

# print("+++++++++++++++")
# print(row[1])

# for i in range(length_symbols):
#     print("accepted symbols[i]", accepted_symbols[i])
#     for row in inputfile:
#         print("row:", row)
#         for j in range(369):
#             print("row[2][j]", row[2][j])
#             # if row[j] == accepted_symbols[i]:
#             addition += 1
#             print("sum", addition)



