/*****************************************************************************
 * Test cases for libxlsxwriter.
 *
 * Test to compare output against Excel files.
 *
 * Copyright 2014-2015, John McNamara, jmcnamara@cpan.org
 *
 */

#include "xlsxwriter.h"

int main() {

    lxw_workbook  *workbook  = new_workbook("test_chart_bar01.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    lxw_chart     *chart     = workbook_add_chart(workbook, LXW_CHART_BAR);

    /* For testing, copy the randomly generated axis ids in the target file. */
    chart->axis_id_1 = 64052224;
    chart->axis_id_2 = 64055552;

    uint8_t data[5][3] = {
        {1, 2,  3},
        {2, 4,  6},
        {3, 6,  9},
        {4, 8,  12},
        {5, 10, 15}
    };

    int row, col;
    for (row = 0; row < 5; row++)
        for (col = 0; col < 3; col++)
            worksheet_write_number(worksheet, row, col, data[row][col] , NULL);

    lxw_chart_series *series1 = chart_add_series(chart, "=Sheet1!$A$1:$A$5", "=Sheet1!$B$1:$B$5");
    lxw_chart_series *series2 = chart_add_series(chart, "=Sheet1!$A$1:$A$5", "=Sheet1!$C$1:$C$5");

    worksheet_insert_chart(worksheet, CELL("E9"), chart);

    /* Add cache data for testing. */
    lxw_chart_add_data_cache(series1->categories, data[0], 5, 3, 0);
    lxw_chart_add_data_cache(series2->categories, data[0], 5, 3, 0);
    lxw_chart_add_data_cache(series1->values,     data[0], 5, 3, 1);
    lxw_chart_add_data_cache(series2->values,     data[0], 5, 3, 2);


    return workbook_close(workbook);
}
