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

key(0):
key(1):  91  11
key(2):  12  22
key(3):  13
key(4):  94
key(5):
key(6):
key(7):
key(8):
key(9):  19

try now to search for and delete some values: (0 means False while 1 is True)
search for value 13 --> 1
search for value 11 --> 1
search by index 1 --> value 91 found
remove value 13 --> 1
search again for value 13 --> 0
try again to remove value 13 --> 0

print the table after the deletion

key(0):
key(1):  91  11
key(2):  12  22
key(3):
key(4):  94
key(5):
key(6):
key(7):
key(8):
key(9):  19

insert value 4

key(0):
key(1):  91  11
key(2):  12  22
key(3):
key(4):  4  94
key(5):
key(6):
key(7):
key(8):
key(9):  19

search by index 4 --> value 4 is found

remove value 91 --> 1

table is now looking like:

key(0):
key(1):  11
key(2):  12  22
key(3):
key(4):  4  94
key(5):
key(6):
key(7):
key(8):
key(9):  19
```
It is working fine!
