# Calibration

<p align="center">
<img src="https://avatars2.githubusercontent.com/u/14118363?s=200&v=4"/>
</p>
<p align="center">TuSimple Calibration Manager</p>
<p align=center>
</p>


[**Release** branch documents](http://nas-web.sd.tusimple.ai/scratch/LPS/Calibration-Manager/site/)



**Calibration files are managed by Octopus API**

All vehicle related configuration/parameters are all stored in [octopus-vehicle-config](https://github.com/TuSimple/octopus-vehicle-config) (testing vehicles), or Vehicle Manager (production vehicles).

Calibration files are included as well, and are managed by Octopus API. 

All vehicle related configuration/parameters including calibration files are saved into bag everytime, so when replay, Octopus API will acquire those files and provide to each module. 

Calibration files are no longer stored in `Data` folder, `Data` folder only keeps legacy calibration files for backward compatibility.  
