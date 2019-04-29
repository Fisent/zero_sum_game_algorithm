#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>


void xml_rpc(){
    std::cout << "Hello xml rpc test\n";

    const std::string serverUrl("http://localhost:8000/RPC2");

    xmlrpc_c::clientSimple myClient;
    xmlrpc_c::value result;
    xmlrpc_c::value result_array;
    
    myClient.call(serverUrl, "show_window", &result);

    std::string re = xmlrpc_c::value_string(result);

    std::cout << "Result of RPC (hello): " << re << '\n';

    myClient.call(serverUrl, "get_array", &result_array);

    auto re_array = xmlrpc_c::value_array(result_array).vectorValueValue();

    std::cout << "Printing received array:\n";
    for(auto element : re_array)
        std::cout << "   " << xmlrpc_c::value_int(element) << '\n';
}
