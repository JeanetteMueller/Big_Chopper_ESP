const String indexHtml = R"====(

Index Page UNDER CONSTRUCTION

<br />
<a href="/settings.html">Settings</a>

<div id="joyDiv" style="width:200px;height:200px;margin:10px"></div>
Pos X:<input id="joy1PosX" type="text" /> 
Pos Y:<input id="joy1PosY" type="text" /><br />
Rel X :<input id="joy1RelX" type="text" /> 
Rel Y :<input id="joy1RelY" type="text" /><br />
<br />
Rotate<br />
<input id="domeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onchange="sendFormularUpdate()"><br />

<br />
Body Arms<br />
<input type="checkbox" id="bodyArmLeft" name="bodyArmLeft" value="1" onchange="sendFormularUpdate()">
<label for="bodyArmLeft">Left</label>
<input type="checkbox" id="bodyArmRight" name="bodyArmRight" value="1" onchange="sendFormularUpdate()">
<label for="bodyArmRight">Right</label><br>

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

function sendFormularUpdate() {
    console.log("sendFormularUpdate");

    const data = { 
        joy1: {
            x: joy1RelX.value,
            y: joy1RelY.value
        },
        body: {
            arms: {
                left: document.getElementById("bodyArmLeft").checked,
                right: document.getElementById("bodyArmRight").checked
            }
            
        },
        dome: {
            rotate: document.getElementById("domeRotate").value
        }
    };

    console.log(data);

    postData("/api/post.json", data).then((result) => {
        console.log(result); // JSON data parsed by `result.json()` call
    });
}

</script>

)====";
