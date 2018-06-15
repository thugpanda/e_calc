# e_calc

*e_calc* is a small CLI-application for calculating basic laws of electrical engineering.

It is able to calculate

* The currents of a schmitt trigger with given resistor values
* All three variants of Ohms law (impedance, current, resistance)
* The value of a parallel resistor with *n* individual resistor values

It is planned to extend the features as required.

## How To

```
-a, -A, -I, -i		Calculate the Impedance in Ampere

Expects 2 values:	Current in Volts, Resistance in Ohms
```

```
-C, -c, -V, -v		Calculate the Current in Volts

Expects 2 values:	Impedance in Amperes, Resistance in Ohms
```

```
-R, -r			Calculate the Resistance in Ohms

Expects 2 values:	Currents in Volts, Impedance in Amperes
```

```
-Rp, -rp		Calculate the Resistance of multiple parallel Resistors

Expects n values:	Resistance 1 in Ohms, Resistance 2 in Ohms, ...
```

```
-S, -s			Calculate the Voltages of a Schmitt Trigger with Resistor values

Expects 4 values:	VRef
			Ra (between Collector of T1 and Base of T2)
			Rb (between Ra and Common/Ground)
			R1 (between supply and Collectors of Transistors)
```

```
-tmv, -TMV		Calculate the frequency of oscillation of an Astable Transistor Multivibrator

Expects 2 [or 4] values:
				Resistance 1
				Capacitance 1
				[Resistance 2]
				[Capacitance 2]

Only four if oscillation is asynchronous (aka R1!=R2 and/or C1!=C2)
```

Every feature has got a Question-Answer based input option as well.

