#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include <vector>
#include <string>
#include <sstream>

std::string fields_to_string(const std::vector<int>& fields){
    std::ostringstream ss;
    for(auto field : fields){
        std::cout << static_cast<int>(field) << '\n';
        ss << static_cast<int>(field);
    }
    return ss.str();
}

void xml_rpc(std::vector<int> fields, int phase){
    std::cout << "Hello xml rpc test\n";

    const std::string serverUrl("http://localhost:8000/RPC2");

    xmlrpc_c::clientSimple myClient;
    xmlrpc_c::value result;
    xmlrpc_c::value result_array;
    
    std::string encoded_fields = fields_to_string(fields);
    myClient.call(serverUrl, "show_window", "si" ,&result, encoded_fields.c_str(), xmlrpc_c::value_int(phase));

    std::string re = xmlrpc_c::value_string(result);

    std::cout << "Result of RPC (hello): " << re << '\n';

    myClient.call(serverUrl, "get_array", &result_array);

    auto re_array = xmlrpc_c::value_array(result_array).vectorValueValue();

    std::cout << "Printing received array:\n";
    for(auto element : re_array)
        std::cout << "   " << xmlrpc_c::value_int(element) << '\n';
}

