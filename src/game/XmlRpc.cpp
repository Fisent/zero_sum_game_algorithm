#include "XmlRpc.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

std::string fields_to_string(const std::vector<int>& fields){
    std::ostringstream ss;
    for(auto field : fields){
        // std::cout << static_cast<int>(field) << '\n';
        ss << static_cast<int>(field);
    }
    return ss.str();
}

std::string phase_to_string(int phase){
    std::ostringstream ss;
    ss << phase;
    return ss.str();
}

Move ask_player_about_move(std::vector<int> fields, int phase, bool time_to_take){
    
    const std::string serverUrl("http://localhost:8000/RPC2");

    xmlrpc_c::clientSimple myClient;
    xmlrpc_c::value result;
    // xmlrpc_c::value result_array;
        
    std::cout << "Calling python with phase " << phase << '\n';

    std::string encoded_fields = fields_to_string(fields);
    std::string time_to_take_str = time_to_take ? "yes" : "";
    myClient.call(serverUrl, "show_window", "ss" ,&result, encoded_fields.c_str(), phase_to_string(phase).c_str(), time_to_take);

    std::string re = xmlrpc_c::value_string(result);

    std::cout << "Result of RPC (show_window): " << re << '\n';

    // myClient.call(serverUrl, "get_array", &result_array);

    // auto re_array = xmlrpc_c::value_array(result_array).vectorValueValue();

    // std::cout << "Printing received array:\n";
    // for(auto element : re_array)
    //     std::cout << "   " << xmlrpc_c::value_int(element) << '\n';


    if(phase == 0)
        return Move{boost::lexical_cast<int>(re), time_to_take};
    else if(phase == 1 or phase == 2){
        std::vector<std::string> results;
        boost::split(results, re, [](char c){return c == ',';});
        
        return Move{boost::lexical_cast<int>(results.at(0)), boost::lexical_cast<int>(results.at(1)), time_to_take};
    }
    else
        return Move{-3, -3, false};
}

// void xml_rpc(std::vector<int> fields, int phase){
//     std::cout << "Hello xml rpc test\n";

//     const std::string serverUrl("http://localhost:8000/RPC2");

//     xmlrpc_c::clientSimple myClient;
//     xmlrpc_c::value result;
//     xmlrpc_c::value result_array;
    
//     std::string encoded_fields = fields_to_string(fields);
//     myClient.call(serverUrl, "show_window", "ss" ,&result, encoded_fields.c_str(), phase_to_string(phase).c_str());

//     std::string re = xmlrpc_c::value_string(result);

//     std::cout << "Result of RPC (show_window): " << re << '\n';

//     myClient.call(serverUrl, "get_array", &result_array);

//     auto re_array = xmlrpc_c::value_array(result_array).vectorValueValue();

//     std::cout << "Printing received array:\n";
//     for(auto element : re_array)
//         std::cout << "   " << xmlrpc_c::value_int(element) << '\n';
// }
