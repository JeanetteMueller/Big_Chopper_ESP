const String javascript_1 = R"====(

async function postData(url = "", data = {}) {
  // Default options are marked with *
  const response = await fetch(url, {
    method: "POST",
    mode: "cors", // no-cors, *cors, same-origin
    cache: "no-cache",
    headers: {
      "Content-Type": "application/json"
    },
    referrerPolicy: "no-referrer", // no-referrer, *no-referrer-when-downgrade, origin, origin-when-cross-origin, same-origin, strict-origin, strict-origin-when-cross-origin, unsafe-url
    body: JSON.stringify(data), // body data type must match "Content-Type" header
  });
  return response.json(); 
}

)====";

const String javascript_2 = R"====(

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
)====";

const String javascript_3 = R"====(
function systemInit() {
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
}


)====";

const String javascript_joystick_1 = "let StickStatus={xPosition:0,yPosition:0,x:0,y:0,cardinalDirection:\"C\"};var JoyStick=function(t,e,i){var o=void 0===(e=e||{}).title?\"joystick\":e.title,n=void 0===e.width?0:e.width,a=void 0===e.height?0:e.height,r=void 0===e.internalFillColor?\"#00AA00\":e.internalFillColor,c=void 0===e.internalLineWidth?2:e.internalLineWidth,";
const String javascript_joystick_2 = "s=void 0===e.internalStrokeColor?\"#003300\":e.internalStrokeColor,d=void 0===e.externalLineWidth?2:e.externalLineWidth,u=void 0===e.externalStrokeColor?\"#008000\":e.externalStrokeColor,h=void 0===e.autoReturnToCenter||e.autoReturnToCenter;i=i||function(t){};var S=document.getElementById(t);S.style.touchAction=\"none\";";
const String javascript_joystick_3 = "var f=document.createElement(\"canvas\");f.id=o,0===n&&(n=S.clientWidth),0===a&&(a=S.clientHeight),f.width=n,f.height=a,S.appendChild(f);var l=f.getContext(\"2d\"),k=0,g=2*Math.PI,x=(f.width-(f.width/2+10))/2,v=x+5,P=x+30,m=f.width/2,C=f.height/2,p=f.width/10,y=-1*p,w=f.height/10,L=-1*w,F=m,E=C;function W(){";
const String javascript_joystick_4 = "l.beginPath(),l.arc(m,C,P,0,g,!1),l.lineWidth=d,l.strokeStyle=u,l.stroke()}function T(){l.beginPath(),F<x&&(F=v),F+x>f.width&&(F=f.width-v),E<x&&(E=v),E+x>f.height&&(E=f.height-v),l.arc(F,E,x,0,g,!1);";
const String javascript_joystick_5 = "var t=l.createRadialGradient(m,C,5,m,C,200);t.addColorStop(0,r),t.addColorStop(1,s),l.fillStyle=t,l.fill(),l.lineWidth=c,l.strokeStyle=s,l.stroke()}function D(){let t="",e=F-m,i=E-C;return i>=L&&i<=w&&(t=\"C\"),i<L&&(t=\"N\"),i>w&&(t=\"S\"),e<y&&(\"C\"===t?t=\"W\":t+=\"W\"),e>p&&(\"C\"===t?t=\"E\":t+=\"E\"),t}\"ontouchstart\"in document.documentElement?(";
const String javascript_joystick_6 = "f.addEventListener(\"touchstart\",function(t){k=1},!1),document.addEventListener(\"touchmove\",function(t){1===k&&t.targetTouches[0].target===f&&(F=t.targetTouches[0].pageX,E=t.targetTouches[0].pageY,\"BODY\"===f.offsetParent.tagName.toUpperCase()?(F-=f.offsetLeft,E-=f.offsetTop):(F-=f.offsetParent.offsetLeft,E-=f.offsetParent.offsetTop),l.clearRect(";
const String javascript_joystick_7 = "0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus))},!1),document.addEventListener(\"touchend\",function(t){k=0,h&&(F=m,E=C);l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=(";
const String javascript_joystick_8 = "(F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus)},!1)):(f.addEventListener(\"mousedown\",function(t){k=1},!1),document.addEventListener(\"mousemove\",function(t){1===k&&(F=t.pageX,E=t.pageY,\"BODY\"===f.offsetParent.tagName.toUpperCase()?(F-=f.offsetLeft,E-=f.offsetTop):(F-=f.offsetParent.offsetLeft,E-=f.offsetParent.offsetTop";
const String javascript_joystick_9 = "),l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus))},!1),document.addEventListener(\"mouseup\",function(t){k=0,h&&(F=m,E=C);l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=(";
const String javascript_joystick_10 = "(F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus)},!1)),W(),T(),this.GetWidth=function(){return f.width},this.GetHeight=function(){return f.height},this.GetPosX=function(){";
const String javascript_joystick_11 = "return F},this.GetPosY=function(){return E},this.GetX=function(){return((F-m)/v*100).toFixed()},this.GetY=function(){return((E-C)/v*100*-1).toFixed()},this.GetDir=function(){return D()}};";
