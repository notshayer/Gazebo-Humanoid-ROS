import os
import numpy as np
import time
from pyautogui import hotkey, write

waypointcmd = "rosservice call /gazebo/set_model_state '{model_state: { model_name: bruno, pose: { position: { x:, y: 0 ,z: 0 }, orientation: {x: 0, y: 0, z: 0, w: 0.870604813099 } } , reference_frame: world } }'"
xi = waypointcmd.find("x:") +2
print(xi)

xc = np.linspace(0, 10, 100)

for x in xc:
    newcmd = waypointcmd[0:xi]+" "+str(x)+waypointcmd[xi:]
    # newcmd+=" "+ str(x)
    # newcmd+=waypointcmd[xi:]
    # aa=newcmd.split()
    # print(newcmd)
    os.system(newcmd)