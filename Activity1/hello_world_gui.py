"""
  file: hello_world_gui.py
  
  Python script to demonstrate a window with some text using
   the Tkinter toolkit.
   
  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu

  Revision history:
      12/28/09  original Python version, from a demo program 
   
"""

from Tkinter import *    # import all names from Tkinter

# Create an instance of the class Tkinter.Tk
my_root_window = Tk()    # this is the top-level or "root" window

# Give it a label and invoke "pack" to put it in the root window 
label_1 = Label(my_root_window, text='Hello, 6810 student!',
               foreground="white", background="red")
label_1.pack()

# Change the font using config()
label_1.config(font=("Times", 24, "italic"))
      

# Start the "event loop" running, which waits for things to happen 
my_root_window.mainloop()  #    
