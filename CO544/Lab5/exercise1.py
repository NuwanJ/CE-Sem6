# CO544 Lab 5
# E/15/140 Jaliyagoda A.J.N.M.


# 1.1 Importing required modules.
import numpy as np
import matplotlib.pyplot as plt

from sklearn import datasets
from sklearn.cluster import KMeans
from sklearn.datasets.samples_generator import make_blobs

from mpl_toolkits import mplot3d
from matplotlib.lines import Line2D 

# (a) Import 'iris' dataset from the standard Scikit-learn datasets. The dataset is intended to use for classification. Make the dataset into an unlabeled dataset by removing the class attribute.

dataset = datasets.load_iris()
X = dataset['data']
#print(X)


# (b) Use Elbow method to identify the best k which minimizes the Within-Cluster-Sum-of-Squared(inertia).
wcss = []
for i in range(1, 11):
	kmeans = KMeans(n_clusters=i, init='k-means++', max_iter=300, n_init=10, random_state=0)
	kmeans.fit(X)
	wcss.append(kmeans.inertia_)

plt.plot(range(1, 11), wcss)
plt.title('Elbow Method')
plt.xlabel('Number of clusters')
plt.ylabel('WCSS')
plt.show()

# decided to use k=4

# (c) Fit the k-Means algorithm with the k value identied from part(b).

kmeans = KMeans(n_clusters=4, random_state=0) #from Elbow method we identified n_clusters=4
closest_cluster_index = kmeans.fit_predict(X)
cluster_centers=kmeans.cluster_centers_

labels=np.unique(closest_cluster_index)
#print(labels)


# (d) Explain the results of following code snippet.
#		kmeans.cluster_centers_
#	  ;where kmeans is the KMeans object

'''
'kmeans.cluster_centers_' returns a list of identified cluster centers as N dimensional vectors, 
where the N is the column count of the input dataset 'X'

'''

# (e) Visualize the data points and cluster centers in a 3D plot where first three variables of the dataset are the axes.

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
scatterCenters = ax.scatter(cluster_centers[:,0], cluster_centers[:,1], cluster_centers[:,2], s=50,c='red',marker='o')
scatter = ax.scatter(X[:,0], X[:,1], X[:,2], label=labels, c=closest_cluster_index,  marker='x')

handles = [plt.Line2D([],[], marker="o", ls="", color=scatter.cmap(scatter.norm(yi))) for yi in labels]
ax.legend(handles, labels)
plt.title('Iris Dataset - Clustering with KMeans')
plt.legend(handles, labels)
plt.show()

