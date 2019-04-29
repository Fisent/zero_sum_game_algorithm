from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler

from gui import show_window

def get_array():
    return [1, 5, 10, 12, 15]


def serve():
    # Restrict to a particular path.
    class RequestHandler(SimpleXMLRPCRequestHandler):
        rpc_paths = ('/RPC2',)

    # Create server
    with SimpleXMLRPCServer(('localhost', 8000),
                            requestHandler=RequestHandler) as server:
        server.register_introspection_functions()

        server.register_function(show_window)
        server.register_function(get_array)

        # Run the server's main loop
        server.serve_forever()
