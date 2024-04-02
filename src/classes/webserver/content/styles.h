const String styles = R"====(

body { 
	font-family: 'Helvetica', 'Arial', sans-serif; 
	font-size: 16pt; 
	background-color:#ccc;
}

a:link, a:visited, a:active { 
	text-decoration: none;
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

.slider {
  -webkit-appearance: none;  /* Override default CSS styles */
  appearance: none;
  width: 100%; /* Full-width */
  height: 25px; /* Specified height */
  background: #d3d3d3; /* Grey background */
  outline: none; /* Remove outline */
  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */
  -webkit-transition: .2s; /* 0.2 seconds transition on hover */
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1; /* Fully shown on mouse-over */
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none; /* Override default look */
  appearance: none;
  width: 25px; /* Set a specific slider handle width */
  height: 25px; /* Slider handle height */
  background: #04AA6D; /* Green background */
  cursor: pointer; /* Cursor on hover */
}

.slider::-moz-range-thumb {
  width: 25px; /* Set a specific slider handle width */
  height: 25px; /* Slider handle height */
  background: #04AA6D; /* Green background */
  cursor: pointer; /* Cursor on hover */
}

)====";
