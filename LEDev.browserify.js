(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
const BAUD_RATE = 115200;

document.querySelector("button").addEventListener("click", async () => {
  const { writer, reader } = await openPort();

  document.getElementById("status")
    .setAttribute("style", "display: block;");

  // Setup event listeners
  document.getElementById("color").addEventListener("change", (event) => {
    handleColorChange(event, writer, reader);
  });
});

async function openPort() {
  const port = await navigator.serial.requestPort();
  await port.open({ baudRate: BAUD_RATE });
  const writer = await port.writable.getWriter();
  const reader = await port.readable.getReader();

  return {
    writer,
    reader,
  }
}

async function handleColorChange(event, writer, reader) {
  const encoder = new TextEncoder();
  const decoder = new TextDecoder();

  const color = `#${event.target.value.substring(1)}`
  const colorLabel = document.getElementById("color_label");
  colorLabel.textContent = color

  await writer.write(encoder.encode("H\n"));

  console.log("Waiting for acceptance...");

  while (true) {
    const { value, done } = await reader.read();
    const decoded = decoder.decode(value);
    if (decoded === "A") {
      break;
    }
  }

  console.log("Sending color...");

  const json = {
    effect: "meteor",
    color,
  }

  await writer.write(encoder.encode(JSON.stringify(json) + "\n"));
  console.log("Done!");
}

},{}]},{},[1]);
