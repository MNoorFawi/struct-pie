# Priority Queue

Create the python module from C scripts
```bash
python3 setup.py build_ext --inplace
```

In a python session, let's try the module
```python
>>> import cpq
>>> pq = cpq.PQ()
>>> pq.display_pq()

        The queue is Empty
>>> pq.push(b"exercise", 3)
>>> pq.push(b"sleep", 2)
>>> pq.push(b"repeat", 1)
>>> pq.push(b"code", 5)
>>> pq.display_pq()
(
        {'task': code, 'priority': 5}
        {'task': exercise, 'priority': 3}
        {'task': sleep, 'priority': 2}
        {'task': repeat, 'priority': 1}
)
>>> pq.exec_task()

Task (code) with priority (5) has been removed
'code'
>>> pq.display_pq()
(
        {'task': exercise, 'priority': 3}
        {'task': sleep, 'priority': 2}
        {'task': repeat, 'priority': 1}
)
>>> pq.exec_task()

Task (exercise) with priority (3) has been removed
'exercise'
>>> pq.exec_task()

Task (sleep) with priority (2) has been removed
'sleep'
>>> pq.exec_task()

Task (repeat) with priority (1) has been removed
'repeat'
>>> pq.exec_task()

        The queue is empty

''
>>> pq.display_pq()

        The queue is Empty
>>> quit()
```

It is working fine!
