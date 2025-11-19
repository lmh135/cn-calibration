# Python API

## Constructor

## Method with calibration_manager lib

```__init__()``` 
* **Return**: a CalibrationManager object

* **Noted** This constructor can be only used for online use (with octopus) 



```__init__(dataset=bag_name, system=system_name)``` 

* **Parameter**
dataset is the bag name stored in the TuSimple Dataset. 
system must be one of ('', 'pri', 'sec'), system_name is not necessary, dafault is 'pri'.

* **Return**: a CalibrationManager object

* **Noted** This constructor can be either online or offline


```__init__(vehicle=vehicle, system=system_name)``` 

* **Parameter**
vehicle name must be consistent with Octopus. 

system must be one of ('', 'pri', 'sec'), system_name is not necessary, dafault is 'pri'.

* **Return**: a CalibrationManager object

* **Noted** This constructor can be either online or offline

##### Example
```
from py_calibration_manager import CalibrationManager, from_vehicle, from_dataset

calib_manager = CalibrationManager()
```

or 

```
calib_manager = CalibrationManager(dataset=bag_name, system=system_name)
```

or 


```
calib_manager = CalibrationManager(vehicle=vehicle, system=system_name)
```

**Warning**

one is NOT allowed to input both dataset and vehicle 

```
CalibrationManager(dataset=bag_name, vehicle=vehicle, system=system_name)
```

an Error will be raised if initializing as above



## Methods

#### ```get_cameras()```

Get all cameras' calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by camera_id. 
The inner dictionary contains all information of a camera 

* **Example**:
    ```
    cam_calib = calib_manager.get_cameras()
    cam1 = cam_calib[1]
    ```


#### ```get_lidar()```

Get all LiDARs' calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by lidar_id. 
The inner dictionary contains all information of the LiDAR 

* **Example**:
    ```
    lidar_calib = calib_manager.get_lidar()
    lidar_1 = lidar_calib[1]
    ```


#### ```get_imus()```

Get all IMUs' calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by imu_id. 
The inner dictionary contains all information of the imu 

* **Example**:
    ```
    imu_calib = calib_manager.get_imus()
    imu_0 = imu_calib[0]
    ```

#### ```sensor_graph```

read-only Property

Get all pair-wise sensor extrinsic calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by src sensor and dest sensor

* **Example**:
    ```
    rt_imu2cam1 = calib_manager.sensor_graph['imu-0']['camera-1']
    rt_cat12imu = calib_manager.sensor_graph['camera-1']['imu-0']
    ```


## Method with py_calibration_manager lib

py_calibration_manager is pybind lib with c++ API

```from_environment()``` 
* **Return**: a CalibrationManager object

* **Noted** This constructor can be only used for online use (with octopus) 



```from_dataset(bag_name, system_name)``` 

* **Parameter**
bag_name is the bag name stored in the TuSimple Dataset. 
system_name must be one of ('', 'pri', 'sec'). 

* **Return**: a CalibrationManager object

* **Noted** This constructor can be either online or offline


```from_vehicle(vehicle_name, system_name)``` 

* **Parameter**
vehicle_name must be consistent with Octopus. 

system_name must be one of ('', 'pri', 'sec').

* **Return**: a CalibrationManager object

* **Noted** This constructor can be either online or offline

##### Example
```
from py_calibration_manager import from_environment, from_vehicle, from_dataset

calib_manager = from_environment()
```

or 

```
calib_manager = from_dataset(bag_name, system_name)
```

or 


```
calib_manager = from_vehicle(vehicle_name, system_name)
```




## Methods

#### ```get_cameras()```

Get all cameras' calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by camera_id. 
The inner dictionary contains all information of a camera 

* **Example**:
    ```
    cam_calib = calib_manager.get_cameras()
    cam1 = cam_calib[1]
    intrinsic = cam1.intrinsic
    distortion = cam1.distortion
    img_shape = cam1.img_shape
    ```


#### ```get_lidar()```

Get all LiDARs' calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by lidar_id. 
The inner dictionary contains all information of the LiDAR 

* **Example**:
    ```
    lidar_calib = calib_manager.get_lidar()
    lidar_1 = lidar_calib[1]
    ```


#### ```get_imus()```

Get all IMUs' calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by imu_id. 
The inner dictionary contains all information of the imu 

* **Example**:
    ```
    imu_calib = calib_manager.get_imus()
    imu_0 = imu_calib[0]
    ```

#### ```sensor_graph```

read-only Property

Get all pair-wise sensor extrinsic calibration

* **Parameter**: None

* **Return**: a dictionary of a dictionary keyed by src sensor and dest sensor

* **Example**:
    ```
    rt_imu2cam1 = calib_manager.sensor_graph['imu-0']['camera-1']
    rt_cat12imu = calib_manager.sensor_graph['camera-1']['imu-0']
    ```
