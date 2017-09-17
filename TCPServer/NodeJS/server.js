var net = require('net');
var server = net.createServer(function(connection) {
	console.log('on connection');

	// receive data
	connection.on('data', function(data){
		console.log('on data: ip[' + connection.remoteAddress + '], port[' + connection.remotePort + '], data[' + data + ']');
		connection.write('hello ' + connection.remoteAddress);
	});

	// connection close
	connection.on('close', function() {
		console.log('on close: ip[' + connection.remoteAddress + '], port[' + connection.remotePort + ']');
	});

	// connection error
	connection.on('error', function() {
		console.log('on error: ip[' + connection.remoteAddress + '], port[' + connection.remotePort + ']');
	});
}).listen(8124);