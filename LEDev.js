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
