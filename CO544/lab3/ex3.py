import numpy as np 							#importing numpy module
import matplotlib.pyplot as plt 			#importing matplotlib modules to plot
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.utils import resample

# i. Import the Boston Housing.csv
df = pd.read_csv("Boston_Housing.csv").apply(pd.to_numeric)

dataX = np.array(df[df.columns[0:3]])
dataY = np.array(df[df.columns[3]])

X, x, Y, y = train_test_split(dataX, dataY, test_size=0.2, random_state=1)

a = np.linalg.inv(np.dot(X.transpose(),X))
b = np.dot(np.dot(a,X.transpose()),Y)
y_pred_0 = np.dot(x,b)						#predicting response variable values

y_pred = np.arange(len(x))

for i in range(50):
	bootsX, bootsY = resample(X,Y, replace=True, n_samples=100, random_state=1)
	#print(bootX, bootY)
	a = np.linalg.inv(np.dot(bootsX.transpose(),bootsX))
	b = np.dot(np.dot(a,bootsX.transpose()),bootsY)

	y_pred = y_pred + np.dot(x,b)						#predicting response variable values

y_pred = y_pred/50

print(y_pred)

plt.title('Simple Linear Regression')
plt.xlabel('Predicted Value')
plt.ylabel('Actual Value')

plt.scatter(y_pred_0, y, color = "b", marker = "*") 			#plotting the predicted line
plt.scatter(y_pred, y, color = "r", marker = "*") 			#plotting the predicted line
plt.show() 	

