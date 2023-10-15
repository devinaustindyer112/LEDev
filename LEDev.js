document.querySelector("button").addEventListener("click", async () => {
  const port = await navigator.serial.requestPort();
  await port.open({ baudRate: 115200 });
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

  await writer.write(encoder.encode("H\n"));

  setTimeout(async () => {
    const json = {
      effect: "wave",
    }
    await writer.write(encoder.encode(`${JSON.stringify(json)}\n`));
  }, 1000);
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
