# PID Controller

---
## Introduction
In this project, I implemented the PID controller in "src/PID.cpp" file. I also implemented the twiddle algorithm for tuning hyperparamters in the "src/PIDOptimizer.cpp". The hyperparamters was first selected manually by trial-and-error in the simulation. Then the twiddle algorithm was used to fine tune the hyperparameters.


## Basic Build Instructions
The CMakeLists.txt was modified to include compilation of "src/PIDOptimizer.cpp".
Here are the steps to build and run the binary:

1. Make a build directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./pid`. 


## Effects of P, I, D Components
The P (proportional) component sets the steering angle in proportion to the cross track error. Therefore, it attempts to steer the car towards the center of the lane. With only the P component, the steering tend to overshoot and thus the car would oscillate around the center of the lane.

The D (differential) component counteracts the car's tendency of overshooting and oscillation. A proper D parameter can make the car approach the center line smoonthly.

The I (integration) component is intended to counteract the systematic bias such as the steering drift.

## Selection of Hyperparameters
The initial parameters were manually selected in a trial-and-error manner. As the car could easily got out of track if the hyperparameters were not selected properly, it was challenging to apply Twiddle to automatically tune the hyperparameters without a good initial parameters. The initial parameters were selected using the following procedure:

1. Set D and I to 0 and gradually increase P from 0 until the car reaches the state of stable oscillation.
2. Then gradually increase D until the car stops oscillation.
3. Gradually increase I until the car does not go off track.

The initially selected parameters were: P=0.1, D=0.75 and I=0.00001. 

Then I used the Twiddle algorithm to fine-tune the parameters. Note that the road conditions vary during a complete lap, therefore, to make the comparision fair, the average error for each set of parameters was evaluated once a whole lap was passed (~800 steps). The final parameters were found after evaluating for about 35 laps. The final parameters were P=0.1, D=0.7, and I=0.00001.

