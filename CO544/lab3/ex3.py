#----------------------------------------------------
# E/15/140	| CO544 | lab 3
#----------------------------------------------------

import numpy as np 
import matplotlib.pyplot as plt 
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.utils import resample

from sklearn.linear_model import LogisticRegression

df = pd.read_csv("Boston_Housing.csv").apply(pd.to_numeric)
df.insert(0, "index", np.ones(len(df)))

dataX = np.array(df[df.columns[0:4]])
dataY = np.array(df[df.columns[4]])

X, x, Y, y = train_test_split(dataX, dataY, test_size=0.2, random_state=1)

a = np.linalg.inv(np.dot(X.transpose(),X))
b = np.dot(np.dot(a,X.transpose()),Y)
y_pred_0 = np.dot(x,b)						#predicting response variable values

y_pred = np.arange(len(x))

sample_count = 50

for i in range(sample_count):
	
	bootsX, bootsY = resample(X,Y, replace=True, n_samples=100, random_state=5)
	
	a = np.linalg.inv(np.dot(bootsX.transpose(),bootsX))
	b = np.dot(np.dot(a,bootsX.transpose()),bootsY)
	predictions = np.dot(x,b)						#predicting response variable values

	'''
	log_reg = LogisticRegression() 				#creating an instance of the model
	log_reg.fit(bootsX, bootsY) 				#fitting the relationship between data
	predictions = log_reg.predict(x) 		#predict labels for test data
	'''
	y_pred = y_pred + predictions


y_pred = y_pred/(sample_count*1.0)
#print(y_pred)

plt.title('Linear Regression with Bootstrapping')
plt.xlabel('Predicted Value')
plt.ylabel('Actual Value')

plt.plot([0, 1000000], [0, 1000000], 'g')
plt.scatter(y_pred_0, y, color = "b", marker = ".") 			#plotting the predicted line
plt.scatter(y_pred, y, color = "r", marker = "*") 			#plotting the predicted line
plt.legend(['Residual Error= 0', 'Without Bootstrapping', 'With Bootstrapping'])
plt.show() 	

