import pandas as pd 
import numpy as np

df = pd.read_csv('data.csv')
features=df.iloc[:,0:4]
target=df.iloc[:,4:5]
np.random.seed(1234)

X = features
y = target

column_names = features.columns.tolist()
feature = column_names

from sklearn import tree
decision_tree = tree.DecisionTreeClassifier(criterion='gini')
decision_tree.fit(X, y)


import serial
import time
arduino_port = "/dev/ttyACM0" 
baud = 9600 
ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)

command_dict = {"front":'f', "back":'b', "left":'l', "right":'r', "stop":'s'}
while True:
    getData = str(ser.readline())
    raw_data = getData[2:][:-5]
    data = [int(x) for x in raw_data.split(',') if x.strip().isdigit()]
    if len(data) == 4:    
        data = np.array(data)
        data = data.reshape(1,-1)
        command = decision_tree.predict(data)
        print("For ",data ," command is ", command)
        command_byte = command_dict[command[0]].encode('utf-8')
        ser.write(command_byte)
    else:
        print("Raw data received: ", raw_data)