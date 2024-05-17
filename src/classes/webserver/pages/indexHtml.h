const char indexHtml[] = R"====(

<div class="statusbar">
        <button id="show_menu">Menu</button>
    </div>
    <!-- Overlays start -->
    <div id="menu">
        <div class="statusbar">
            <button id="hide_menu">Close X</button>
        </div>

        <a href="/settings.html">Settings</a>
    </div>

    <!-- Overlays end -->

    <div class="row">
        <div class="c75">
            <h4>Rotate Dome</h4>
            <input id="domeRotate" type="range" min="1000" max="2000" value="1500" class="slider" onInput="sendDomeUpdate()">
        </div>
        <div class="c25">
            <input type="checkbox" id="domeShake" name="domeShake" value="1" onchange="sendDomeUpdate()">
            <label for="domeShake" class="interaction">Dome shake</label>
        </div>
        
    </div>
    <div class="row">
        <div class="c50">
            <h4>Utility Arms</h4>
        </div>
        <div class="c50">
            <h4>Periscope</h4>
        </div>
        <div class="c25">
            <input type="checkbox" id="utilityArm" name="utilityArm" value="1" onchange="sendBodyUpdate()"><br />
            <label for="utilityArm" class="interaction">Utility Arm</label>
        </div>

        <div class="c25">
            <input type="checkbox" id="utilityArmGripper" name="utilityArmGripper" value="1" onchange="sendBodyUpdate()"><br />
            <label for="utilityArmGripper" class="interaction">Utility Arm Gripper</label>
        </div>

        
        <div class="c25">
            <label for="periscopeLift" class="centered">Lift</label>
            <input id="periscopeLift" type="range" min="0" max="255" value="0" class="slider" onInput="sendDomeUpdate()">
        </div>
        <div class="c25">
            <label for="periscopeRotate" class="centered">Rotate</label>
            <input id="periscopeRotate" type="range" min="-127" max="127" value="0" class="slider" onInput="sendDomeUpdate()">
        </div>
    </div>

    <div class="cLeft c50">
        <h4>Left Dome Arm</h4>
        
        <div class="row">
        <div class="c75">
            <label for="domeLeftArmRotate" class="centered">Rotate</label>
            <input id="domeLeftArmRotate" type="range" min="1000" max="2000" value="2000" class="slider" onInput="sendDomeUpdate()">
        </div>
        <div class="c25">
            <input type="checkbox" id="domeLeftArmExtend" name="domeLeftArmExtend" value="1" onchange="sendDomeUpdate()"><br />
            <label for="domeLeftArmExtend" class="interaction">Extend</label>
        </div>
        </div>
        <input type="checkbox" id="bodyArmLeft" name="bodyArmLeft" value="1" onchange="sendBodyUpdate()">
        <label for="bodyArmLeft" class="interaction">Body Tool Left (Dataport)</label>
    </div>

    <div class="cRight c50">
        <h4>Right Dome Arm</h4>
        <div class="row">
        <div class="c25">
            <input type="checkbox" id="domeRightArmExtend" name="domeRightArmExtend" value="1" onchange="sendDomeUpdate()"><br />
            <label for="domeRightArmExtend" class="interaction">Extend</label>
        </div>
        <div class="c75">
            <label for="domeRightArmRotate" class="centered">Rotate</label>
            <input id="domeRightArmRotate" type="range" min="1000" max="2000" value="1000" class="slider" onInput="sendDomeUpdate()">
        </div>
        </div>
        <input type="checkbox" id="bodyArmRight" name="bodyArmRight" value="1" onchange="sendBodyUpdate()">
        <label for="bodyArmRight" class="interaction">Body Tool Right (Saw)</label>

    </div>



    <script>
        window.onload = function () {
            console.log('Dokument geladen');
            systemInit();
        }
    </script>

)====";
