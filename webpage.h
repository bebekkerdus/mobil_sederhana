#ifndef WEBPAGE_H
#define WEBPAGE_H

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Sensor & Motor Control</title>
    <link rel="stylesheet" type="text/css" href="/style.css">
</head>
<body>
    <h1>ESP32 Sensor & Motor Control</h1>

    <h2>Temperature: <span id="temp">--</span> °C</h2>
    <h2>Humidity: <span id="hum">--</span> %</h2>

    <button onclick="sendCommand('forward')">Forward</button>
    <button onclick="sendCommand('stop')">Stop</button>
    <button onclick="sendCommand('backward')">Backward</button>
    <br><br>
    <button onclick="sendComm('sedot')">sedot</button>
    <button onclick="sendComm('stp')">Stp</button>
    <script>
        function sendCommand(cmd) {
            fetch("/motor?cmd=" + cmd);
        }

        function sendComm(amb) {
            fetch("/clean?amb=" + amb);
        }
        
        function updateData() {
            fetch("/sensor").then(response => response.json()).then(data => {
                document.getElementById("temp").innerText = data.temperature;
                document.getElementById("hum").innerText = data.humidity;
            });
        }
        setInterval(updateData, 5000);
        updateData();
    </script>
</body>
</html>
)rawliteral";

#endif
