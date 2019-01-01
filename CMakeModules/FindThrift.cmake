# - Find Thrift executable, header and library
#
# The module defines the following variables:
#
# THRIFT_EXECUTABLE - path to the thrift program
# THRIFT_INCLUDE_PATH - path to the include file
# THRIFT_LIBRARY_PATH - path to the library file

FIND_PROGRAM(THRIFT_EXECUTABLE thrift DOC "path to the thrift program")
MARK_AS_ADVANCED(THRIFT_EXECUTABLE)
