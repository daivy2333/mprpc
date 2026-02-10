set(SRC_LIST mprpcapplication.cc mprpcconfig.cc rpcprovider.cc rpcheader.pb.cc mprpcchannel.cc mprpccontroller.cc logger.cc zookeeperutil.cc)
add_library(re_rpc STATIC ${SRC_LIST})

# 添加re_muduo的头文件路径
include_directories(${PROJECT_SOURCE_DIR}/../../re_muduo)
link_directories(${PROJECT_SOURCE_DIR}/../../re_muduo/lib)
target_link_libraries(re_rpc re_muduo pthread zookeeper_mt)