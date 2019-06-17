# ********************************************** Python C Extension Interface ***********************************************
# In many cases, building an extension is more complex than defining an extension named demo which is build by compiling a single source file, demo.c. 
# Additional preprocessor defines and libraries may be needed.
#

# This is demonstrated in the example below.

from distutils.core import setup, Extension

module1 = Extension('demo',
define_macros = [('MAJOR_VERSION', '1'),
('MINOR_VERSION', '0')],
include_dirs = ['/usr/local/include'],
libraries = ['tcl83'],
library_dirs = ['/usr/local/lib'],
sources = ['demo.c'])
setup (name = 'PackageName',
version = '1.0',
description = 'This is a demo package',
author = 'Martin v. Loewis',

author_email = 'martin@v.loewis.de',
url = 'https://docs.python.org/extending/building',
long_description = '''
This is really just a demo package.
''',
ext_modules = [module1])

