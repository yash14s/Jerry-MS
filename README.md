Paper: https://arxiv.org/abs/2111.12542 

Demo Videos: https://www.youtube.com/playlist?list=PLOb2NXVbCPbSkYf4oxKLrVQkXnnsJ8HQE  

arduino_control - Original code for arduino, raspi independent

create_csv.py - Python code to log ultrasonic values in data. csv file. Execute in a terminal after executing arduino_control.ino

sensor_readings - code for viewing ultrasonic sensor values on serial window.

ML - model.py contains ML model code for classification. data.csv is the dataset.
real_time_classification - implementation of model.py for classification generating commands.

test - contains latest code, under development

Usage:
1. Execute code.ino
2. Execute real_time_classification.py
