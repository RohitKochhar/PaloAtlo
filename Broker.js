// Node-module imports ---------------------------------------------------------
var mosca = require('mosca');
// Global Variables ------------------------------------------------------------
var broker;                                       // Variable to store mosca broker
var g_port = 1927;                                // Port to access mosca broker
// Create Mosca Broker ---------------------------------------------------------
function createMosca(){
  console.log("Creating listener on port 1927...")
  broker = new mosca.Server({port: g_port});
  broker.on('ready', () => {console.log("Listener is ready on port 1927")})
  broker.on('clientConnected', (client) => {console.log(client.id + " has connected")})
  broker.on('published', function(packet, client) {
    console.log("Topic: " + packet.topic + ", Message: " + packet.payload.toString())
  })
}
