# Struct Pie
A set of python modules for data structures. All data structures are written in **C** and imported into python using **cython**. No python code involved to make the data structure pretty fast.

The idea is to extend python data structures to add more flexibility and to include more data structures that can help in different situations.

## Quick Start
To install the library
```bash
pip install structpie
```

Testing the different data structures from within python

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

#### Hash Table
**Separate Chaining** hash map that enables fast lookup and search. 
It facilitates searching by "value" **O(1)**, in contrary to python dictionary which enables O(1) search when key is known.

For full comparison between list, dict and HashTable, try to run the **example.py** script in */hash_table/* folder.

To initiate a hash table, size and type should be specified. It supports 'int', 'float' and 'str'
```python
size = 10
type = "str"
ht = HashTable(size, type)
arr = ["Hello", "Salam", "Hola", "Ola", "Ciao", "Konnichiwa", "Merhaba", "privetstviye"]
```

If the table is of "str" type, input string should be converted into **bytes** for Cython to be able to convert it into **C char***. 
```python
# insert data into the table
for i in arr:
    ht.insert_val(i.encode())

# print the table
ht.display()
# index(0):
# index(1):  Salam
# index(2):
# index(3):  Ciao  Hello
# index(4):
# index(5):
# index(6):
# index(7):
# index(8):
# index(9):  Merhaba  Ola  Hola
```
Check the size of the table and how many indices are occupied.
```python
print("size of the table is %d while number of filled indices is %d" %
    (ht.length(), ht.occupied()))
# size of the table is 10 while number of filled indices is 3
```
Search for a value in the table, remove and search by index:
```python
print("try now to search for and delete some values: (0 means False while 1 is True)")
# try now to search for and delete some values: (0 means False while 1 is True)
print("search for value Merhaba --> %d" % ht.search_value("Merhaba".encode()))
# search for value Merhaba --> 1
print("search for value Namaste --> %d" % ht.search_value("Namaste".encode()))
# search for value Namaste --> 0
print("search by index 1 --> value %s found" % ht.search_by_index(1))
# search by index 1 --> value Salam found
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
# index(0):
# index(1):  Salam
# index(2):
# index(3):  Ciao  Hello
# index(4):
# index(5):
# index(6):
# index(7):
# index(8):
# index(9):  Merhaba  Hola
```
#### The library also supports Binary Search Tree and Priority Queues. 

More data structures will be supported soon.
