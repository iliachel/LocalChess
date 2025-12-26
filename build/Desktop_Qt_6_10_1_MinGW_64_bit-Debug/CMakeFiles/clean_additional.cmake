# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\chess_client1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chess_client1_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\chess_client2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chess_client2_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\chess_server_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chess_server_autogen.dir\\ParseCache.txt"
  "chess_client1_autogen"
  "chess_client2_autogen"
  "chess_server_autogen"
  )
endif()
