#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <regex>

using namespace std;

int main()
{
    string roughness_str = "01.0";
    string envmapLvl_str = "0.0";
    char buff[256];
    std::cmatch m;
    string shader_txt = "../fragment_shader.txt";
    string shader_txt_out = "../fragment_shader_modified.txt";
    fstream setRoughness(shader_txt);
    ofstream setRoughness_out(shader_txt_out, ios::out);
    regex rule_roughness("(roughness.*defaultval)");
    regex rule_envmapLvl("(envMapLevel.*defaultval)");
    regex rule_default("defaultval(\\s*)=(\\s*)\".*\"");
    if (!setRoughness.is_open())
        cout << "Error open shader_txt" << endl;
    if (!setRoughness_out.is_open())
        cout << "Error open shader_txt_out" << endl;
    while (!setRoughness.eof())
    {
        setRoughness.getline(buff, 100);
        bool ret_1 = std::regex_search(buff, m, rule_roughness);
        bool ret_2 = std::regex_search(buff, m, rule_envmapLvl);
        if (ret_1)
        {
            cout << buff << endl;
            char toreplace_buff[256];
            sprintf(toreplace_buff, "defaultval=\"%s\"", roughness_str.c_str());
            string new_string = std::regex_replace(buff, rule_default, toreplace_buff);
            setRoughness_out << new_string << endl;
        }

        else if (ret_2)
        {
            cout << buff << endl;
            char toreplace_buff[256];
            sprintf(toreplace_buff, "defaultval=\"%s\"", envmapLvl_str.c_str());
            string new_string = std::regex_replace(buff, rule_default, toreplace_buff);
            setRoughness_out << new_string << endl;
        }
        else
        {
            setRoughness_out << buff << endl;
        }
    }
    setRoughness.close();
    setRoughness_out.close();

    return 0;
}