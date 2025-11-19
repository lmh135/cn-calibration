# C++ API

## Constructor

```
// Using namespace could be so much convenient 
using CM = octopus::calibration_manager;
```

#### Construct in octopus online environment

```
auto cm = CM::FromEnvironment();
``` 

* **Parameter**

* **Return**: a share_ptr of CalibrationManager object (current online vehicle in octopus)
#### Construct from vehicle name

```
const std::string vehicle = "Foton-3052";
const std::string system = "";
auto cm = CM::FromVehicle(vehicle, system);
``` 

* **Parameter**
  * **vehicle**: vehicle name.
  * **system**: system name (one of ["", "pri", "sec"]).

* **Return**: a share_ptr of CalibrationManager object

#### Construct from vehicle path

``` 
const std::string vehicle_path = "/root/.tspkg_cellar/vehicle_config_foton-3053@1.1.176/res";
const std::string system = "sec";
auto cm = CM::FromVehicle(vehicle_path, system);
``` 

* **Parameter**
  * **vehicle_path**: vehicle config path.
  * **system**: system name (one of ["", "pri", "sec"]).

* **Return**: a share_ptr of CalibrationManager object

#### Construct from dataset name 

```
const std::string bag_name("2021-12-27-18-12-43-668874");
const std::string system = "";
auto cm = CM::FromDataset(bag_name, system);
``` 

* **Parameter**
  * **bag_name**: dataset bag name.
  * **system**: system name (one of ["", "pri", "sec"]).

* **Return**: a share_ptr of CalibrationManager object

#### Construct from dataset path 

```
const std::string bag_path("/mnt/weka/datasets/v2/2021-12-16-16-25-33-674034");
const std::string system("sec");
auto cm = CM::FromDataset(bag_path, system);
``` 

* **Parameter**
  * **bag_path**: dataset bag path.
  * **system**: system name (one of ["", "pri", "sec"]).

* **Return**: a share_ptr of CalibrationManager object


## Attributes

#### ```sensor_graph```

```
unordered_map<string, unordered_map<string, Eigen::MatrixXd>>
```

The matrix means from source sensor to destination sensor

* **Example**: 
  ```
  // get extrinsic from camera-4 to imu-0
  Eigen::MatrixXd tf_imu0_cam4 = cm.sensor_graph["camera-4"]["imu-0"]  
  std::cout << tf_imu0_cam4 << std::endl;
  ```

## Methods
#### ```GetCameras```

Get a dictionary of camera object 

* **Param**: None

* **Return**: unordered_map<int, Camera>

* **Example**:
    ```
    auto cams_dict = cm.GetCameras();
    const auto& cam1 = cams_dict[1];
    std::cout << cam1.img_shape << std::endl;
    std::cout << cam1.distortion << std::endl;
    std::cout << cam1.intrinsic << std::endl;
    ```
  
##### Camera object
```
Camera {
public:
  Eigen::Vector2d img_shape;
  Eigen::VectorXd distortion;
  Eigen::Matrix3d intrinsic;
}
```


#### ```GetLidars```

Get a dictionary of LiDAR object 

* **Param**: None

* **Return**: unordered_map<int, LiDAR>

* **Example**:
    ```
    auto lidars_dict = cm.GetLidars()
    const auto& lidar1 = lidars_dict[1];
    std::cout << lidar1.intrinsic_file_path << std::endl;
    ```
  
##### Camera object
```
LiDAR {
public:
  std::string intinsic_file_path;
}
```

#### ```GetRadars```

Get a dictionary of Radar object 

* **Param**: None

* **Return**: unordered_map<int, Radar>

* **Example**:
    ```
    auto radars_dict = cm.GetRadars()
    const auto& radar1 = radars_dict[1];
    // nothing to print for radar1 since it doesn't have intrinsic
    ```
  
##### Radar object
```
Radar {
public:
  // empty
}
```

#### ```GetImus```

Get a dictionary of IMU object 

* **Param**: None

* **Return**: unordered_map<int, IMU>

* **Example**:
    ```
    auto imus_dict = cm.GetImus()
    const auto& imu0 = imus_dict[0];
    std::cout << imu0.ground_height << std::endl;
    ```
  
##### IMU object
```
IMU {
public:
  float ground_height;
}
```

#### ```GetWheelSpeeds```

Get a dictionary of WheelSpeed object 

* **Param**: None

* **return**: unordered_map<int, WheelSpeed>

* **Example**:
    ```
    auto ws_dict = cm.GetWheelSpeeds()
    const auto& ws1 = ws_dict[1];
    std::cout << ws1.intrinsic << std::endl;
    ```
  
##### WheelSpeed object
```
WheelSpeed {
public:
  Eigen::VectorXd intrinsic;
}
```
