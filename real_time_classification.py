import pandas as pd 
import numpy as np

print("LOADING DATASET")
df = pd.read_csv('data_test.csv')
features=df.iloc[:,0:4]
target=df.iloc[:,4:5]
np.random.seed(1234)

X = features
y = target

column_names = features.columns.tolist()
feature = column_names

from sklearn import tree
decision_tree = tree.DecisionTreeClassifier(criterion='gini')
print("APPLYING ML")
decision_tree.fit(X, y)

import serial
import time
import threading
arduino_port = "/dev/ttyACM0" 
baud = 115200 
ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
print("READY")

command_dict = {"front":'f', "back":'b', "left":'l', "right":'r', "stop":'s'}
while True:
    getData = str(ser.readline())
    raw_data = getData[2:][:-5]
    data = [int(x) for x in raw_data.split(',') if x.strip().isdigit()]
    if len(data) == 4:    
        data = (np.array(data)).reshape(1,-1)
        #print("For ",data ," command is ", command)
        command = decision_tree.predict(data)
        command_byte = command_dict[command[0]].encode('utf-8')
        ser.write(command_byte)



