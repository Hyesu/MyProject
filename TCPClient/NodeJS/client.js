var net = require('net');
var client = new net.Socket();
client.setEncoding('utf8');
client.connect('8124', 'localhost', function() {
	console.log('connected to server');
	client.write('hello server!');
});

process.stdin.resume();
process.stdin.on('data', function(data) {
	client.write(data);
});