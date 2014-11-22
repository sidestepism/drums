var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

var sp = new SerialPort("/dev/tty.usbmodem1411", { // ここのパスは適宜変更する
    baudrate: 9600,
    parser: serialport.parsers.readline("\n") // 1行毎にパースする
}, false);

var server = require('http').Server();
var io = require('socket.io').listen(server);
server.listen(process.env.PORT || 8000);

var drumTable = ['cymbal', 'rightTam', 'bassDrum', 'leftTam'];
sp.open(function () {
    sp.on('data', function(data) {
        console.log('data received: ' + data);
        data = data.split(' ');
        var drumtype = drumTable[parseInt(data[0])];
        var intensity = parseInt(data[1]);
        console.log(drumtype, intensity);
        io.sockets.emit(drumtype, intensity);
    });
});