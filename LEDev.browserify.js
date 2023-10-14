(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
document.querySelector("button").addEventListener("click", async () => {
  const port = await navigator.serial.requestPort();
  await port.open({ baudRate: 19200 });
  const writer = await port.writable.getWriter();
  const decoder = new TextDecoder();
  portOpened();

  // Setup event listeners
  // Pass writer/reader to each method
  document.getElementById("color").addEventListener("change", (event) => {
    watchColorPicker(event, writer);
  });

  while (port.readable) {
    const reader = port.readable.getReader();
    try {
      while (true) {
        const { value, done } = await reader.read();
        const decoded = decoder.decode(value);
        console.log(decoded);
        if (done) {
          break;
        }
      }
    } catch (error) {
      console.log(error);
    } finally {
      reader.releaseLock();
    }
  }
});

// Functions
function portOpened() {
  let status = document.getElementById("status");
  status.setAttribute("style", "display: block;");
}

async function watchColorPicker(event, writer) {
  const encoder = new TextEncoder();

  // let hexString = event.target.value.substring(1);
  // // Breaks the string into 2 character chunks representing hexidecimal
  // const hexArray = hexString.match(/.{1,2}/g).map((byte) => parseInt(byte, 16));
  // const dataArray = new Uint8Array(hexArray);
  // await writer.write(dataArray);

  await writer.write(encoder.encode("PING\n"));
}

//JSON testing

function writeJSON() {
  let effect = {
    type: "wave",
    settings: {
      color: "#c8743a",
    },
  };
}

},{}]},{},[1]);
