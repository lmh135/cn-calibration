# Objective-oriented Design


## CalibrationManager
the manager is designed to read and parse all calibration files and construct sensor graph


## Sensor
abstract object 

### Camera
inherit from Sensor, contains Camera specific parameters and functions

### LiDAR
inherit from Sensor, contains LiDAR specific parameters and functions


### IMU 
inherit from Sensor, contains IMU specific parameters and functions

