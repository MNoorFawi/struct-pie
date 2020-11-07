from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
#import os
#import sys


#os.system("gcc -fPIC -c bstree.c -o bstree.o")
#if sys.platform == "linux":
    #os.system("gcc -shared bstree.o -o libbstree.so")
    #os.system("export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./")
#elif "win" in sys.platform:
    #os.system("gcc -shared bstree.o -o libbstree.dll")
    #os.system('PATH="$PATH:./"')

ext_modules = [Extension("hash_bst", ["pyhash.pyx", "hash.c", "bstree.c"])]

setup(
  cmdclass = {"build_ext": build_ext},
  ext_modules = ext_modules
  )

#os.system("rm *.o *.so")