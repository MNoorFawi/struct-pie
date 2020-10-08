# LIFO & FIFO Stack

### Stack data structure written in C that is of multiple type; ("int", "float", "str").

Create the python module from C scripts
```bash
python3 setup.py build_ext --inplace
```
In a python session, let's try the module
```python
from pystack import *

stack = Stack("int")

stack.length()
# 0

stack.pop()
# STACK IS EMPTY
# -1

stack.push(13)
stack.push(11)
stack.push(19)
stack.push(91)

stack.length()
# 4
stack.display()
# [13 11 19 91 ]

stack.pop()
# 91
stack.popleft()
# 13
stack.display()
# [11 19 ]

print("#############################################")
stack = Stack("float")

stack.length()
# 0
stack.push(1.3)
stack.push(1.1)
stack.push(1.9)
stack.push(9.1)

stack.length()
# 4
stack.display()
# [1.30 1.10 1.90 9.10 ]
stack.pop()
# 9.1
stack.popleft()
# 1.3
stack.display()
# [1.10 1.90 ]
print("#############################################")
stack = Stack("str")

stack.length()
# 0
stack.push("Hello")
stack.push("Hola")
stack.push("Ciao")
stack.push("Merhaba")

stack.length()
# 4
stack.display()
# [Hello, Hola, Ciao, Merhaba, ]
stack.pop()
# b'Merhaba'
stack.popleft()
# b'Hello'
stack.display()
# [Hola, Ciao, ]
```
It is working fine!
