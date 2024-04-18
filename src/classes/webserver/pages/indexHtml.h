const char indexHtml[] = R"====(
<a href="/settings.html">Settings</a>

<h5>Drive</h5>
<div id="joyDrive" class="joystick"></div>
Pos X:<input id="joyDrivePosX" type="text" /> 
Pos Y:<input id="joyDrivePosY" type="text" />
Rel X :<input id="joyDriveRelX" type="text" /> 
Rel Y :<input id="joyDriveRelY" type="text" />

<h4>Body</h4>
<h5>Arms</h5>
<input type="checkbox" id="bodyArmLeft" name="bodyArmLeft" value="1" onchange="sendBodyUpdate()">
<label for="bodyArmLeft">Left</label>
<input type="checkbox" id="bodyArmRight" name="bodyArmRight" value="1" onchange="sendBodyUpdate()">
<label for="bodyArmRight">Right</label>
<br />
<input type="checkbox" id="utilityArm" name="utilityArm" value="1" onchange="sendBodyUpdate()">
<label for="utilityArm">Utility Arm</label>
<input type="checkbox" id="utilityArmGripper" name="utilityArmGripper" value="1" onchange="sendBodyUpdate()">
<label for="utilityArmGripper">Utility Arm Gripper</label>

<h4>Dome</h4>
<h5>Rotate</h5>
<input id="domeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendDomeUpdate()">
<h5>Left</h5>
<input id="domeLeftArmExtend" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendDomeUpdate()">
<label for="domeLeftArmExtend">Extend Left</label>
<input id="domeLeftArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendDomeUpdate()">
<label for="domeLeftArmRotate">Rotate Left</label>

<h5>Right</h5>
<input id="domeRightArmExtend" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendDomeUpdate()">
<label for="domeRightArmExtend">Extend Right</label>
<input id="domeRightArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendDomeUpdate()">
<label for="domeRightArmRotate">Rotate Right</label>

<h4>Periscope</h4>
<input id="periscopeLift" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendDomeUpdate()">
<label for="periscopeLift">Lift</label>
<input id="periscopeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendDomeUpdate()">
<label for="periscopeRotate">Rotate</label>

<script>
    window.onload = function () {
        console.log('Dokument geladen');
        systemInit();
    }
</script>

)====";
