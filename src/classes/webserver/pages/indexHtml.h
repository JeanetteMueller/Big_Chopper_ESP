const String indexHtml = R"====(
<a href="/settings.html">Settings</a>

<h5>Drive</h5>

<div id="joyDiv" style="width:200px;height:200px;margin:10px"></div>
Pos X:<input id="joy1PosX" type="text" /> 
Pos Y:<input id="joy1PosY" type="text" /><br />
Rel X :<input id="joy1RelX" type="text" /> 
Rel Y :<input id="joy1RelY" type="text" />

<h5>Dome Rotate</h5>
<input id="domeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendFormularUpdate()"><br />

<h5>Body Arms</h5>
<input type="checkbox" id="bodyArmLeft" name="bodyArmLeft" value="1" onchange="sendFormularUpdate()">
<label for="bodyArmLeft">Left</label>
<input type="checkbox" id="bodyArmRight" name="bodyArmRight" value="1" onchange="sendFormularUpdate()">
<label for="bodyArmRight">Right</label>

<h5>Dome Arms</h5>
<input id="domeLeftArmExtend" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()"><br />
<label for="domeLeftArmExtend">Extend Left</label>
<input id="domeRightArmExtend" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()"><br />
<label for="domeRightArmExtend">Extend Right</label>
<br />
<input id="domeLeftArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()"><br />
<label for="domeLeftArmRotate">Rotate Left</label>
<input id="domeRightArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()"><br />
<label for="domeRightArmRotate">Rotate Right</label>

<h5>Periscope</h5>
<input id="periscopeLift" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()"><br />
<label for="periscopeLift">Lift</label>
<input id="periscopeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendFormularUpdate()"><br />
<label for="periscopeRotate">Rotate</label>


<script type="text/javascript">

var joy1PosX = document.getElementById("joy1PosX");
var joy1PosY = document.getElementById("joy1PosY");
var joy1RelX = document.getElementById("joy1RelX");
var joy1RelY = document.getElementById("joy1RelY");

var Joy1 = new JoyStick('joyDiv', {
    "autoReturnToCenter": true
}, function(stickData) {
    joy1PosX.value = stickData.xPosition;
    joy1PosY.value = stickData.yPosition;
    joy1RelX.value = stickData.x;
    joy1RelY.value = stickData.y;

    sendFormularUpdate();
});

</script>

)====";
