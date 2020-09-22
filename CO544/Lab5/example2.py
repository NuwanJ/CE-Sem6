

# 1.2 Importing Required modules.

from mlxtend.frequent_patterns import apriori
from mlxtend.frequent_patterns import association_rules
from mlxtend.preprocessing import TransactionEncoder

import pandas as pd
import numpy as np

# 1.3 Input data

dataset = [['Milk', 'Onion', 'Nutmeg', 'Kidney Beans', 'Eggs', 'Yogurt'],
	['Dill', 'Onion', 'Nutmeg', 'Kidney Beans', 'Eggs', 'Yogurt'],
	['Milk', 'Apple', 'Kidney Beans', 'Eggs'],
	['Milk', 'Unicorn', 'Corn', 'Kidney Beans', 'Yogurt'],
	['Corn', 'Onion', 'Onion', 'Kidney Beans', 'Ice cream', 'Eggs']]



# 1.4 Creating the dataframe of frequent itemsets.

te = TransactionEncoder()
te_ary = te.fit(dataset).transform(dataset)
df = pd.DataFrame(te_ary, columns=te.columns_)

# 1.5 Applying Apriori algorithm and finding Association rules.

sup = apriori(df, min_support=0.002, use_colnames=True) 
rules= association_rules(sup, metric="support", min_threshold=0.5)
print(rules)












