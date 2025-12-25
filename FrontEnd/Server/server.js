const express = require("express");
const cors = require("cors");
const { spawn } = require("child_process");
const path = require("path");
const app = express();


const corsOptions = {
  origin: "*",          // allow all origins for testing
  methods: ["GET","POST","PUT","DELETE","OPTIONS"],
  allowedHeaders: ["Content-Type"]
};

app.use(cors(corsOptions));


app.use(express.json());
console.log("Platform:", process.platform);

const cppFile = process.platform === "win32"
  ? path.join(__dirname, "CPP", "main.exe")
  : path.join(__dirname, "CPP", "main");

// Initial check
let month = new Date().getMonth();
sendDataToCppAndReceiveItAfterCppOperation(cppFile, {command:"check new month", info:String(month), object:{}});



app.post("/submit", (req, res) => {
  sendDataToCppAndReceiveItAfterCppOperation(cppFile, req.body, res);
});

const PORT = process.env.PORT || 3000 ;

app.listen(PORT, "0.0.0.0" , () => {
  console.log("Server running on http://localhost:"+PORT);
});

function sendDataToCppAndReceiveItAfterCppOperation(cppPath, data, res) {
  const cpp = spawn(cppPath);
  let finished = false ;

  let output = "";

  cpp.stdout.on("data", data => output += data.toString());
  cpp.stderr.on("data", data => console.log(`C++ stderr: ${data}`));

  cpp.on("close", code => {
    finished = true ;
    console.log(`C++ exited with code ${code}`);
    if (res) res.json({ result: output.trim() });
  });

  cpp.stdin.write(JSON.stringify(data) + "\n");
  cpp.stdin.end();


  setTimeout(() => {
    if (!finished) {
      cpp.kill();
      finished = true;
      console.log("C++ TimeOut Error");
    }
  }, 10000);
}
