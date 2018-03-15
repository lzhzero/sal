// Hello World server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "world"
console.time('em_module');
var em_module = require('./fs.js');
console.timeEnd('em_module');
var zmq = require('zmq');
// socket to talk to clients
var responder = zmq.socket('rep');
//load local em wasm module

responder.on('message', function(request) {
  var raws = request.toString();
//  console.log("Received request: [", raws, "]");
  
    var strLen = em_module.lengthBytesUTF8(raws);
    var dataptr = em_module._malloc(strLen+1);
    em_module.stringToUTF8(raws, dataptr, strLen+1)
    em_module._run(dataptr);
    em_module._free(dataptr); 
    // send reply back to client.
    responder.send(" Done");
//    responder.send("ZF "+ s+ " Done");


});

responder.bind('tcp://*:5555', function(err) {
  if (err) {
    console.log(err);
  } else {
    console.log("Listening on 5555…");
  }
  console.time('fs_prepare');
  em_module._fs_prepare();
  console.timeEnd('fs_prepare');
});

process.on('SIGINT', function() {
  responder.close();
});


