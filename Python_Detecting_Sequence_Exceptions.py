# Python Detecting Sequence Exceptions.
# A simple example of detecting Dictionary exceptions and passing them on. 
# The following example function shows some error cleanup. 
#

def incr_item(dict, key):

    try:
        item = dict[key]

    except KeyError:
        item = 0

    dict[key] = item + 1
