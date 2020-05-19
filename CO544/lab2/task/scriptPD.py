import numpy as np
import pandas as pd
from pandas.plotting import scatter_matrix
import matplotlib.pyplot as plt

# function to assign values for 'class' in df
def f(x):
    return 1 if((x['Chanel1'] + x['Chanel5'])/2 < ((x['Chanel2'] + x['Chanel3'] + x['Chanel4'])/3)) else 0

# 1. Read CSV
df = pd.read_csv('lab02Exercise01.csv', names=['Chanel1', 'Chanel2', 'Chanel3', 'Chanel4', 'Chanel5'])

# 2. Fill missing values with column average
df = df.fillna(df.mean())

# 3. Show in scatter plot
scatter_matrix(df , alpha =0.2 , figsize =(6, 6),diagonal='kde')

# 4. Add a new class to df
df['class']  = df.apply(f, axis=1)
print(df)

# Plot the chart
plt.show()
