
from sklearn import datasets
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix,accuracy_score


#dataset =datasets.load_wine() 			#load 'wine' data set from standard data sets
dataset = datasets.load_digits() 

x=dataset["data"] 						#defining features values
y =dataset["target"] 					#defining target variable values

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.20, random_state=1)


log_reg = LogisticRegression() 				#creating an instance of the model
log_reg.fit(x_train,y_train) 				#fitting the relationship between data
predictions = log_reg.predict(x_test) 		#predict labels for test data

#print(classification_report(y_test, predictions))

print('Accuracy:')
print(accuracy_score(y_test, predictions))

print('Confusion Matrix:')
print(confusion_matrix(y_test, predictions))