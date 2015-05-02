## Zero O2 Simulator

An O2 or lambda simulator is used to send a simulated oxygen/lambda sensor signal to an engine ECU running in closed loop mode. O2 sensors generate voltages between 0.9V (rich) and 0.1V (lean).  A properly running simulator will generate an oscillation of 1-2Hz at 0.6V to 0.3V (though check your specific application).

This uses an ATTiny85 as the signal generator (using DDS, see: http://cho-yaba.punyu.jp/?p=1663).  Where most O2 simulators in the past used a 555 timer the ATTiny85 gives the advantage of being fully programmable.

![Alt text](./doc/schematic.png?raw=true "Schematic")
![Alt text](./doc/board.png?raw=true "board")
![Alt text](./doc/signal.png?raw=true "Signal")
![Alt text](./doc/finished-board.jpg?raw=true "Finished")

## Status

May 2 2015 - This is still early proof of concept version.  The hardware design will work and the current software emits a sine wave signal.  The signal will need to be tuned for your specific application and will require modification.  

## TODO

* Modify circuit to accept external rich <--> lean control via a digital pot. (currently need to reprogram the microcontroller).
* Create a surface mount component version.

## License

BSD License (free to use it, copy it, etc)

## References

  ATTiny signal generation using DDS: http://cho-yaba.punyu.jp/?p=1663
  555 O2 Simulator Project: http://www.bobblick.com/techref/projects/o2sensor/o2sim/o2sim.html

