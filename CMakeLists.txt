cmake_minimum_required(VERSION 3.14)
project(tp4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Source files
set(COMMON_SOURCES
  common/messages.cpp
  common/tcp_connection.cpp
  common/rpc_protocol.cpp
  logic/logic.cpp
)

add_executable(
  agent
  agent.cpp
  ${COMMON_SOURCES}
)

target_include_directories(
  agent PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  agent
  Threads::Threads
)


add_executable(
  mock_server
  mock_server.cpp
  ${COMMON_SOURCES}
)

target_include_directories(
    mock_server PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  mock_server
  Threads::Threads
) 


