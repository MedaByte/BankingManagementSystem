const express = require("express");
const cors = require("cors");
const { spawn } = require("child_process"); // Needed to run C++
const app = express();

app.use(cors());
app.use(express.json());
let month = new Date().getMonth();
sendDataToCppAndReseveItAfterCppOperation("CPP/main.exe",{command:"check new month",info:String(month),object:{}})

app.post("/submit", (req, response) => {
  const dataRecieved = req.body; // Extract values from JSON
  sendDataToCppAndReseveItAfterCppOperation(
    "CPP/main.exe",
    dataRecieved,
    response
  );
});

app.listen(3000, () => {
  console.log("Server running on http://localhost:3000"); // this is the server http entered in google no github required
});

function sendDataToCppAndReseveItAfterCppOperation(
  cppFilePath,
  dataToSend,
  response
) {
  const cpp = spawn(cppFilePath); // or "compute.exe" on Windows

  let output = "";

  // Capture output from C++
  cpp.stdout.on("data", (data) => {
    output += data.toString();
  });

  // Handle errors
  cpp.stderr.on("data", (data) => {
    console.log(`C++ messages: ${data}`);
  });

  // When C++ process finishes, send result back
  cpp.on("close", (code) => {
    console.log(`C++ exited with code ${code}`);
    if (response) response.json({ result: output.trim() });
  });

  // Send input to C++ via stdin
  cpp.stdin.write(JSON.stringify(dataToSend) + "\n");
  cpp.stdin.end();
}
