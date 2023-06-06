# CDR-23 Robot
This repository is for a robot being built at UniMakers Club for the EurobotOpen 2023 competition that was held on May 23.

EurobotOpen is an amateur robotics competition open to young people, and the common objectives are to allow young people to be the actors of their learning and to put into practice their knowledge, skills, and attitudes by participating in a fun and friendly event.
The technical challenge is to build an autonomous robot as well as an optional secondary autonomous robot.

The robot in this project uses LiDAR technology and Omni wheels
for free movement.
The project contains both firmware and user interface.

There are currently three libraries available for use in this project:
 - Lidarx: a wrapper for the RPLidar library to be easy to use with ESP32.
 - Handy: An HTTP library wrapping over the robot movement for debugging purposes only, it eliminates the need for to be constantly wired to PC and or constant recompiles for testing movement and robot features.
 - Handy (Web interface): A web interface built using Svelte that controls all the robot including wheels acceleration, speed, movement, LiDAR...etc.
 - Movement: A library made specifically for Omni Wheels movement, and has methods that facilitate vector movement on a 2d plan.

Note: These libraries are specifically designed to be used with this project on ESP32 hardware, and the PINS are hardcoded. The author may refactor the Movement library in the future for use on all Arduino-supported hardware.


