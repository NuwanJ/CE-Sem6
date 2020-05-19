import numpy as np 							#importing numpy module
import matplotlib.pyplot as plt 			#importing matplotlib modules to plot

x= np.array([1,2,3,4,5,6,7,8,9,10]) 		#array of independent variable values
y= np.array([2,5,7,8,9,11,14,15,17,19]) 	#array of dependent variable values
n= np.size(x) 								#get the number of observations

m_x=np.mean(x) 								#determining the mean values of variables
m_y=np.mean(y)

SS_xy = np.sum(y*x) - n*m_y*m_x 			#to find b_1 estimator value
SS_xx = np.sum(x*x) - n*m_x*m_x

b_1 = SS_xy / SS_xx 						#determining the parameter values
b_0 = m_y - b_1*m_x

plt.scatter(x, y,color = "b", marker = "*", s = 60) #plotting a scatter plot
plt.title('Simple Linear Regression') 		#adding a title to the graph
plt.xlabel('Independent Variable') 			#adding axis labels
plt.ylabel('Dependent Variable')

y_pred = b_0 + b_1*x 						#predicting response variable values

plt.plot(x, y_pred, color = "r") 			#plotting the predicted line
plt.show() 									#displaying the plotb