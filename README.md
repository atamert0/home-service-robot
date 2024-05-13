In this project, we're using two cool tools: slam gmapping for making maps and amcl for finding where we are. With these, we're making a robot do simple task, like picking up and dropping off objects marked by a special sign.

This sign keeps an eye on the robot's movements using its odometry data. Once the robot reaches the spot, the sign disappears, showing it got the job done. Then, the robot heads to another spot to 'drop off' the objects, marked by another sign.

By using slam, localization, and these signs, we're making our robot act like it's doing real-world tasks smoothly and accurately.