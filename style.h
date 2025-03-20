#ifndef STYLE_H
#define STYLE_H

const char cssPage[] PROGMEM = R"rawliteral(
body {
    font-family: Arial, sans-serif;
    text-align: center;
    background-color: #f4f4f4;
    padding-top: 50px;
}
button {
    font-size: 20px;
    padding: 10px 20px;
    margin: 10px;
    cursor: pointer;
}
input[type="range"] {
    width: 50%;
}
)rawliteral";

#endif
