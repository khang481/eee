#include "colors.h"
using namespace std;

const Color darkGrey = {26, 31, 40, 1};
const Color green = {47, 230, 23, 1};
const Color red = {232, 18, 18, 1};
const Color orange = {226, 116, 17, 1};
const Color yellow = {237, 234, 4, 1};
const Color purple = {166, 0, 247, 1};
const Color cyan = {21, 204, 209, 1};
const Color blue = {13, 64, 216, 1};
const Color lightBlue = {59, 85, 162, 1};
const Color darkBlue = {44, 44, 127, 1};

vector<Color> GetCellColors()
{
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}
