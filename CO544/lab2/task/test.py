import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('lab02Exercise01.csv', names=['Chanel1','Chanel2','Chanel3','Chanel4','Chanel5'])
df=df.fillna(df.mean())
df["Class"] = ""

def f(x):
    if [((df.iloc[:,0][i]+df.iloc[:,4][i])/2) > ((df.iloc[:,1][i]+df.iloc[:,2][i]+df.iloc[:,3][i])/3) for i in range(0,df.shape[0])]:
        df["Class"] = 1
    else:
        df["Class"] = 0
        
df['class'] = df.apply(f, axis=1)
    
print(df)