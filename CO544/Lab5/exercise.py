
# 1.1 Importing required modules.
import numpy as np
from sklearn.cluster import KMeans
from sklearn.datasets.samples_generator import make_blobs

import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from matplotlib.lines import Line2D 

from sklearn import datasets
dataset = datasets.load_iris()

X = dataset['data']
#print(X)
'''
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
'''
# decided to use k=4

# Applying KMeans  algorithm with cluster size 4
kmeans = KMeans(n_clusters=4, random_state=0) #from Elbow method we identified n_clusters=4
closest_cluster_index = kmeans.fit_predict(X)
cluster_centers=kmeans.cluster_centers_

labels=np.unique(closest_cluster_index)
#print(labels)

# Plot first 3 variables in 3D space

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
scatterCenters = ax.scatter(cluster_centers[:,0], cluster_centers[:,1], cluster_centers[:,2], s=50,c='red',marker='o')
scatter = ax.scatter(X[:,0], X[:,1], X[:,2], label=labels, c=closest_cluster_index,  marker='x')

handles = [plt.Line2D([],[], marker="o", ls="", color=scatter.cmap(scatter.norm(yi))) for yi in labels]
ax.legend(handles, labels)
plt.title('Iris Dataset - Clustering with KMeans')
plt.legend(handles, labels)
plt.show()

