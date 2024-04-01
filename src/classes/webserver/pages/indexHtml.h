const String indexHtml = R"====(

Index Page UNDER CONSTRUCTION

<br />
<a href="/settings.html">Settings</a>

<div id="joyDiv" style="width:200px;height:200px;margin:50px"></div>
Pos X:<input id="joy1PosX" type="text" /><br />
Pos Y:<input id="joy1PosY" type="text" /><br />
Rel X :<input id="joy1RelX" type="text" /></br>
Rel Y :<input id="joy1RelY" type="text" />

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

    sendFormularUpdate(stickData);
});

function sendFormularUpdate(stickData) {
    console.log("sendFormularUpdate");

    const data = { 
        joy1: {
            x: stickData.x,
            y: stickData.y
        }
    };

    postData("/api/post.json", data).then((result) => {
        console.log(result); // JSON data parsed by `result.json()` call
    });
}

</script>

)====";
