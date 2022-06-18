#include "Simple_window.h"
#include "Graph.h"
#include "hyperelliptic.h"
#include "std_lib_facilities.h"
#include <iostream>

int main() {
    double a, b, m, n;
    int N;
    cout << "Please input a b m n N (N is a non-negative even integer): ";
    cin >> a >> b >> m >> n >> N;

    Hyperelliptic hyp(a, b, m, n, N);

    hyp.set_color(Color :: red);

    Point tl(200, 200);
    Simple_window win(tl, 800, 600, "Hyperelliptic");

    win.attach (hyp);

    win.wait_for_button();
    return 0;
}
