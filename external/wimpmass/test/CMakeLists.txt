#
# Copyright (C) 2015-2016 Jan Hajer
#
create_test(Mt2 Mt2.cpp)
create_test(Invisible2 Invisible2.cpp)
configure_file(Wimpmass.lhe ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
