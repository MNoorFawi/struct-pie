# Priority Queue

Create the python module from C scripts
```bash
python3 setup.py build_ext --inplace
```

In a python session, let's try the module
```python
import cpq
pq = cpq.PQ()
pq.display()

#        The queue is Empty

pq.push(b"exercise", 3)
pq.push(b"sleep", 2)
pq.push(b"repeat", 1)
pq.push(b"code", 5)
pq.display()
# (
#        {code, 5}
#        {exercise, 3}
#        {sleep, 2}
#        {repeat, 1}
# )
pq.pop()

# (code) with priority (5) has been removed
# 'code'
pq.display()
# (
#        {exercise, 3}
#        {sleep, 2}
#        {repeat, 1}
# )
pq.pop()

# (exercise) with priority (3) has been removed
# 'exercise'
pq.pop()

# (sleep) with priority (2) has been removed
# 'sleep'
pq.pop()

# (repeat) with priority (1) has been removed
# 'repeat'
pq.pop()

#        The queue is empty

# ''
pq.display()

#        The queue is Empty
```

It is working fine!
