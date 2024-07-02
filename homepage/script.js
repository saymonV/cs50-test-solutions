// Selecting button and storing it in a variable
const btnSend = document.querySelector("#btn-send");

// Calls alertUser function on button click
btnSend.addEventListener("click", alertUser)

// Simple function that pops alert in a browser 
function alertUser() {
  alert("Sending messages currently disabled. Sorry for the inconveinece.")
}


