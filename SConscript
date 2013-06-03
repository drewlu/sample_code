import os

env = Environment(CC = 'gcc', CCFLAGS = '-O3')
#env = Environment(CC = 'gcc', CCFLAGS = '-O0 -g')
VariantDir('./output/mymock', 'mymock', duplicate=0)

mock_objs = env.Object(source=[Glob('#./output/mymock/*.cpp')])

env.SharedLibrary(target='sample_lib', source=["sample_lib.cpp"])


env.Program('atest', 'a.c')
env.Program('zb', 'zombie.c')
env.Program('bigfork', 'bigfork.c')
env.Program('inherit', 'inherit.cpp')
env.Program('strlenth', 'str_test.cpp')
env.Program('sock_server', 'sock_server.cpp')
env.Program('sock_read_timeout', 'sock_read_timeout.cpp')
env.Program('http_proxy_client', 'http_proxy_client.cpp')
env.Program('nginx_client', 'nginx_client.cpp')
env.Program('stream_test', 'stream_test.cpp')
env.Program('delete_void', 'delete_void.cpp')
env.Program('constructor', 'constructor.cpp')
env.Program('mix_ref_ptr', 'mix_ref_ptr.cpp')
env.Program('connect_timeout_server', 'connect_timeout_server.cpp')
env.Program('epoll_server', 'epoll_sample.cpp')
env.Program('epoll_send_server', 'epoll_send_server.cpp')
env.Program('epoll_recv_only_server', 'epoll_recv_only_server.cpp')
env.Program('while_recv_server', 'while_recv_server.cpp')

env.Program('epoll_client', 'epoll_client.cpp')
env.Program('while_client', 'while_send_client.cpp')
env.Program('epoll_send_client', 'epoll_send_client.cpp')

env.Program("struct_init", "struct_init.cpp")
env.Program("config_parse", "config_parse.cpp")
env.Program("override_childish", "override_childish.cpp")

#SConscript(dirs=["override"], exports='env')
env.Program('mock_test', source=['mock_test.cpp', mock_objs], CPPPATH=['mymock'])
env.Program('cache_line_test1', 'cache_line_test1.cpp')
env.Program('cache_line_test2', 'cache_line_test2.cpp')
env.Program('aiosize', 'aio_size.cpp')

#env.Program('sample_case', source=['sample_case.cpp'], LIBS=['sample_lib'], LIBPATH=['./output'])
#

#SConscript(dirs=["epoll_rhs"], exports='env')
