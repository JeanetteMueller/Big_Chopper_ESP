const String indexHtml = R"====(
<a href="/settings.html">Settings</a>

<h5>Drive</h5>
<div id="joyDiv" class="joystick"></div>
Pos X:<input id="joy1PosX" type="text" /> 
Pos Y:<input id="joy1PosY" type="text" />
Rel X :<input id="joy1RelX" type="text" /> 
Rel Y :<input id="joy1RelY" type="text" />

<h4>Body</h4>
<h5>Arms</h5>
<input type="checkbox" id="bodyArmLeft" name="bodyArmLeft" value="1" onchange="sendFormularUpdate()">
<label for="bodyArmLeft">Left</label>
<input type="checkbox" id="bodyArmRight" name="bodyArmRight" value="1" onchange="sendFormularUpdate()">
<label for="bodyArmRight">Right</label>

<h4>Dome</h4>
<h5>Rotate</h5>
<input id="domeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendFormularUpdate()">
<h5>Left</h5>
<input id="domeLeftArmExtend" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()">
<label for="domeLeftArmExtend">Extend Left</label>
<input id="domeLeftArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()">
<label for="domeLeftArmRotate">Rotate Left</label>

<h5>Right</h5>
<input id="domeRightArmExtend" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()">
<label for="domeRightArmExtend">Extend Right</label>
<input id="domeRightArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()">
<label for="domeRightArmRotate">Rotate Right</label>

<h4>Periscope</h4>
<input id="periscopeLift" type="range" min="1000" max="2000" value="1000" class="slider" onchange="sendFormularUpdate()">
<label for="periscopeLift">Lift</label>
<input id="periscopeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendFormularUpdate()">
<label for="periscopeRotate">Rotate</label>

<script>
    window.onload = function () {
        console.log('Dokument geladen');
        systemInit();
    }
</script>

)====";
