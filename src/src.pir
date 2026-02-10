<pir>
<meta>
name: src
root: /home/daivy/projects/muduo_learn/mprpc/src
profile: generic
lang: CC,H
</meta>
<units>
u0: mprpccontroller.cc type=CC role=lib module=src
u1: logger.cc type=CC role=lib module=src
u2: mprpcapplication.cc type=CC role=lib module=src
u3: mprpcchannel.cc type=CC role=lib module=src
u4: zookeeperutil.cc type=CC role=lib module=src
u5: rpcheader.pb.cc type=CC role=lib module=src
u6: rpcprovider.cc type=CC role=lib module=src
u7: mprpcconfig.cc type=CC role=lib module=src
u8: include/mprpccontroller.h type=H role=lib module=include
u9: include/mprpcconfig.h type=H role=lib module=include
u10: include/rpcprovider.h type=H role=lib module=include
u11: include/zookeeperutil.h type=H role=lib module=include
u12: include/lockqueue.h type=H role=lib module=include
u13: include/mprpcapplication.h type=H role=lib module=include
u14: include/logger.h type=H role=lib module=include
u15: include/mprpcchannel.h type=H role=lib module=include
u16: include/rpcheader.pb.h type=H role=lib module=include
</units>
<dependency-pool>
d0: include:[algorithm]
d1: include:[arpa/inet.h]
d2: include:[bits/getopt_core.h]
d3: include:[condition_variable]
d4: include:[functional]
d5: include:[google/protobuf/arena.h]
d6: include:[google/protobuf/arenastring.h]
d7: include:[google/protobuf/descriptor.h]
d8: include:[google/protobuf/extension_set.h]
d9: include:[google/protobuf/generated_message_reflection.h]
d10: include:[google/protobuf/generated_message_table_driven.h]
d11: include:[google/protobuf/generated_message_util.h]
d12: include:[google/protobuf/inlined_string_field.h]
d13: include:[google/protobuf/io/coded_stream.h]
d14: include:[google/protobuf/message.h]
d15: include:[google/protobuf/metadata_lite.h]
d16: include:[google/protobuf/port_def.inc]
d17: include:[google/protobuf/port_undef.inc]
d18: include:[google/protobuf/reflection_ops.h]
d19: include:[google/protobuf/repeated_field.h]
d20: include:[google/protobuf/service.h]
d21: include:[google/protobuf/unknown_field_set.h]
d22: include:[google/protobuf/wire_format.h]
d23: include:[google/protobuf/wire_format_lite.h]
d24: include:[iostream]
d25: include:[limits]
d26: include:[lockqueue.h]
d27: include:[logger.h]
d28: include:[mprpcapplication.h]
d29: include:[mprpcchannel.h]
d30: include:[mprpcconfig.h]
d31: include:[mprpccontroller.h]
d32: include:[muduo/net/EventLoop.h]
d33: include:[muduo/net/InetAddress.h]
d34: include:[muduo/net/TcpConnection.h]
d35: include:[muduo/net/TcpServer.h]
d36: include:[mutex]
d37: include:[rpcheader.pb.h]
d38: include:[rpcprovider.h]
d39: include:[semaphore.h]
d40: include:[stdlib:c]
d41: include:[stdlib:py]
d42: include:[sys/socket.h]
d43: include:[sys/types.h]
d44: include:[thread]
d45: include:[unordered_map]
d46: include:[zookeeper/zookeeper.h]
d47: include:[zookeeperutil.h]
</dependency-pool>
<dependencies>
u0->refs:[d31]
u1->refs:[d27]
u2->refs:[d28 d24 d41 d2]
u3->refs:[d28 d47 d43 d41 d29 d40 d1 d24 d42]
u4->refs:[d28 d24 d47]
u5->refs:[d9 d13 d17 d8 d37 d7 d18 d0 d23 d22 d16]
u6->refs:[d28 d38 d47 d27 d37]
u7->refs:[d41 d24 d30 d27]
u8->refs:[d41 d20]
u9->refs:[d41 d45]
u10->refs:[d34 d33 d4 d20 d32 d7 d45 d35]
u11->refs:[d41 d39 d46]
u12->refs:[d41 d44 d3 d36]
u13->refs:[d31 d30 d29]
u14->refs:[d26 d24 d40]
u15->refs:[d20 d37 d14 d7]
u16->refs:[d9 d11 d15 d13 d17 d19 d12 d8 d14 d5 d41 d21 d25 d10 d6 d16]
</dependencies>
<symbols>
writeLogTask:u1 func
ShowArgsHelp:u2 func
global_watcher:u4 func
InitDefaultsscc_info_RpcHeader_rpcheader_2eproto:u5 func
Push:u12 func
Pop:u12 func
RpcHeader:u16 func
swap:u16 func
Swap:u16 func
UnsafeArenaSwap:u16 func
</symbols>
</pir>