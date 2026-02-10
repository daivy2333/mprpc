set(SRC_LIST mprpcapplication.cc mprpcconfig.cc rpcprovider.cc rpcheader.pb.cc mprpcchannel.cc mprpccontroller.cc logger.cc zookeeperutil.cc)
add_library(re_rpc STATIC ${SRC_LIST})

link_directories(/usr/local/lib)
target_link_libraries(re_rpc muduo_net muduo_base pthread zookeeper_mt)