#
# Copyright (C) 2015-2016 Jan Hajer
#
create_test(Mt2Test TestMt2.cpp)
create_test(Invisible2 TestInvisible2.cpp)
configure_file(Wimpmass.lhe ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
