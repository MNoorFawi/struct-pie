# LIFO Stack

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
# Value 91 is popped from stack
st.display()
# 13 11 19
st.length()
# 3
st.empty()
# 0
st.pop()
# Value 19 is popped from stack
st.pop()
# Value 11 is popped from stack
st.pop()
# Value 13 is popped from stack
st.empty()
# 1
st.length()
# 0
```

It is working fine!
