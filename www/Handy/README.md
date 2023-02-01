# HandyMan
A Web Interface to control and debug Steppy Robot for the "Coupe de France de Robotique 2023" tournament, or briefly CDR-23

## Features
- Control all three Steppers simultaneously
- Control a stepper individually
- Change Acceleration, Speed, and Max Speed
- Easy to use and intuitive user interface
- Written in JS/TS using Svelte framework
- Plugin System which makes it easy to add features such as charts...etc
- Fully compatible to be exported as an Android/IOS app via Capacitor
## To be Added in Future:
- LiDAR integration (Charts, Signal Visualization, ...etc)
- Path Mapper
### Endpoints used to interface with ESP32:
Set Motor steps for all of them:
```
http://host:port/steps/{motor_1}/{motor_2}/{motor_3}
```
Set Motors Speed and Acceleration for all of them
```
http://host:port/flow/{speed}/{maxspeed}/{acceleration}
```
