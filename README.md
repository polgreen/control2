## DSSynth Toolbox

DSSynth is a MATLAB Toolbox that synthesizes digital controllers w.r.t. the stability specification, considering finite word-length (FWL) effects for physical plants represented by transfer-function or state-space equations. DSSynth considers fixed-point numerical representation for the digital controller and dynamic input ranges for the closed-loop control system. Currently, there are two versions of the DSSynth toolbox: command-line and MATLAB application.

#### Useful Links:

Download the latest version of DSSynth Toolbox at: https://drive.google.com/open?id=0ByHTHsS00rluT3FHZ05lc1JrbFE

Video Demonstration about DSSynth Toolbox Installation at: https://drive.google.com/open?id=0ByHTHsS00rluWnNHQnJjQ2hKWDg

Video Demonstration about DSSynth Toolbox Usage at: https://drive.google.com/open?id=0ByHTHsS00rluSnBOOVBwSEFveGM

#### Prerequisistes:

In order to execute DSSynth in MATLAB, the user must install the DSSynth Toolbox in MATLAB 2016b Linux version.

* Required tools to run the scripts: Linux/MATLAB;
* MATLAB version: at least version 2016b;

#### Installation:

In order to install DSSynth Toolbox, the user must download the DSSynth Toolbox installation file from https://drive.google.com/open?id=0ByHTHsS00rluT3FHZ05lc1JrbFE

After that, the following steps must be executed:

1. Open MATLAB;
2. Go to the directory where "DSSynth.mltbx" file is stored;
3. Execute the file with the “.mltbx$” extension (or double-click on it); a pop-up screen to install DSSynth Toolbox will be shown.
4. Click on the install button.

#### Automated Procedures Performed by MATLAB:

1. **Setup**: obtain the plant, fixed-point format and dynamic input ranges, and translate them to a struct in MATLAB;
2. **Parse**: obtain the digital plant implementation, and then translate it to an ANSI-C file;
3. **Execute**: obtain the ANSI-C file from the previous step, call CBMC-CEGIS as back-end program synthesis tool, and then perform the automated synthesis;
4. **Extract**: obtain the .log that is generated after the synthesis phase and then check the synthesized digital-controller.
5. **Report**: obtain the digital-controller, translate it to a MATLAB system, and then show the result to the user.

## Toolbox Usage:

#### Configuration:

(1) Before running the DSSynth toolbox, the user must execute the following command in the MATLAB Workspace in order to configure the toolbox:

	setenv('LD_LIBRARY_PATH','installation path to libstdc++');

Example:

	setenv('LD_LIBRARY_PATH','/usr/lib/x86_64-linux-gnu/libstdc++.so.6');

#### Toolbox Command-Line Usage:

Steps to use the DSSynth toolbox:

1) Download and Install MATLAB 2016b;
2) Download and Install the DSSynth Toolbox;
3) Design a digital-plant in MATLAB as transfer-function or state-space format;
4) Start the synthesis process by providing all required parameters (plant, numeric representation, and dynamic ranges).

###### Invoking Command:

synthesize(plant,intBits,fracBits, maxRange, minRange);

where:

- *plant*: digital-plant as transfer-function or state-space. See details about 'tf' and 'ss' commands in MATLAB to design digital-systems.
- *intBits*: represents the integer bits part;
- *fracBits*: represents the fractionary bits part;
- *rangeMax*: represents the maximum dynamic range;
- *rangeMin*: represents the minimum dynamic range;

In order to visualize the documentation about the *synthesize* function, please invoke the following command:

``help  synthesize``

Example (transfer-function):

	>> system = tf([-0.06875 0 0],[1 -1.696 0.7089],0.02)
	>> system =
		-0.06875 z^2
		----------------------
		z^2 - 1.696 z + 0.7089
		Sample time: 0.02 seconds
		Discrete-time transfer function.
	>> synthesize(system,8,8,1,-1)
	
Example (state-space):
	
	>> A = [0.90122,1.3429e-08;7.4506e-09,0];
	>> B = [128;0];
	>> C = [0.0014826,189.0217];
	>> D = [0];
	>> system = ss(A,B,C,D,0.02);
	>> synthesize(system,8,8,1,-1)
	
Video Demonstration about Synthesis for Plants in Transfer-function Format: https://drive.google.com/open?id=0ByHTHsS00rluSnBOOVBwSEFveGM

Video Demonstration about Synthesis for Plants in State-Space Format: https://drive.google.com/open?id=0ByHTHsS00rluSWlzSWZDbXAyaUE

#### Toolbox Application Usage:

In order to perform the synthesis of digital-controllers, a MATLAB Application was developed for DSSynth, which aims to improve usability and, consequently, attract more digital-system engineers (potential users). In Addition, the MATLAB Application is able to generate graphs as "Step Response" to show the stability of the digital-controllers generated by the DSSynth tool.

###### Invoking Application GUI by Command:

	>> DSSynth

Video Demonstration about the usage of the MATLAB Application (state-space): https://drive.google.com/open?id=0ByHTHsS00rluTVVZa3NWVFU3MEk

Video Demonstration about the usage of the MATLAB Application (transfer-function): https://drive.google.com/open?id=0ByHTHsS00rluNVo0OEI2UUozcmM
