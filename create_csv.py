import serial

arduino_port = "/dev/ttyACM0" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName="data.csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")

#display the data to the terminal


#add the data to the file
while True:
    getData=str(ser.readline())
    data=getData[0:][:-2]
    print(data)
    file = open(fileName, "a") #append the data to the file
    file.write(data + "\n") #write data with a newline


#close out the file
print("Data collection complete")
file.close()

