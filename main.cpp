#include <iostream>
#include <fstream>
#include <OpenXLSX.hpp>

#include "arrayProcedures.h"


using namespace OpenXLSX;


int main() {
    XLDocument doc;
    doc.open("map.xlsx");
    auto wks = doc.workbook().worksheet("Paradarium");

    cout << wks.cell("BW7").value();

    doc.save();

    return 0;
}
