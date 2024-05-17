const char javascript[] = R"====(

var JoyDrive;
var JoyDriveX = 0;
var JoyDriveY = 0;

function sendBodyUpdate() {
    const data = {
        body: {
            arms: {
                left: document.getElementById("bodyArmLeft").checked,
                right: document.getElementById("bodyArmRight").checked
            },
            utility: {
                arm: document.getElementById("utilityArm").checked,
                gripper: document.getElementById("utilityArmGripper").checked
            }
        }
    };

    sendData(data);
}

function sendDomeUpdate() {

    if (document.getElementById("domeRightArmExtend").checked == false) {
        document.getElementById("domeRightArmRotate").value = 1000;
    }

    if (document.getElementById("domeLeftArmExtend").checked == false) {
        document.getElementById("domeLeftArmRotate").value = 2000;
    }

    const data = {
        dome: {
            shake: document.getElementById("domeShake").checked,
            rotate: document.getElementById("domeRotate").value,
            arms: {
                left: {
                    extend: document.getElementById("domeLeftArmExtend").checked ? 1200 : 1000,
                    rotate: 3000 - document.getElementById("domeLeftArmRotate").value
                },
                right: {
                    extend: document.getElementById("domeRightArmExtend").checked ? 1200 : 1000,
                    rotate: document.getElementById("domeRightArmRotate").value
                }
            },
            periscope: {
                lift: document.getElementById("periscopeLift").value,
                rotate: document.getElementById("periscopeRotate").value
            }
        }
    };

    sendData(data);
}

function getServerData() {
    const data = {};
    
    postData("/api/get.json", data).then(json => {
        console.log("Result from Server: ");
        callbackActionOnServerGet(json);
    });
}

async function postData(url = "", data = {}) {
    // Default options are marked with *
    const response = await fetch(url, {
        method: "POST",
        mode: "no-cors", // no-cors, *cors, same-origin
        cache: "no-cache",
        headers: {
            "Content-Type": "application/json"
        },
        referrerPolicy: "no-referrer", // no-referrer, *no-referrer-when-downgrade, origin, origin-when-cross-origin, same-origin, strict-origin, strict-origin-when-cross-origin, unsafe-url
        body: JSON.stringify(data), // body data type must match "Content-Type" header
    });
    return response.json();
}

function sendData(data) {
    console.log(data);

    postData("/api/post.json", data).then(json => {
        console.log("Result from Server: ");
        callbackActionOnServerPost(json);
    });
}

function callbackActionOnServerPost(json) {
    console.log(json);
}

function callbackActionOnServerGet(json) {
    console.log(json);

    document.getElementById("domeShake").checked = json.dome.shake;
    document.getElementById("domeRotate").value = json.dome.rotate;

    document.getElementById("domeLeftArmExtend").checked = json.dome.arms.left.extend >= 1010;
    document.getElementById("domeRightArmExtend").checked = json.dome.arms.right.extend >= 1010;

    document.getElementById("domeLeftArmRotate").value = 3000 - json.dome.arms.left.rotate;
    document.getElementById("domeRightArmRotate").value = json.dome.arms.right.rotate;

    document.getElementById("bodyArmLeft").checked = json.body.arms.left;
    document.getElementById("bodyArmRight").checked= json.body.arms.right;

    document.getElementById("utilityArm").checked = json.body.utility.arm;
    document.getElementById("utilityArmGripper").checked = json.body.utility.gripper;

    document.getElementById("periscopeLift").value = json.dome.periscope.lift;
    document.getElementById("periscopeRotate").value = json.dome.periscope.rotate;
}

function initBindings() {
    document.getElementById('show_menu').addEventListener('click', show_menu);
    document.getElementById('hide_menu').addEventListener('click', hide_menu);
}

function show_menu() {
    let div = document.getElementById('menu');
    div.style.visibility = 'visible';
}
function hide_menu() {
    let div = document.getElementById('menu');
    div.style.visibility = 'hidden';
}

function systemInit() {
    initBindings();

    const intervalID = setInterval(getServerData, 200);
}

)====";
