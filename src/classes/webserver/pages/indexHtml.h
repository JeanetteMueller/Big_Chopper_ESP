const char indexHtml[] = R"====(

<div class="statusbar">
        <button id="show_menu">Menu</button>
        <button id="show_drive">Drive</button>
    </div>
    <!-- Overlays start -->
    <div id="menu">
        <div class="statusbar">
            <button id="hide_menu">Close X</button>
        </div>

        <a href="/settings.html">Settings</a>
    </div>
    <div id="drive">
        <div class="statusbar">
            <button id="hide_drive">Close X</button>
        </div>
        <h4>Drive</h4>
        <div id="joyDrive" class="joystick"></div>
    </div>
    <!-- Overlays end -->

    <div class="contentMax">
        <h4>Rotate Dome</h4>
        <input id="domeRotate" type="range" min="1000" max="2000" value="1500" class="slider"
            onchange="sendDomeUpdate()">
        <hr>
        <h4>Utility Arms</h4>
        <div class="contentHalfBox">
            <input type="checkbox" id="utilityArm" name="utilityArm" value="1" onchange="sendBodyUpdate()">
            <label for="utilityArm" class="interaction">Utility Arm</label>
        </div>

        <div class="contentHalfBox">
            <input type="checkbox" id="utilityArmGripper" name="utilityArmGripper" value="1"
                onchange="sendBodyUpdate()">
            <label for="utilityArmGripper" class="interaction">Utility Arm Gripper</label>
        </div>
        <hr>
        <h4>Periscope</h4>
        <div class="contentHalfBox">
            <label for="periscopeLift" class="centered">Lift</label>
            <input id="periscopeLift" type="range" min="1000" max="2000" value="1000" class="slider"
                onchange="sendDomeUpdate()">
        </div>
        <div class="contentHalfBox">
            <label for="periscopeRotate" class="centered">Rotate</label>
            <input id="periscopeRotate" type="range" min="1000" max="2000" value="1500" class="slider"
                onchange="sendDomeUpdate()">
        </div>
    </div>
    <hr>
    <div class="content contentLeft">
        <h4>Left</h4>

        <div class="contentHalfBox">
            <label for="domeLeftArmExtend" class="centered">Extend</label>
            <input id="domeLeftArmExtend" type="range" min="1000" max="2000" value="2000" class="slider"
                onchange="sendDomeUpdate()">
        </div>
        <div class="contentHalfBox">
            <label for="domeLeftArmRotate" class="centered">Rotate</label>
            <input id="domeLeftArmRotate" type="range" min="1000" max="2000" value="2000" class="slider"
                onchange="sendDomeUpdate()">
        </div>


        <input type="checkbox" id="bodyArmLeft" name="bodyArmLeft" value="1" onchange="sendBodyUpdate()">
        <label for="bodyArmLeft" class="interaction">Dataport</label>



    </div>
    <div class="content contentRight">
        <h4>Right</h4>

        <div class="contentHalfBox">
            <label for="domeRightArmRotate" class="centered">Rotate</label>
            <input id="domeRightArmRotate" type="range" min="1000" max="2000" value="1000" class="slider"
                onchange="sendDomeUpdate()">
        </div>
        <div class="contentHalfBox">
            <label for="domeRightArmExtend" class="centered">Extend</label>
            <input id="domeRightArmExtend" type="range" min="1000" max="2000" value="1000" class="slider"
                onchange="sendDomeUpdate()">
        </div>



        <input type="checkbox" id="bodyArmRight" name="bodyArmRight" value="1" onchange="sendBodyUpdate()">
        <label for="bodyArmRight" class="interaction">Saw</label>
        <br />


    </div>



    <script>
        window.onload = function () {
            console.log('Dokument geladen');
            systemInit();
        }
    </script>

)====";
