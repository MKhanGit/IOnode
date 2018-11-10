# IOnode Firmware
The IOnode v1.1 PCB and firmware are designed based on the Atmega328p microcontroller. The firmware sets up a serial line on the chip's hardware Tx/Rx pins, which can be conntected directly to a TTL convertor or a serial Bluetooth module.

## Serial Commands
Below a table of the Serial Commands implemented in this firmware. Once the board is programmed, any adequate serial adapter can pass and receive commands from the device.

Note, commands that target a specific output (0 to n) must be followed by an index
*Example:* To toggle output 2, send **T2**


| Command 		 | Bytes to Send | Response                 |
| ---------------------- | ------------- | -------- 	            |
|Toggle output <    n    >	 | T <    n    >		 | OK	    		    |
|Force <    n    > High    	 | O<    n    >		 | OK	    		    |
|Force <    n    > Low   	 | X<    n    >		 | OK	    		    |
|Check <    n    > State 	 | I<    n    >	 | <    state, 0 or 1    >	    |
|Ping Device (test)	 | P             | pong    		    |


