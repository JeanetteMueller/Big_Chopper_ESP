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
    const data = {
        dome: {
            rotate: document.getElementById("domeRotate").value,
            arms: {
                left: {
                    extend: document.getElementById("domeLeftArmExtend").value,
                    rotate: document.getElementById("domeLeftArmRotate").value
                },
                right: {
                    extend: document.getElementById("domeRightArmExtend").value,
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
        callbackActionOnServer(json);
    });
}

function callbackActionOnServer(json) {
    console.log(json);
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
}

)====";
