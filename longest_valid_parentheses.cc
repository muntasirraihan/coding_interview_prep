// handle cases
// ()()
// (()()
// ()(()

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty()) return 0;
        
        int maxValid = 0;
        int prevStart = 0;
        stack<pair<char, int> > st;
        for (int i = 0; i < s.size(); ++i) {
            char current = s[i];
            if (current == '(') {
                // see '('
                st.push(make_pair(current, i));
            } else {
                // see ')'
                if (st.empty()) {
                    // invalid ')'
                    prevStart = i + 1;
                } else {
                    // match with a previous '('
                    st.pop();
                    if (st.empty()) {
                        // matched all '(' seen so far since prevStart
                        maxValid = max(maxValid, i - prevStart + 1);
                    } else {
                        // some '(' still not matched
                        pair<char, int> tmp = st.top();
                        maxValid = max(maxValid, i - tmp.second);
                    }
                }
            }
        }
        
        return maxValid;
    }
};