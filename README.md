# DE10-GPU
GPU for OENG1167 in Verilog HDL for DE10 series boards

# Build Instructions

Currently, only Linux is supported for the build process, and as of present, only the DE10 Standard board is compatible
(though this can be modified )

## Building the Drivers
There are 2 drivers you need to build. The OpenGL static library (`libgl.a`) and the actual hardware driver (`drvr3d.a`)
Luckily, there's a script that will manage the entire build for you, called `build_drivers.sh` located in /drv/

1. Navigate to the /drv/ directory
2. Run `./build_drivers.sh`. This will make both the OpenGL and the hardware driver
3. The relveant drivers will be found in their corresponding folders

Now that you've built the software, it's time to actually build the Verilog (hardware) portion of the project

1. Open up Quartus Prime (we used 20.1)
2. Open up the Rush3D `.qpf` file located in `/hw/`
3. Do a full synthesis of the project to generate the `.sof`

Now that it's built, you can flash the GPU onto the FPGA

1. On your DE10, do a HPS Reset (or reset the board)
2. In your serial terminal, stop the boot process by pressing any key
3. Open the Quartus JTAG Programmer
4. Flash the project
5. Do another HPS reset and let QNX boot properly

You can now run OpenGL projects on your DE10

## QNX Setup
TODO: Copy Glenn's instructions here!
