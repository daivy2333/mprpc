# set(SRC_LIST calluserservice.cc ../user.pb.cc)
set(SRC_LIST callfriendservice.cc ../friend.pb.cc)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer ${Protobuf_LIBRARIES} re_rpc)