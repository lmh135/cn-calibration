# Calibration

This repo contains all calibration data and source code of CalibrationManager


## Installation

Select one of the following two methods

### With TSPKG

with TSPKG
```
tsp install calibration_manager
```

### Without TSPKG

Python Package

```
sh init.sh
```

 
C++ Package

* with Octopus
    * it will build and install when building Octopus

* individually
    * create a ROS workspace and put this package into "**src**" folder
    * build with ROS command 
```
calib_mngt_ws
    src
        calibration 
```

```
catkin build
```



## Usage
Python Package


* see details in calibration/test/script/test.py
```
    # online mode: if and only if used online with octopus
    calib_manager = CalibrationManager()
    
    # offline mode: 
    calib_manager = CalibrationManager(dataset=bag)
    
    cam_calibs = calib_manager.get_cameras()
    cam_calibs[1]['intrinsic']  # get intrinsic of "camera-1" 
    cam_calibs[1].['extrinsic']['imu-0']  # get extrinsic from "camera-1" to "imu-0"
```

C++ Package
* see details in calibration/test/script/example.cpp
```
    string vehicle = "Octopus-B4";
    string bag_name = "2018-11-01-14-13-58";
    CalibrationManager cm = CalibrationManager(vehicle, bag_name);
    cm.get_camera_by_name("camera-1")->intrinsic;  // get intrinsic of "camera-1" 
    cm.sensor_graph["camera-1"]["imu-0"];  // get extrinsic from "camera-1" to "imu-0"
```

## Calibration File Storage Format

The top level folder **/Data** contains all current and historical calibration files


### Folder Hierarchy and File Format

```
Calibration
    vehicle
        date
            intrinsic
                camera-1.yaml
                camera-2.yaml
            extrinsic
                camera-1_to_imu.yaml
                camera-2_to_lidar-1.yaml
            config.yaml
```

#### Vehicle folder

Each **vehicle** is the top level of all its sensor calibrations. 

#### Date folder

For each vehicle, all calibrations are grouped by a **unique date**. 
There must be some changes between two distinct date.

#### Intrinsic and extrinsic folder

The **intrinsic** folder contains all sensors' intrinsic calibrations, 
while the **extrinsic** folder contains all valid **pairwise** sensors' extrinsic calibrations.  


#### config.yaml
This file specifies each sensor's setting (both intrinsic and extrinsic).

If two sensors having multiple possible calibrations, this file will determine which one to use. 
For example, the pairwise extrinsic calibration between camera-1 and imu have two available calibration path:
1. camera-1_to_imu
2. camera-1_to_lidar-1, and followed by lidar-1_to_imu  
this file will determine which path to go for.
 


### Name Convention
1. all sensors must be in lower-case, eg 'lidar'

2. ID is followed by the sensor name with '-', eg 'camera-1' 

3. the name of intrinsic calibration file is defined by **sensor-id.ext**, eg 'camera-1.yaml'

4. the name of extrinsic calibration file is defined by **sensorY-id_to_sensorX_id**, eg 'camera-1_to_imu.yaml'

#### Exception
1. if not specified, imu with **id = 0** is the primary imu for vehicle navigation, eg 'imu-0'


