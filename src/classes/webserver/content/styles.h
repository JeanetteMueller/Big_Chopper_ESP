const char styles[] = R"====(

* {
    margin: 0px;
    padding: 0px;
}

body {
    font-family: 'Helvetica', 'Arial', sans-serif;
    font-size: 16pt;
    background-color: black;
    color: #999;
    /* position: fixed; */
    /* overflow-y: scroll; */
    padding: 0px;
    margin: 0px;
    min-width: fit-content;
    width: 100%;
    border: 0;
}

hr {
    margin: 10px;
}

a:link,
a:visited,
a:active {
    text-decoration: none;
}

h4, h5 {
    text-align: center;
}

.statusbar {
    width: 100%;
    background-color: #333;
    padding: 5px;
    text-align: left;
}

#menu {
    z-index: 10000;
    display: block;
    width: 100%;
    height: 100%;
    background-color: #333;
    position: absolute;
    top: 0px;
    left: 0px;
    visibility: hidden;
    text-align: center;
}

.content {
    width: calc(50% - 21px);
    float: left;
    min-height: 100%;
    padding: 10px;
}

.centered{
    width: 100%;
    display: block;
    text-align: center;
}

.contentLeft {
    border-right: 2px solid #333;
}

.contentRight {
    text-align: right;
}
.contentRight > h4 {
    text-align: right;
}

.contentHalfBox {
    width:50%;
    float:left;
    align-items: center;
    text-align: center;
}
.contentMax {
    width: 100%;
}

#drive {
    z-index: 10000;
    display: block;
    width: 100%;
    height: 100%;
    background-color: blue;
    position: absolute;
    top: 0px;
    left: 0px;
    visibility: hidden;
    text-align: center;
}

button {
    background-color: #333;
    display: inline-block;
    padding: 5px;
    margin: 5px;
    color: #fff;
    text-decoration: none;
    border-radius: 5px;
}

.button {
    background-color: #333;
    display: inline-block;
    padding: 5px;
    margin: 5px;
    color: #fff;
    text-decoration: none;
    border-radius: 5px;
}

.interaction {
    padding: 5px;
    margin: 5px;
    background-color: #666;
    min-height: 34px;
    font-size: 28px;
    color: #fff;
    display: inline-block;
    border-radius: 5px;
}

input {
    padding: 10px;
    margin: 10px;
}

.slider {
    -webkit-appearance: none;
    /* Override default CSS styles */
    appearance: none;
    width: calc(100% - 40px);;
    /* Full-width */
    height: 30px;
    /* Specified height */
    background: #333;
    /* Grey background */
    outline: none;
    /* Remove outline */
    -webkit-transition: .2s;
    /* 0.2 seconds transition on hover */
    transition: opacity .2s;
    border-radius: 20px;
    padding: 10px;
}

.slider::-webkit-slider-thumb {
    -webkit-appearance: none;
    /* Override default look */
    appearance: none;
    width: 30px;
    /* Set a specific slider handle width */
    height: 30px;
    /* Slider handle height */
    background: white;
    /* Green background */
    cursor: pointer;
    /* Cursor on hover */
    border-radius: 30px;
}

.slider::-moz-range-thumb {
    width: 30px;
    /* Set a specific slider handle width */
    height: 30px;
    /* Slider handle height */
    background: white;
    /* Green background */
    cursor: pointer;
    /* Cursor on hover */
    border-radius: 30px;
}

)====";
