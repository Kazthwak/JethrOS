# JethrOS

This is a garbage OS made by me. 
I'm currently working on interrupts but I think having them generated on complile time is not how your supposed to do it but it works ;-).
The os-image is a binary file that if written to the start of a disk, *should* work properly.
The makefile generates an os-image and then runs it using qemu.
I am aware that the makefile's structure completely defeats the purpose makefiles and is no better than a bash script.
