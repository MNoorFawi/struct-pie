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
index(1):  91.00  11.00
index(2):  12.00  22.00
index(3):  13.00
index(4):  94.00
index(5):
index(6):
index(7):
index(8):
index(9):  19.00  19.00

size of the table is 10 while number of filled indices is 5


try now to search for and delete some values: (0 means False while 1 is True)
search for value 13 --> 1
search for value 11 --> 1
search by index 1 --> value 91.000000 found
remove value 13 --> 1
search again for value 13 --> 0
try again to remove value 13 --> 0

size of the table is 10 while number of filled indices is 4


print the table after the deletion

index(0):
index(1):  91.00  11.00
index(2):  12.00  22.00
index(3):
index(4):  94.00
index(5):
index(6):
index(7):
index(8):
index(9):  19.00  19.00

insert value 4

index(0):
index(1):  91.00  11.00
index(2):  12.00  22.00
index(3):
index(4):  4.00  94.00
index(5):
index(6):
index(7):
index(8):
index(9):  19.00  19.00

size of the table is 10 while number of filled indices is 4


search by index 4 --> value 4.000000 is found

remove value 91 --> 1

table is now looking like:

index(0):
index(1):  11.00
index(2):  12.00  22.00
index(3):
index(4):  4.00  94.00
index(5):
index(6):
index(7):
index(8):
index(9):  19.00  19.00

size of the table is 10 while number of filled indices is 4


################################## Comparing Normal Lists and Dicts vs HashTable #############################################

constructing a list and a hash table of 50000000 length
and then try to search for value 49990998 linearly, using list comprehension
and using HashTable

time taken to fill the list is 5.213077

time taken to insert values into the HashTable is 10.304981

time to search linearly for value 49990998 in the list is 2.933679

time to search for value 49990998 in the list using list comprehension is 1.208404

value 49990998 --> 1

time to search for value 49990998 in the HashTable is 0.000319


size of the table is 50000000 while number of filled indices is 50000000


time to fill the dictionary is 11.683254

49990998

time to search the dictionary is 2.915389

[49990998]

time to search the dictionary is 1.819143

{49990998: 49990998}

time to search the dictionary is 1.798590
```
It is working fine!
