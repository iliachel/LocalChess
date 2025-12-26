cmake_minimum_required(VERSION 3.16)
project(QtChessLAN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Network REQUIRED)
# если у тебя Qt5 — раскомментируй:
# find_package(Qt5 COMPONENTS Core Network REQUIRED)

# ---------------- SERVER -----------------
add_executable(chess_server
    server/main.cpp
)
target_link_libraries(chess_server
    Qt6::Core Qt6::Network
    # Qt5::Core Qt5::Network
)

# ---------------- CLIENT 1 -----------------
add_executable(chess_client1
    client/main.cpp
)
target_link_libraries(chess_client1
    Qt6::Core Qt6::Network
)

# ---------------- CLIENT 2 -----------------
add_executable(chess_client2
    client/main.cpp
)
target_link_libraries(chess_client2
    Qt6::Core Qt6::Network
)

# ---------- RUN ALL (консольный запуск) ----------
if(WIN32)
    add_custom_target(run_all
        COMMAND start cmd /k chess_server
        COMMAND start cmd /k chess_client1
        COMMAND start cmd /k chess_client2
    )
else()
    add_custom_target(run_all
        COMMAND ./chess_server &
        COMMAND ./chess_client1 &
        COMMAND ./chess_client2 &
    )
endif()
