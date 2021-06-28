import pandas as pd 
import numpy as np
from sklearn.metrics import mean_squared_error

df1 = pd.read_csv('data.csv')
features=df1.iloc[:,0:4]
target=df1.iloc[:,4:5]

from sklearn.model_selection import train_test_split
np.random.seed(1234)
(X_train, X_test, Y_train, Y_test) = train_test_split(features, target, train_size=0.7, random_state=1)

column_names = features.columns.tolist()
feature = column_names

from sklearn import tree
decision_tree = tree.DecisionTreeClassifier(criterion='gini')
decision_tree.fit(X_train, Y_train)
predictions_decision_tree=decision_tree.predict(X_test)
print('The accuracy of the Decision Tree classifier on training data is {:.2f}'.format(decision_tree.score(X_train, Y_train)))
print('The accuracy of the Decision Tree classifier on test data is {:.2f}'.format(decision_tree.score(X_test, Y_test)))

pred=pd.DataFrame(predictions_decision_tree)
temp=Y_test
temp=temp.reset_index(drop=True)
print(pred,temp)