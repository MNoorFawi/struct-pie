from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [Extension("cpq", ["pqpy.pyx", "pq.c"],
                         #include_dirs = ["."]
                         )]

setup(
  cmdclass = {'build_ext': build_ext},
  ext_modules = ext_modules
)