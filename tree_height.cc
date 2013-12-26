
struct tree {
  int x;
  tree * l;
  tree * r;
};

// you can also use includes, for example:
// #include <algorithm>
int solution(tree * T) {
    // write your code in C++98
    if ((T->l == NULL) && (T->r == NULL)) return 0;
    
    int lh = 0;
    int rh = 0;
    if (T->l != NULL) {
        lh = solution(T->l);    
    }
    if (T->r != NULL) {
        rh = solution(T->r);     
    }
    
    return 1 + max(lh, rh);
}