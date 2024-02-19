# Project-3
Team members: Becky Perkins and Grant Bouvin

This code creates a comprehensie windshield wiper subsystem. The system includes four operational modes: High-speed (HIGH), Low-speed (LOW), Interval (INT), and Off (OFF), each with distinct functionalities. The subsystem integrates a user display showing the selected wiper mode and a delay time selector for INT mode. Wipers in HIGH and LOW modes run at 8 and 12 rotations per minute, while the INT mode delays a set number of seconds between cycles. The project includes a driver seat occupancy sensor, ignition push button, blue indicator LED, wiper mode selector, intermittent delay time selector, windshield wiper motor, and a user display. The control system is designed to start and stop the engine based on specific conditions. Wiper functionalities are dependent on the running engine, ensuring proper operation and display feedback. The project uses positional servo motors to simulate the windshield wiper motors, and an LCD acts as the display. The wipers were throughly tested to ensure long term correct behavior and proper timing.

| Ignition Subsystem |  |
|---|---|
| Specification | Test Result |
| Start the engine (i.e., light the blue LED) while the driver’s seat is occupied and when the ignition button is pushed and then released. | Pass |
| Keep the engine running even if the driver should exit the vehicle. | Pass |
| When the engine is running, stop the engine when the ignition button is pushed (i.e., before the button is released). | Pass |
| **Wiper Subsystem** |  |
| Wiper mode dial should correct set wiper mode | Pass |
| Time delay dial should correctly set time delay | Pass |
| Display should show the values of both dials | Pass |
| The wipers do not run if the engine is not running | Pass |
| If wiper is set to off or engine is turned off then: If the wiper is running it should complete its cycle and then turn off.  If the wiper is paused in intermediate mode then wiper should not run.  | Pass |
