from structpie import *
from time import time

size = 10
print("\ninitialize an empty HashTable of size %d:" % size)
ht = HashTable(size, "float")
print("\ninsert new values into the table")
arr = [13, 11, 19, 91, 22, 12, 19, 94]
arr = [float(i) for i in arr]
for i in arr:
    ht.insert_val(i)

print("\nnow the table is not empty and looks like:")
ht.display()
print("\nsize of the table is %d while number of filled indices is %d\n" %
    (ht.length(), ht.occupied()))
print("\ntry now to search for and delete some values: (0 means False while 1 is True)")
print("search for value 13 --> %d" % ht.search_value(13.))
print("search for value 11 --> %d" % ht.search_value(11.))
print("search by index 1 --> value %s found" % ht.search_by_index(1))
print("remove value 13 --> %d" % ht.val_del(13.))
print("search again for value 13 --> %d" % ht.search_value(13.))
print("try again to remove value 13 --> %d" % ht.val_del(13.))
print("\nsize of the table is %d while number of filled indices is %d\n" %
    (ht.length(), ht.occupied()))
print("\nprint the table after the deletion")
ht.display()
print("\ninsert value 4")
ht.insert_val(4.)
ht.display()
print("\nsize of the table is %d while number of filled indices is %d\n" %
    (ht.length(), ht.occupied()))
print("\nsearch by index 4 --> value %s is found\n" % ht.search_by_index(4))
print("remove value 91 --> %d" % ht.val_del(91.))
print("\ntable is now looking like:")
ht.display()
print("\nsize of the table is %d while number of filled indices is %d\n" %
    (ht.length(), ht.occupied()))

print(
    "\n################################## Comparing Normal Lists and Dicts vs HashTable #############################################\n")

x = []
s = 50000000
n = 49990998
print(
    "constructing a list and a hash table of %d length\nand then try to search for value %d linearly, using list comprehension\nand using HashTable\n" %
    (s, n))

ht = HashTable(s, "int")

start = time()
for i in range(s):
    x.append(i)

end = time() - start
print("time taken to fill the list is %f\n" % end)

start = time()
for i in range(s):
    ht.insert_val(i)

end2 = time() - start
print("time taken to insert values into the HashTable is %f\n" % end2)

start = time()
for i in range(len(x)):
    if x[i] == n:
        # print("yes")
        break

end = time() - start
print("time to search linearly for value %d in the list is %f\n" % (n, end))

start = time()
r = [i
     for i in x
     if i == n
     ]
end = time() - start
print("time to search for value %d in the list using list comprehension is %f\n" % (n, end))

start = time()
print("value %d --> %d\n" % (n, ht.search_value(n)))
end = time() - start

print("time to search for value %d in the HashTable is %f\n" % (n, end))

print("\nsize of the table is %d while number of filled indices is %d\n" %
      (ht.length(), ht.occupied()))

d = {}
start = time()
for i in range(s):
    d[i] = i

print("\ntime to fill the dictionary is %f\n" % (time() - start))

start = time()
for k, v in d.items():
    if v == n:
        print(k)
        break

print("\ntime to search the dictionary is %f\n" % (time() - start))

start = time()
print([v for (k, v) in d.items() if v == n])
print("\ntime to search the dictionary is %f\n" % (time() - start))

start = time()
print({k: v for (k, v) in d.items() if v == n})
print("\ntime to search the dictionary is %f\n" % (time() - start))