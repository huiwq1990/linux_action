#This is the makefile of EpollTest

.PHONY:all
all:fork_var_share fock_file_share
server:
	gcc fock_file_share.c -o fock_file_share
client:
	gcc fork_var_share.c -o fork_var_share.c
clean:
	rm -f fork_var_share fock_file_share