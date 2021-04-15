#!/usr/bin/env python 
#
#  file: run_area_cmdline1.py
#
#  This python script runs the C++ code area_cmdline for a sequence
#   of values that are hardcoded in the script.  The output is to
#   the screen.
#
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
#
#  Revision history:
#      28-Dec-2010  original version
#
#  Notes:  
#   * run with: "python run_area_cmdline1.py" or just "./run_area_cmdline1.py"
#   * should check the return code to make sure it worked!
#   * could use Popen instead of call
#   * pass a full string to the shell with the first method below
#      or pass a list of arguments without "shell=True".
#  
#*************************************************************************
from subprocess import call    # make the "call" function available

# Define the inputs at the top, so they are easy to find and change
value_list1 = [5, 10, 15, 20, 25]
value_list2 = [1.0, 0.5, 0.25]
reps = [1,2,3,4,5]
# Ok, let's do it . . .
print "\nFirst try a list of integers:"

index = 0
for radius in value_list1:    # don't forget the colon!  
  my_command = "./area_cmdline.x " + str(radius) + " " + str(reps[index])   # convert radius to a string
  retcode = call(my_command, shell=True)    # pass "my_command" to be executed
  index+=1

print "\nNow try a list of decimal numbers:"

# note the alternative passing of the command
for radius in value_list2:    # don't forget the colon!
  my_command = ["./area_cmdline", str(radius)]  # convert radius to a string
  retcode = call(my_command)
  
print "The last return code was", retcode

#*************************************************************************
