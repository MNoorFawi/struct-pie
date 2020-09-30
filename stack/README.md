# LIFO & FIFO Stack

Create the python module from C scripts
```bash
python3 setup.py build_ext --inplace
```

In a python session, let's try the module
```python
from stack import *
st = Stack()
st.length()
# 0
st.push(13)
st.length()
# 1
st.push(11)
st.push(19)
st.push(91)
st.length()
# 4
st.display()
# 13 11 19 91
st.pop()
# 91
st.display()
# 13 11 19
st.length()
# 3
st.empty()
# False
st.popleft()
# 13
st.popleft()
# 11
st.pop()
# 19
st.empty()
# True
st.length()
# 0
st.pop()

#         STACK IS EMPTY

#-1
st.popleft()

#         STACK IS EMPTY

#-1 
```

It is working fine!
