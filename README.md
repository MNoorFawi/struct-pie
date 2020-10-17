# Struct Pie
A set of python modules for data structures. All data structures are written in **C** and imported into python using **cython**. No python code involved to make the data structure pretty fast.

The idea is to extend python data structures to add more flexibility and to include more data structures that can help in different situations.

## Quick Start
To install the library
```bash
pip install structpie
```

Testing the different data structures from within python

#### Hash Table
**Separate Chaining** hash map that enables fast lookup and search. 
It facilitates searching by "value" **O(1)**, in contrary to python dictionary which enables O(1) search when key is known.

For full comparison between list, dict and HashTable, try to run the **example.py** script in */hash_table/* folder.

To initiate a hash table, size and type should be specified. It supports 'int', 'float' and 'str'
```python
size = 10
type = "str"
ht = HashTable(size, type)
arr = ["Hello", "Salam", "Hola", "Ola", "Ciao", "Konnichiwa", "Merhaba", "Privetstviye"]
```

If the table is of "str" type, input string should be converted into **bytes** for Cython to be able to convert it into **C char***. 
```python
# insert data into the table
for i in arr:
    ht.insert_val(i.encode())

# print the table
ht.display()
# index(0):  Hello
# index(1):
# index(2):
# index(3):  Konnichiwa
# index(4):  Ola
# index(5):  Ciao
# index(6):
# index(7):  Hola
# index(8):  Merhaba  Salam
# index(9):  Privetstviye
```
Check the size of the table and how many indices are occupied.
```python
print("size of the table is %d while number of filled indices is %d" %
    (ht.length(), ht.occupied()))
# size of the table is 10 while number of filled indices is 7
```
Search for a value in the table, remove and search by index:
```python
print("try now to search for and delete some values: (0 means False while 1 is True)")
# try now to search for and delete some values: (0 means False while 1 is True)
print("search for value Merhaba --> %d" % ht.search_value("Merhaba".encode()))
# search for value Merhaba --> 1
print("search for value Namaste --> %d" % ht.search_value("Namaste".encode()))
# search for value Namaste --> 0
print("search by index 3 --> value %s found" % ht.search_by_index(3))
# search by index 3 --> value Konnichiwa found
print("remove value Ola --> %d" % ht.val_del("Ola".encode()))
# remove value Ola --> 1
print("search again for value Ola --> %d" % ht.search_value("Ola".encode()))
# search again for value Ola --> 0
print("try again to remove value Ola --> %d" % ht.val_del("Ola".encode()))
# try again to remove value Ola --> 0
```
Print again
```python
ht.display()
# index(0):  Hello
# index(1):
# index(2):
# index(3):  Konnichiwa
# index(4):
# index(5):  Ciao
# index(6):
# index(7):  Hola
# index(8):  Merhaba  Salam
# index(9):  Privetstviye
```

#### LIFO & FIFO Stack
```python
from structpie import *

# initiate a stack of type "int"
st = Stack("int")

# push values into the stack
st.push(13)
st.push(11)
st.push(19)
st.push(91)

# print the stack
st.display()
# [13 11 19 91 ]

# pop from right (LIFO)
st.pop()
# 91

# pop from left (FIFO)
st.popleft()
# 13

# check length
st.length()
# 2 

# print again
st.display()
# [11 19 ]
```
**The stack can also contain data of type 'float' and 'str'**

#### Binary Search Tree
Binary search tree is a great data structure for quick searching and dynamic sorting while inserting new data. It is widely used in so many applications like indexing in databases for fast lookup.

Struct Pie provides a C-written binary search tree for usage in python.

Insertion is a little bit slower than appending to a python list, but searching is so much faster.

Struct Pie BST nodes can hold 3 data pieces; (int index, char* info1, float info2). This will be extended soon to hold more data.

Let's try the binary search tree on some sample data about Uefa Champions League all-time goalscorers. Each row represents (number of goals, name, goal/game ratio).
```python
# initiate bstree
bst = BSTree()

import pandas as pd
data = pd.read_csv("./binary_search_tree/example_data.csv", header = None)
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
```
Let's insert the data into the tree
```python
for i in range(data.shape[0]):
    bst.insert(data.iloc[i, 0], data.iloc[i, 1].encode(), data.iloc[i, 2])

# check that all data was inserted
data.shape[0] == bst.node_count()
# True
```
Some operations on the tree; **(inorder) printing, searching and deleting**
```python
# print inorder 
bst.inorder()
# 46 -> 48 -> 48 -> 49 -> 50 -> 56 -> 65 -> 68 -> 71 -> 115 -> 130 ->

# search for an index
bst.search(40)
# "node doesn't exist"

bst.search(48)
# (48, b'Andriy Shevchenko', 0.48)

bst.search(46)
# (46, b'Thomas Muller', 0.4)

bst.search(49)
# (49, b'Alfredo Di Stefano', 0.84)

# delete a node
bst.remove(48)

# new order after deletion
bst.inorder()
# 46 -> 48 -> 49 -> 50 -> 56 -> 65 -> 68 -> 71 -> 115 -> 130 ->

bst.node_count()
# 10

bst.remove(71)
bst.node_count()
# 9
bst.inorder()
# 46 -> 48 -> 49 -> 50 -> 56 -> 65 -> 68 -> 115 -> 130 ->

bst.search(65)
# (65, b'Karim Benzema', 0.54)
```

#### Priority Queue
Priority queue is a very good data structure for inserting new values and ordering the queue according to certain priority so that when poping the more important ones get popped first even if they were inserted later.

```python
pq = PQ()
pq.display()
# The queue is Empty
```
PQ takes two inputs, for now, (char * name, int priority). This will definitely be expanded soon.
###### C char* is represented in python as bytes by cython. So while inserting strings, they should be encoded into bytes first.

Let's insert some tasks and priorities:
```python
pq.push(b"exercise", 3)
pq.push(b"sleep", 2)
pq.push(b"repeat", 1)
pq.push(b"code", 5)
pq.display()
# (
#  {code, 5}
#  {exercise, 3}
#  {sleep, 2}
#  {repeat, 1}
# )
``` 
Queue was dynamically ordered according to priorities.

Now let's pop:
```python
pq.pop()
# (code) with priority (5) has been removed
# 'code'
```
Note that pop method prints a confirmation message and returns the task name as a string
```python
some = pq.pop()
# (exercise) with priority (3) has been removed
print(some)
# exercise

pq.display()
# (
#  {sleep, 2}
#  {repeat, 1}
# )

pq.pop()
# (sleep) with priority (2) has been removed
# 'sleep'
pq.pop()
# (repeat) with priority (1) has been removed
# 'repeat'

## when trying to pop from an empty queue, an empty string '' is returned.
pq.pop()
# The queue is empty
# ''
pq.display()
# The queue is Empty
```

**More data structures will be supported soon.**
