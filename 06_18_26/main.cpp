#include "node.h"
#include "donut.h"

int main()
{
    donut myDonut("none", "none", "none");
    node2<donut> d(myDonut);

    return 0;
}