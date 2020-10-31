from setuptools import setup, Extension

cython_exists = False
try:
    from Cython.Distutils import build_ext
    cython_exists = True
except ImportError:
    from distutils.command.build_ext import build_ext

if cython_exists:
    ext_modules=[
        Extension("pystack", ["stack/pystack.pyx", "stack/stack.c"]),
        Extension("pybstree", ["binary_search_tree/pybstree.pyx", "binary_search_tree/bstree.c"]),
        Extension("cpq", ["priority_queue/pqpy.pyx", "priority_queue/pq.c"]),
        Extension("pyhash", ["hash_table/pyhash.pyx", "hash_table/hash.c"])
    ]

with open("README.md", "r", encoding="utf8") as rm:
    readme = rm.read()
    
with open("requirements.txt") as rq:
    requirements = rq.read().split('\n')

setup(
      name="structpie",
      version="0.0.5",
      description="A set of python modules for data structures written in C",
      packages=["structpie"],
      install_requires=requirements,
      long_description=readme,
      include_package_data=True,
      long_description_content_type="text/markdown",
      url="https://github.com/MNoorFawi/struct-pie",
      author="Muhammad N. Fawi",
      author_email="m.noor.fawi@gmail.com",
      cmdclass = {"build_ext": build_ext},
      license="MIT",
      classifiers=[
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
    ],
      ext_modules = ext_modules
)