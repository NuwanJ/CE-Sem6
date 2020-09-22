
# CO544 - Lab 4 
# E/15/140 Jaliyagoda A.J.N.M.

from sklearn.decomposition import PCA
from sklearn import preprocessing
from sklearn import datasets

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from matplotlib.lines import Line2D 

dataset = datasets.load_wine()

df = pd.DataFrame(data= np.c_[dataset['data'], dataset['target']],columns=dataset['feature_names'] + ['target'])

X = dataset['data'] # df.columns != 'target'
y = dataset['target'].astype(int)

#print(X)
#print(y)
#print(X.columns)
#print(y.columns)

# Standardize the dataset before PCA
#scaler = preprocessing.StandardScaler().fit(X)
#X = scaler.transform(X)
#print(X)

pca = PCA(n_components = 3)
result = pca.fit(X)

result=pd.DataFrame(result.transform(X), columns=['pca%i' % i for i in range(3)])
#print(result)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
labels = np.unique(y)

scatter = ax.scatter(result['pca0'], result['pca1'], result['pca2'], c=y, label=labels, marker='o')
handles = [plt.Line2D([],[],marker="o", ls="", color=scatter.cmap(scatter.norm(yi))) for yi in labels]
ax.legend(handles, labels)

plt.title('Principle Component Analysis')
plt.legend(handles, labels)
ax.set_xlabel('Principal Component 0')
ax.set_ylabel('Principal Component 1')
ax.set_zlabel('Principal Component 2')

plt.show()
