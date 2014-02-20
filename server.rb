<<<<<<< Updated upstream
require 'socket'               # Get sockets from stdlib
require 'json'

server = TCPServer.open(2000)  # Socket to listen on port 2000
loop {                         # Servers run forever
  client = server.accept       # Wait for a client to connect
  client.puts("REQUEST_OK")  # Send the time to the client
  request = client.gets
  puts request
  hash = JSON.parse request
  client.puts "Connection closing"
  client.close                 # Disconnect from the client
}
=======
require 'socket'
require 'json'

server = TCPServer.open(2000)
loop {
	client = server.accept
	client.puts("REQUEST_OK")
	client.puts "Connection closing"
	request = client.gets
	puts request
	client.close
}
>>>>>>> Stashed changes
