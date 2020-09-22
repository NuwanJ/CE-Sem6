# CO544 Lab 06 
# E/15/140 Jaliayagoda A.J.N.M. 


# (a) Importing required modules

import re 			#importing re module with regular expressions
import nltk 		#importing natural language toolkit module
from sklearn.datasets import load_files

from nltk.corpus import stopwords 			#importing collection of stop words in NLT (you can add related stop words to the problem in addition to these)
nltk.download('stopwords')

from nltk.stem import WordNetLemmatizer 	#for lemmatization
nltk.download('wordnet')

# (b) Loading data

#movie_data = load_files(r"txt_sentoken_test")
movie_data = load_files(r"txt_sentoken")
X, y = movie_data.data, movie_data.target

# (c) Data preprocessing

X=movie_data.data
print('There are {} data entries in the dataset'.format(len(X)))

docs = []
stemmer = WordNetLemmatizer()

for sen in range(0, len(X)):
    doc = re.sub(r'\W', ' ', str(X[sen]))			# Remove all the special characters
    doc = re.sub(r'\s+[a-zA-Z]\s+', ' ', doc)		# remove all single characters
    doc = re.sub(r'\^[a-zA-Z]\s+', ' ', doc) 		# Remove single characters from the start
    doc = re.sub(r'\s+', ' ', doc, flags=re.I)		# Substituting multiple spaces with single space

    # TODO 1: Find data preprocessing steps other than mentioned above.
    doc = re.sub(r'^b\s+', '', doc) 				# Removing prefixed 'b'
    doc = re.sub(r"\d+", "", doc)					# Remove numbers

    doc = doc.lower()								# Converting to lowercase
    doc = doc.split() 								# Lemmatization
    doc = [stemmer.lemmatize(word) for word in doc]
    doc = ' '.join(doc)
    docs.append(doc)
#print(docs)

# (d) Convert text into numbers.

from sklearn.feature_extraction.text import CountVectorizer

vectorizer = CountVectorizer(max_features=1500, min_df=7, max_df=0.8, stop_words=stopwords.words('english'))
X = vectorizer.fit_transform(docs).toarray() 
	# TODO 2: Discuss advantages and disadvantages of 'Bag of Words model'


#(e) Text Classification

from sklearn.model_selection import train_test_split 
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix,accuracy_score

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0) # Logistic regression model

# -------------------------------------------------------------------------------------

from sklearn.linear_model import LogisticRegression

log_reg = LogisticRegression()
log_reg.fit(X_train,y_train)
predictions_LR = log_reg.predict(X_test)

print('\n-- LogisticRegression -----------------------------------------------')
print('\nAccuracy:')
print(accuracy_score(y_test, predictions_LR))

print('\nConfusion Matrix:')
print(confusion_matrix(y_test, predictions_LR))

# TODO 3: Train a Random Forest model, a Support Vector Machine model and a Naive Byesian
# 		  classfier. Compare the accuracies of four models including the Logistic Regression model.
# 		  What is the best model? Justify your answer.

# -------------------------------------------------------------------------------------

from sklearn.ensemble import RandomForestClassifier

clf_RF = RandomForestClassifier(max_depth=2, random_state=0)
clf_RF.fit(X_train,y_train)
predictions_RF = clf_RF.predict(X_test)

print('\n-- Random Forest -----------------------------------------------')
print('\nAccuracy:')
print(accuracy_score(y_test, predictions_RF))

print('\nConfusion Matrix:')
print(confusion_matrix(y_test, predictions_RF))


# -------------------------------------------------------------------------------------

from sklearn import svm

clf_SVM = RandomForestClassifier(max_depth=2, random_state=0)
clf_SVM.fit(X_train,y_train)
predictions_SVM = clf_SVM.predict(X_test)

print('\n-- Support Vector Machine --------------------------------------')
print('\nAccuracy:')
print(accuracy_score(y_test, predictions_SVM))

print('\nConfusion Matrix:')
print(confusion_matrix(y_test, predictions_SVM))


# -------------------------------------------------------------------------------------

from sklearn.naive_bayes import GaussianNB

clf_NB = GaussianNB()
clf_NB.fit(X_train,y_train)
predictions_NB = clf_NB.predict(X_test)

print('\n-- Gaussian Naive Bayes --------------------------------------')
print('\nAccuracy:')
print(accuracy_score(y_test, predictions_NB))

print('\nConfusion Matrix:')
print(confusion_matrix(y_test, predictions_NB))


print('\n-- Summary ---------------------------------------------------')

from sklearn.metrics import classification_report

print('Logistic Regression')
print(classification_report(y_test,predictions_LR))

print('Random Forest')
print(classification_report(y_test,predictions_RF))

print('Support Vector Machine')
print(classification_report(y_test,predictions_SVM))

print('Gaussian Naive Bayes')
print(classification_report(y_test,predictions_NB))



'''

LogisticRegression is model with best accuracy


-- LogisticRegression -----------------------------------------------

Accuracy:
0.8275

Confusion Matrix:
	[[169  39]
	 [ 30 162]]

-- Random Forest -----------------------------------------------

Accuracy:
0.7925

Confusion Matrix:
	[[139  69]
	 [ 14 178]]

-- Support Vector Machine --------------------------------------

Accuracy:
0.7925

Confusion Matrix:
	[[139  69]
	 [ 14 178]]

-- Gaussian Naive Bayes --------------------------------------

Accuracy:
0.7525

Confusion Matrix:
	[[165  43]
	 [ 56 136]]

Logistic Regression
              precision    recall  f1-score   support

           0       0.85      0.81      0.83       208
           1       0.81      0.84      0.82       192

    accuracy                           0.83       400
   macro avg       0.83      0.83      0.83       400
weighted avg       0.83      0.83      0.83       400

Random Forest
              precision    recall  f1-score   support

           0       0.91      0.67      0.77       208
           1       0.72      0.93      0.81       192

    accuracy                           0.79       400
   macro avg       0.81      0.80      0.79       400
weighted avg       0.82      0.79      0.79       400

Support Vector Machine
              precision    recall  f1-score   support

           0       0.91      0.67      0.77       208
           1       0.72      0.93      0.81       192

    accuracy                           0.79       400
   macro avg       0.81      0.80      0.79       400
weighted avg       0.82      0.79      0.79       400

Gaussian Naive Bayes
              precision    recall  f1-score   support

           0       0.75      0.79      0.77       208
           1       0.76      0.71      0.73       192

    accuracy                           0.75       400
   macro avg       0.75      0.75      0.75       400
weighted avg       0.75      0.75      0.75       400

'''