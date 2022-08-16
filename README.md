# Person-Following Laptop Stand

<h1>Overview</h1>
Built a robot that takes a laptop placed on top, and follows the user left/right and up/down using the laptop's camera.
The purpose for this device is to keep the user centered during online meetings and calls, which are nowadays increasingly more common.
The device uses DC motors for the lateral movement, and a mechanism (a lead scew attached to a DC motor) for the vertical movement.
More details below.

- The 3D modeling was done using Fusion360.
- The models were 3D printed using Cura software, and 3D-printed using Prusa i3 Mk3 printer.
- All wooden parts are in MDF, and were laser cut.
- The code was written in Python and Arduino.
- The electronics' schematics were done using Fritzing.

![image](https://user-images.githubusercontent.com/67190150/184812113-17e6148e-1723-4d40-8125-5debbed760a8.png)
![image](https://user-images.githubusercontent.com/67190150/184813110-b85f40f3-302f-4c35-9b35-42708b9d3e25.png)
![image](https://user-images.githubusercontent.com/67190150/184813147-31f1df87-fd61-4a39-9d7a-7bf6eb7be660.png)
![image](https://user-images.githubusercontent.com/67190150/184813209-3937d600-fe72-4613-88ae-6724d97bb53e.png)


# The robot is divided into two levels: upper and lower. 
<h2>Lower Level<h2>

![LOWER](https://user-images.githubusercontent.com/67190150/184819032-d82c35e8-eed8-40c8-9641-4815a8f3d768.jpg)

In the lower level, the wheeilng system is placed: this is used for the left/right movement. Instead of directly attaching the wheels to the motors, a gearing system (2 gears, 1:1 ratio) was used in combination with a 3D-printed component with 2 radial ball bearings in ints inside: this allowed to transfer the weight load from the motors' shafts to the device.
![activeWheel](https://user-images.githubusercontent.com/67190150/184816164-2b1d5bab-ac05-4c32-bcba-9bd9d5b29b90.jpg)
![activeWheelOpen](https://user-images.githubusercontent.com/67190150/184816120-5cb27ee5-512a-405d-8616-2262017b6068.jpg)

There is also a mechanism (composed of a DC motor and a lead screw) for the up/down movement: this mechanism will move the base at the top of the device on which the laptop is placed.
![12motor](https://user-images.githubusercontent.com/67190150/184816331-e5adbe15-e80f-4192-a88a-0da8f67148b6.jpg)

Finally, two IR sensors are placed at the extremities of the device, which are used for edge detection and preventing the robot from falling off of the surface on which it is placed.

<h2>Upper Level</h2>
 
![UPPERFLOOR](https://user-images.githubusercontent.com/67190150/184819058-0c166a46-0331-499c-b2ce-ad3499d2580d.jpg)

In the upper level, the Arduino, breadboard and AC/DC converter (or, if connecting the robot to an electric outlet is not feasible, a battery) are placed.
Two IR sensors are also placed for preventing the base from moving too high or too low. An extra component is installed to maintain the rotation of the lead screw centred. 
![image](https://user-images.githubusercontent.com/67190150/184816764-5ec62bfc-1975-4970-adba-5fedd5f44a88.png)

Guiding rods are installed at the four corners of the upper level: their purpose is to maintain the fixed orientation of the base, which  in turn enables the lead screw to move the base up and down. These guiding rods work in combination with the rods that are fixed underneath the laptop base. Additionally, a 3D-printed component is also fixed to enable the transfering of the lead screw's rotational work into linear vertical movement of the base.
![image](https://user-images.githubusercontent.com/67190150/184816817-98f9817d-6510-4914-9919-ecfe5efff5a7.png)
