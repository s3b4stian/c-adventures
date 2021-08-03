//you mustn’t use this declaration outside a function body;
//the array’s size must be greater than zero;

//you mustn’t use this declaration if the declared array is a field of a structure
//struct { int vec[n]; } S;

//jumping into a block containing a variable-length array declaration is not allowed; both of the following programs are erroneous:
//int main (void)
//{
//    int n = 1;
//    goto inner;
//
//    for (;;) {
//        int t[n];
//inner:
//        t[0] = 0;
//    }
//}