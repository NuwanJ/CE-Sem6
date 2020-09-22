# CO544 Lab 5
# E/15/140 Jaliyagoda A.J.N.M.


# 1.2 Importing Required modules.
import pandas as pd
import numpy as np

from mlxtend.frequent_patterns import apriori
from mlxtend.frequent_patterns import association_rules
from mlxtend.preprocessing import TransactionEncoder


# (a) Import the given dataset 'groceries.csv'
df = pd.read_csv('./grocc.csv', header=None)
#print(df)

# (b) Explore the dataset and create the frequent item dataset.
records = []
for i in range(0, len(df.index)):
    records.append([str(df.values[i,j]) for j in range(0, 31) if str(df.values[i,j]) != 'nan'])
#print(records)

te = TransactionEncoder()
te_ary = te.fit(records).transform(records)
df = pd.DataFrame(te_ary, columns=te.columns_)

# (c) Apply Apriori algorithm and identify the itemsets where the support is greater than 10%.

frequent_itemsets = apriori(df, min_support=0.1, use_colnames=True) 
print(frequent_itemsets)

'''
    support            itemsets
0  0.110524     (bottled water)
1  0.193493  (other vegetables)
2  0.183935        (rolls/buns)
3  0.108998   (root vegetables)
4  0.174377              (soda)
5  0.104931    (tropical fruit)
6  0.255516        (whole milk)
7  0.139502            (yogurt)
'''

# (d) Find the set of Association rules using the metric 'lift'

rules= association_rules(frequent_itemsets, metric="lift", min_threshold=2)
print(rules)


# (e) Select any Association rule from the set and describe the selected rule.

'''
antecedents 		{'tropical fruit'}
consequents 		{'bottled water'}
antecedent support: 0.105
consequent support 	0.110
support 			0.019
confidence 			0.176
lift 				1.596
leverage 			0.007
conviction 			1.080

This Association rule says buyers who buy 'Topical Fruit' also buy 'Bottled Water' in confidence of 0.176.
Supports for the antecedent and consequent are 0.105, 0.110
Support for the association rule is 0.019

'''

# (f) How many rules are there when the 'lift' is greater than 4 and the 'confidence' is greater than 0.8.

frequent_itemsets_2 = apriori(df, use_colnames=True, min_support=0.001)
rules= association_rules(frequent_itemsets_2, metric="lift", min_threshold=4)
result = rules[rules['confidence']>0.8]
print(result)

# Result: 142 rows (by assumming that min_support=0.001)



