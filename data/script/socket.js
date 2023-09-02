import { canvas } from "./graph.js";

let targetUrl = `ws://${window.location.hostname}:777/ws`;
let websocket;
let buttons = document.getElementById("buttons")
let loading = document.getElementById("carregando")

window.addEventListener('load', onLoad);
document.getElementById("downloadBtn").onclick = getCsv;

fetchData()
canvas()

async function fetchData() {
  const response = await fetch("data")
    .then(response => response.json())
    .then(data => {
      console.log(data);
      if(data.length){
        for(let i=0 ; i<data.length; i++){
          let div = document.createElement("div");
          let text = document.createElement("p");
          let button = document.createElement("button");

          text.textContent = `Led ${data[i][0]} - State "${data[i][1]}"`;

          button.textContent = stateButton(data[i][1]);
          button.classList.add("button")
          button.classList.add(`${stateButton(data[i][1])}${data[i][0]}`);
          button.id = data[i][0];
          button.onclick = function() {buttonToggle(this)};

          div.appendChild(text);
          div.appendChild(button);
          buttons.appendChild(div);
        }
        buttons.classList.remove("hidden")
        loading.classList.add("hidden")
      }
  })
}

function stateButton(button){
  if(button==="ON"){
    return "OFF"
  } else{
    return "ON"
  }
}

function onLoad() {
  initializeSocket();
}

function initializeSocket() {
  console.log('Opening WebSocket connection to ESP32...');
  websocket = new WebSocket(targetUrl);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}
function onOpen(event) {
  console.log('Starting connection to server..');
}
function onClose(event) {
  console.log('Closing connection to server..');
  setTimeout(initializeSocket, 2000);
}
function onMessage(event) {
  console.log("WebSocket message received:", event)
}

function sendMessage(message) {
  websocket.send(message);
}

function buttonToggle(test){
  let buttonId = test.id;
  let button = document.getElementById(buttonId);
    if(button.innerHTML=="ON"){
      sendMessage(`${buttonId},ON`); 
      button.classList.remove(`ON${buttonId}`)
      button.innerHTML="OFF"
    }else{
      sendMessage(`${buttonId},OFF`); 
      button.classList.add(`ON${buttonId}`)
      button.innerHTML="ON"
    }
}

function getCsv(){
  fetch('/test.csv')
    .then(response => {
      if (!response.ok) {
        throw new Error('Erro na solicitação: ' + response.statusText);
      }
      return response.text()
    })
    .then(csvContent => {
        const blob = new Blob([csvContent], { type: 'text/csv' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'data.csv';
        a.click();
    }).catch(error => {
      console.log(error);
    });
}