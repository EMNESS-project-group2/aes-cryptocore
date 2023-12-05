# Exercise 1: HW description file
Now it’s time to try to build your own HW description file!

Try to modify by yourself the hw description files of your system in order to communicate through the AXI4 interface. Instantiate your hw, the processor and the communication needed.

Use the main guide and the README.md guide for reference on the steps you need to do.

A solution for this exercise is inside the repository, in vivado/ip_repo/hdl/*

# Exercise 2: Test your HW
Now it’s time to try to test your own HW description file!

Modify the helloworld.c template in Vitis in order to write and read on the registers you settled up in the previous exercise.

Use the main guide and the README.md guide for reference on the steps you need to do.

A solution for this exercise is inside the repository, in vitis/bare_metal_test.c. 
There is also a zip file containing the project of vitis. You can open it directly there if you are not able to develop your own test.

# Exercise 3: Build your linux system
Now it’s time to try to test what you learned in the previous steps.
Try to follow the guide in the repository and build your linux system. 
Flash the system through JTAG and then SD card.

Follow the main guide README.md for the steps involved in the process. For connections related problems, check also the /docs/connections.md file.

# Exercise 4: Build the Driver
The final exercises are related to the driver build and the test. 

Try to write your own driver implementation that uses your device. A possible implementation is in driver/


# Exercise 5: Test your driver
Write a C application to run on your linux system to check if the driver is working correctly. A possible solution is in driver/


