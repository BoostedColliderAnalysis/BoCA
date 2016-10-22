#
# Copyright (C) 2015-2016 Jan Hajer
#
set(WimpmassSources
Mt2.cpp
Invisible2.cpp
Invisible3.cpp
)
create_library(Wimpmass WimpmassSources)

if(BUILD_TESTING)
  add_executable(TestMt2 TestMt2.cpp)
  message("${GTEST_LIBRARIES}")
  target_link_libraries(TestMt2 ${GTEST_LIBRARIES} Wimpmass pthread)
  add_test(Mt2 TestMt2)
endif()
