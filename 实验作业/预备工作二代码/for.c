int main() {
    int a = 0 ,b = 1, res;
    for (int i = 0; i < 10; i ++ ) {
        b = b + a;
        a = b - a;
    }
    res = b;
    return 0;
}