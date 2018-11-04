#ifndef JARNGREIPR_WRITE_TOML_VALUE_HPP
#define JARNGREIPR_WRITE_TOML_VALUE_HPP
#include <extlib/toml/toml.hpp>

namespace jarngreipr
{

template<typename charT, typename traits>
void write_toml_value(
        std::basic_ostream<charT, traits>& os, const toml::value& v)
{
    switch(v.type())
    {
        case toml::value_t::Boolean:
        {
            os << std::boolalpha << toml::get<bool>(v);
            return;
        }
        case toml::value_t::Integer:
        {
            os << toml::get<toml::Integer>(v);
            return;
        }
        case toml::value_t::Float:
        {
            os << std::setw(9) << std::fixed<< std::setprecision(4)
               << toml::get<toml::Float>(v);
            return;
        }
        case toml::value_t::String:
        {
            os << '"' << toml::get<toml::String>(v) << '"';
            return;
        }
        case toml::value_t::Array:
        {
            os << '[';
            const auto ary = v.cast<toml::value_t::Array>();
            for(auto iter = ary.begin(); iter != ary.end(); ++iter)
            {
                if(iter != ary.begin()){os << ',';}
                write_toml_value(os, item);
            }
            os << ']';
            return;
        }
        case toml::value_t::Table:
        {
            os << '{';
            const auto& tab = v.cast<toml::value_t::Table>();
            for(auto iter = tab.begin(); iter != tab.end(); ++iter)
            {
                if(iter != tab.begin()) {os << ',';}
                os << iter->first << '=';
                write_toml_value(os, iter->second);
            }
            os << '}';
            return;
        }
        default:
            throw std::runtime_error("write_toml_value: not a simple value: " +
                    toml::stringize(v.type()));
    }
}

} // jarngreipr
#endif// JARNGREIPR_WRITE_TOML_VALUE_HPP
