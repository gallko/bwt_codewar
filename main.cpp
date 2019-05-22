#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::pair<std::string, int> encode(const std::string& s) {
    std::vector<std::string> v;
    for (auto i = 0; i < s.length(); ++i) {
        std::string ts(s);
        std::rotate(ts.begin(), ts.end() - i, ts.end());
        v.push_back(ts);
    }
    std::sort(v.begin(), v.end());
    auto it = std::find(v.begin(), v.end(), s);
    std::string result(s);
    std::transform(v.begin(), v.end(), result.begin(), [](std::string s) -> char {
        return *(s.end()-1);
    });
    return {result, it - v.begin()};
}

std::string decode(const std::string& s, int n) {
    using my_pair = std::pair<char, int>;
    std::vector<my_pair> v(s.length());
    auto it = 0;
    std::for_each(v.begin(), v.end(), [s, &it](my_pair &el){
        el.first = s[it];
        el.second = it++;
    });

    std::stable_sort(v.begin(), v.end(),[](const my_pair &el1, const my_pair &el2) {
        return (el1.first < el2.first);
    });

    std::string r(s);
    std::for_each(r.begin(), r.end(), [v, &n](char &el) {
        const my_pair &p = v[n];
        el = p.first;
        n = p.second;
    });
    return r;
}

int main() {
    std::cout << "Hello, World!" <<  std::endl;

    auto str = "dddaaa";

    auto d = encode(str);
    auto s = decode(d.first, d.second);

    std::cout << d.first << " " << d.second << std::endl;
    std::cout << s << std::endl;
    std::cout << str << std::endl;
    std::cout << (str == s) << std::endl;


    return 0;
}
