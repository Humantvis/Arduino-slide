# Arduino-slide
Small Arduino example on sensors in a water park slide.

This is a small prototype for the water park. It simulates a system with photosensors, that help people safely slide down the slide.

It allows only one person in at a time. The red light means that the slide is ocupied and you can not enter, the green light means the slide is clear. If there is an error, for example if two people entered the slide at the same time, the system enters "error state"(yellow and red light together) that needs to be turned off by pressing the reset button.

Instalation diagram files show how the system would be installed in a water park.

Slide.brd is the schema dezigned for tinkercad.

SlideArduino.png is a screenshot of the arduino wiring.

slide.ino has the code of the system.

demo video:
https://drive.google.com/file/d/1N-9g1Y5H9_kzPKENOfmKG7FFkG8XR3ic/view?usp=drive_link
