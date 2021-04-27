var os = require('os');
var osu = require('os-utils');
const SerialPort = require('serialport');
const port = new SerialPort('COM4', { baudRate: 9600 });

// Read the port data
port.on("open", () => {
    console.log('Connected');
    setTimeout(() => {
        port.write(`OS\n`);
        port.write(`${os.userInfo().username}@${os.hostname()}\n`);
        port.write(`${os.platform()} ${os.release()}\n`);
        setTimeout(() => {
            setInterval(() => {
                osu.cpuUsage(function(v){
                    const res = convertMS(osu.sysUptime());
                    port.write(`CPU ${(v * 100).toFixed(0)}%\n`);
                    port.write(`MEM ${((-osu.freememPercentage() + 1) * 100).toFixed(0)}%\n`);
                    port.write(`TIME ${res.d}:${res.h}:${res.m}:${res.s}\n`);
                });
            }, 10000);
        }, 5000);
    }, 5000);
});

function convertMS(ms) {
    var d, h, m, s;
    s = Math.floor(ms / 1000);
    m = Math.floor(s / 60);
    s = s % 60;
    h = Math.floor(m / 60);
    m = m % 60;
    d = Math.floor(h / 24);
    h = h % 24;
    return { d: d, h: h, m: m, s: s };
};
