from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler

def hello():
    return 'Hey! Hello World!'

def get_array():
    return [1, 5, 10, 12, 15]

# Restrict to a particular path.
class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

# Create server
with SimpleXMLRPCServer(('localhost', 8000),
                        requestHandler=RequestHandler) as server:
    server.register_introspection_functions()

    server.register_function(hello)
    server.register_function(get_array)

    # Run the server's main loop
    server.serve_forever()