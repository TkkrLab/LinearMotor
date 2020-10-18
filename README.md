# DIY Ironless Linear Motor
Brushless DC (BLDC) motors constist of a stator and a rotor, which produce a rotational torque when powered. A linear motor is essentially a BLDC motor which has been folded open and produces a linear force by applying current to the different phases. This causes the [forcer](#forcer) (rotor) to move along a [magnetic track](#magnetic-track) (stator).
![LinearMotorPrincipal](/images/Linearmotorprinzip.png)


## Linear Motor basics
As explained a linear motor is a flattened BLDC motor. There are several different types, each having its own advantages and disadvantages. We decided to go with an ironless linear motor.
An ironless linear motor has two main components:
* A magnetic track composed of two metal plates with magnets attached and a seperator / spacer. 
* A forcer composed of 3 copper coils, an aluminium housing, wiring and epoxy.
![CrossSection](/images/Cross-sectional-view-of-an-ironless-linear-motor.png)


### Magnetic Track
To get the correct spacing we take a look at a BLDC, in this case a three phase two pole motor.
![Three phase two pole motor](/images/twoPoleMotor.jpg)

During rotation one of the phases of the motor will move from a positive polarity (+) to the negative polarity (-) and back to positive. The other two phases have a 120° offset from this phase, but for now lets focus on just the one phase. This translation in polarity means that we now know the spacing between magnets of the same polarity => 360° rotation, or 3* distance between coils(coil spacing). To get the coil spacing we take a look at what coils we have available.

The coils that we purchased were produced specifically for linear motors, they have a size of 25.5*14mm. Since we also want to add watercooling channels between the coils we decided on a spacing of 18mm. If you do not wish to add watercooling we would recommend putting the coils as close together as possible.

If we apply these values we would have a magnet with positive polarity at 0, negative polarity at 27mm and positive again at 54mm. Even though this would work, the motor will not be very powerfull. This can be improved by adding more pole pairs to the motor. You can keep adding adding pole pairs according to the following formula until you reach a magnet spacing / size suitable for your motor:  
![Formula](/images/MagnetSpacingFormula.svg)  
You can also decide on a magnet spacing first and calculate the coil spacing accordingly.


### Forcer
As previously mentioned we want to add watercooling to our linear motor so we can put more current into the coils without overheating the system. This adds some more complexity to the design of the forcer. 
For more details on the design check out [Version 1](/Solidworks/V1/README.md) and [Version 2 Watercooled](/Solidworks/V2_Watercooled/README.md)

There are some companies that sell coils made to specifications. We got ours from [JHCoils](https://www.jhcoils.com/), but if you are up to it you can always wind your own. If you decide to buy your coils, just keep in mind that you will have to pay extra if they do not have the required tooling available (So ask which sizes they have available already and pick one of those).
![Coils](/images/coils.jpg)

#### Coil specs
dimensions: 25.5*14 mm  
wire: 0.4mm

## Commutation
Commutation is the process of switching current in the motor phases to generate motion. Our ironless linear motors is based on a three phase motor design. There are several different ways to commutate a three phase motor, of which sinusoidal control is the most efficient and most commonly used in the higher-end motor drives. 

In sinusoidal commutation, all three wires are permanently energized with a sinusoidal current that is 120 degrees apart on each phase. This has the effect of creating a North/South magnetic field that rotates inside the motor cage. As shown in the figure below:  
![Commutation](/images/Rotating_field-compact.gif)


If a magnet is placed on a rotor inside this cage, its North and South poles will be pulled towards the South and North poles of the rotating field. Assuming for a moment that the magnetis field rotation is paused, we can see the effect of the pull on the magnet at different angular position relative to the rotating field.

	
### FOC (Field Oriented Control)
...TODO...  
(https://www.roboteq.com/technology/field-oriented-control)





### Motor Drive
To drive our motor we are using a [TMC4671](https://www.trinamic.com/products/integrated-circuits/details/tmc4671-es/) controller from [Trinamic](#sponsors)

We use this drive specifically because it has hardware FOC (Field Oriented Control). The TMC4671 [datasheet](https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC4671_datasheet_v1.06.pdf)  explains very well what FOC is exactly, so please check it out.

	
### Motor Initialization
...TODO...

__So why make our own?__
Simply, just because we can! And its awesome to learn about new stuff.

We do wish to mention [Vulcaman's](https://www.instructables.com/id/DIY-IRONLESS-LINEAR-SERVO-MOTOR/) motor build. This version is based on a simple L6234 motor controller IC and implements a basic sinusoidal commutation.

		
## Sponsors
We would like to thank our Trinamic for providing us with a TMC4671 evaluation kit.
![Trinamic](/images/TRINAMIC_LOGO_STANDARD_RGB.png)