### A simple example of using `call_usermodehelper`

This trivial module calls a delayed worker and an immediate function when it is loaded

The delayed function will output in dmesg after the immediate function and the two files for the ls output should be created in /tmp
