from pyhash import *

size = 10
print("initialize an empty HashTable of size %d:" % size)
ht = HashTable(size)
print("\ninsert new values into the table")
arr = [13, 11, 19, 91, 22, 12, 94]
for i in arr:
    ht.insert_val(i)
    
print("\nnow the table is not empty and looks like:")
ht.display()
print("\ntry now to search for and delete some values: (0 means False while 1 is True)")
print("search for value 13 --> %d" % ht.search_value(13))
print("search for value 11 --> %d" % ht.search_value(11))
print("search by index 1 --> value %d found" % ht.search_by_index(1))
print("remove value 13 --> %d" % ht.val_del(13))
print("search again for value 13 --> %d" % ht.search_value(13))
print("try again to remove value 13 --> %d" % ht.val_del(13))
print("\nprint the table after the deletion")
ht.display()
print("\ninsert value 4")
ht.insert_val(4)
ht.display()
print("\nsearch by index 4 --> value %d is found\n" % ht.search_by_index(4))
print("remove value 91 --> %d" % ht.val_del(91))
print("\ntable is now looking like:")
ht.display()