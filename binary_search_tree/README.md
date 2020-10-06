# Binary Search Tree

Create the python module from C scripts
```bash
python3 setup.py build_ext --inplace
```

In a python session, let's try the module
```python
import pandas as pd
data = pd.read_csv("example_data.csv", header = None)
data
#      0                    1     2
#0   130    Cristiano Ronaldo  0.76
#1   115         Lionel Messi  0.80
#2    71        Raul Gonzalez  0.50
#3    68   Robert Lewandowski  0.76
#4    65        Karim Benzema  0.54
#5    56  Ruud van Nistelrooy  0.77
#6    50        Thierry Henry  0.45
#7    49   Alfredo Di Stefano  0.84
#8    48    Andriy Shevchenko  0.48
#9    48   Zlatan Ibrahimovic  0.40
#10   46        Thomas Muller  0.40
from pybstree import *
bst = BSTree()
data.shape
# (11, 3)
data.shape[0]
# 11
for i in range(data.shape[0]):
    bst.insert(data.iloc[i, 0], data.iloc[i, 1].encode(), data.iloc[i, 2])

bst.node_count()
# 11
bst.inorder()
# 46 -> 48 -> 48 -> 49 -> 50 -> 56 -> 65 -> 68 -> 71 -> 115 -> 130 -> >>>
bst.search(40)
# "node doesn't exist"
bst.search(48)
# (48, b'Andriy Shevchenko', 0.48)
bst.search(46)
# (46, b'Thomas Muller', 0.4)
bst.search(49)
# (49, b'Alfredo Di Stefano', 0.84)
bst.remove(48)
bst.inorder()
# 46 -> 48 -> 49 -> 50 -> 56 -> 65 -> 68 -> 71 -> 115 -> 130 -> >>>
bst.node_count()
# 10
bst.remove(71)
bst.node_count()
# 9
bst.inorder()
# 46 -> 48 -> 49 -> 50 -> 56 -> 65 -> 68 -> 115 -> 130 -> >>>
bst.search(65)
# (65, b'Karim Benzema', 0.54)
```

It is working fine!
