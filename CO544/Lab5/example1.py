
# 1.1 Importing required modules.
from sklearn.cluster import KMeans
from sklearn.datasets.samples_generator import make_blobs
import matplotlib.pyplot as plt

# 1.2 creating a sample dataset with 4 clusters

X, y = make_blobs(n_samples=400, centers=4, cluster_std=0.90, random_state=1)
#print(X)
#print(y)


# 1.3 Determining the optimum value of k using Elbow method.

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


# 1.4 Applying K-Means algorithm.
kmeans = KMeans(n_clusters=4, random_state=0) #from Elbow method we identified n_clusters=4
closest_cluster_index = kmeans.fit_predict(X)
cluster_centers=kmeans.cluster_centers_

# 1.5 Visualizing
plt.scatter(X[:,0], X[:,1],c='green')
plt.scatter(kmeans.cluster_centers_[:,0],kmeans.cluster_centers_[:,1],s=200,c='black',marker='*')
plt.show()













