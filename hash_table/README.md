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

try now to search for and delete some values: (0 means False while 1 is True)
search for value 13 --> 1
search for value 11 --> 1
search by index 1 --> value 91 found
remove value 13 --> 1
search again for value 13 --> 0
try again to remove value 13 --> 0

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
```
It is working fine!
