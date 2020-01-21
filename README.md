# hax
Starter pack for OSCP/HTB/VHL/etcetera labs.

Common 
This has some basic shells and enumeration scripts. Gets you through 80% of boxes. I usually build this out with some common exploits (AutoBlue, JuicyPotato.exe) and other enumeration scripts (Sherlock, unixprivchecker). But they're usually not required.

spawnshell.py 

Generates either a bunch of shells or commands for shells (depending on the type you pick), for a specified interface. Good to run when you've got a few boxes to get through and an unchanging IP address.

usage example: python spawnshell.py tun0 1

requirements: pip install netifaces

Cherrytree doc

Skeleton for taking notes. I migrated to Cherrytree from OneNote because I found the shortcuts for creating and moving nodes genuinely useful, and I also like the icons for quickly identifying what's what. 

I based my template off: https://411hall.github.io/assets/files/CTF_template.ctb 

Pretty straightforward and easy to use. Load a skeleton for each box. During enum, slide all the services you're investigating out of the 'service list' folder (shift+left arrow). Paste relevant scan results into the appropriate spots within each service. Do you your investigations and keep your notes.