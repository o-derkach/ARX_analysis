cmake_minimum_required(VERSION 2.8)	 # �������� ������ CMake.

project(ARX_analysis)			# �������� �������

aux_source_directory("Src/ciphers"	SRC_DIRS)
aux_source_directory("Src/analyzer" 	SRC_DIRS)
aux_source_directory("Src" 		SRC_DIRS)

set(HEADER_FILES "Inc")			# ���� �����, �� ��� ����������

#set(EXTRA_LIBS crypto)

include_directories(${HEADER_FILES})

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3 -march=native")

add_executable(main ${SRC_DIRS})	# ������� ����������� ���� � ������ main

#find_library(M_LIB m)

#target_link_libraries(main ${M_LIB})
