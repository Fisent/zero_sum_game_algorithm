import xmlrpc.client

s = xmlrpc.client.ServerProxy('http://localhost:8000')
print(s.hello())  # Returns 2**3 = 8

# Print list of available methods
print(s.system.listMethods())