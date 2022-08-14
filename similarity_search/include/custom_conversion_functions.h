#include <stdint.h>
#include <string>
#include <algorithm>
#include <bitset>
#include <limits.h>

namespace custom_conversion_functions_hergen {
    std::string uint32_to_string(uint32_t value) {
        std::bitset<32> bits(value);
        std::string str = bits.to_string();
        reverse(str.begin(), str.end());
        return str;
    }

    std::string float_to_bits(float f)
    {
        union
        {
            float input; // assumes sizeof(float) == sizeof(int)
            uint32_t output;
        } data;
    
        data.input = f;
    
        std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);
        std::string str = bits.to_string();
        
        reverse(str.begin(), str.end());
        return str;
    }
}