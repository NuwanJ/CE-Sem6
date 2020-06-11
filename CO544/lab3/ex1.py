#----------------------------------------------------
# E/15/140	| CO544 | lab 3
#----------------------------------------------------

import numpy as np 							#importing numpy module
import matplotlib.pyplot as plt 			#importing matplotlib modules to plot
import pandas as pd
from sklearn.model_selection import train_test_split

df = pd.read_csv("Boston_Housing.csv").apply(pd.to_numeric)
df.insert(0, "index", np.ones(len(df)))

dataX = np.array( df[df.columns[0:4]])
dataY = np.array(df[df.columns[4]])

print(dataX)
#print(dataY)

X, x, Y, y = train_test_split(dataX, dataY, test_size=0.2, random_state=1)

a = np.linalg.inv(np.dot(X.transpose(),X))
b = np.dot(np.dot(a,X.transpose()),Y)

Y_pred = np.dot(X,b)						#predicting response variable values
y_pred = np.dot(x,b)						#predicting response variable values

plt.title('Simple Linear Regression')
plt.xlabel('Predicted Value')
plt.ylabel('Actual Value')
plt.plot([0, 1000000], [0, 1000000], 'g')

plt.scatter(Y_pred, Y,  color = "r", marker = "*") 			#plotting the predicted line
plt.scatter(y_pred, y, color = "b", marker = "*") 			#plotting the predicted line
plt.legend(['Residual Error= 0','Train Data', 'Test Data'])
plt.show() 	

