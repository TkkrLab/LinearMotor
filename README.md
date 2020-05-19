
  
# DIY Ironless Linear Motor
Brushless dc (BLDC) motors constist of a stator and a rotor, which produce a rotational torque when powered. A linear motor is essentially a BLDC motor which has been folded open and produces a linear force by applying current to the different phases. This causes the [forcer](#forcer) (rotor)  to move along a [magnetic track](#magnetic-track) (stator).

There are several different types of linear motors:

* Cylindrical linear motor
* U-Channel linear motor
* Flat Type linear motor
* Slotless Ironless flat motor
* Slotless Iron flat motor
* Slotted Iron flat motor

We will focus on the U-Channel Linear motor / Ironless linear motor.

__So why make our own?__
Simply, just because we can! And its awesome to learn about new stuff.

We do wish to mention [Vulcaman's](https://www.instructables.com/id/DIY-IRONLESS-LINEAR-SERVO-MOTOR/) motor build. This version is based on a simple L6234 motor controller IC and implements a basic sinusoidal commutation.

## Required tools
Glue gun\
Drill press or Milling machine\
M4 tap\
3.3mm and 4.5mm drills\
3d printer (You can also order the 3d printed parts from a printing service)\






## Required Materials
Acrylic sheet to make a mould casing\
N35 Neodynium magnets - 100 pieces\
3x Copper coils ![Coils](/images/coils.jpg) \
Polyurethane\
Silicone rubber\
Optional: Copper wire 0.4mm\
Cyanoacrylate glue ( superglue )\
M4x18 bolts



#### Forcer
![Forcer](/images/forcer.jpg) 
	coils
#### Magnetic Track
	magnets
		spacing
		
### Commutation
Commutation is the process of switching current in the motor phases to generate motion. Today most linear motors use a 3 phase brushless design. There are three different ways to commutate a motor:

	- Sinusoidal
	- trapezoidal
	- six step


To drive our motor we are using a [TMC4671](https://www.trinamic.com/products/integrated-circuits/details/tmc4671-es/) controller from [Trinamic](#sponsors)

We use this drive specifically because it has hardware FOC (Field Oriented Control). The TMC4671 [datasheet](https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC4671_datasheet_v1.06.pdf)  explains very well what FOC is exactly, so please check it out.

	

		
## Sponsors
We would like to thank our Trinamic for providing us with a TMC4671 evaluation kit.
![Trinamic](/images/TRINAMIC_LOGO_STANDARD_RGB.png)