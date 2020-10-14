# Separate Chaining Hash Table

### Separate chaining hash table data structure python module that is written originally in C and imported using Cython.

Create the python module from C scripts
```bash
$ python3 setup.py build_ext --inplace
```

Now run the **example.py** script to demonstrate the **HashTable** functionalities
```bash
$ python3 example.py

initialize an empty HashTable of size 10:

insert new values into the table

now the table is not empty and looks like:

index(0):
index(1):  91  11
index(2):  12  22
index(3):  13
index(4):  94
index(5):
index(6):
index(7):
index(8):
index(9):  19

size of the table is 10 while number of filled indices is 5


try now to search for and delete some values: (0 means False while 1 is True)
search for value 13 --> 1
search for value 11 --> 1
search by index 1 --> value 91 found
remove value 13 --> 1
search again for value 13 --> 0
try again to remove value 13 --> 0

size of the table is 10 while number of filled indices is 4


print the table after the deletion

index(0):
index(1):  91  11
index(2):  12  22
index(3):
index(4):  94
index(5):
index(6):
index(7):
index(8):
index(9):  19

insert value 4

index(0):
index(1):  91  11
index(2):  12  22
index(3):
index(4):  4  94
index(5):
index(6):
index(7):
index(8):
index(9):  19

size of the table is 10 while number of filled indices is 4


search by index 4 --> value 4 is found

remove value 91 --> 1

table is now looking like:

index(0):
index(1):  11
index(2):  12  22
index(3):
index(4):  4  94
index(5):
index(6):
index(7):
index(8):
index(9):  19

size of the table is 10 while number of filled indices is 4


################################## Comparing Normal Lists vs HashTable #############################################

constructing a list and a hash table of 5000000 length
and then try to search for value 4999998 linearly, using list comprehension
and using HashTable

time taken to fill the list is 0.544994

time taken to insert values into the HashTable is 0.590530

time to search linearly for value 4999998 in the list is 0.329196

time to search for value 4999998 in the list using list comprehension is 0.138425

value 4999998 --> 1

time to search for value 4999998 in the HashTable is 0.001664


size of the table is 5000000 while number of filled indices is 5000000
```
It is working fine!
