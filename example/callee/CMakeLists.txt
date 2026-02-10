# set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

add_executable(provider ${SRC_LIST})
target_link_libraries(provider ${Protobuf_LIBRARIES} re_rpc)