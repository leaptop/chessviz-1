#include "board_print_html.h"

#include "funcs.h"
#include "board.h"

#include <stdlib.h>
#include <stdio.h>

void PrintHtmlHead() {
    fprintf(outfile,R"(
        <!DOCTYPE html>
        <html>
            <head>
                <meta charset="utf-8">
                <title>chessviz</title>
                <style type="text/css">
                table.chessboard {
                    border: 5px solid #333;
                    border-collapse: collapse;
                    height: 320px;
                    margin: 20px;
                    width: 320px;
                }
                table.chessboard caption {
                    text-align: left;
                }
                table.chessboard td {
                    background-color: #fff;
                    font-size: 25px;
                    height: 40px;
                    text-align: center;
                    vertical-align: middle;
                    width: 40px;
                }
                table.chessboard tr:nth-child(odd) td:nth-child(even),
                table.chessboard tr:nth-child(even) td:nth-child(odd) {
                    background-color: #999;
                }
    
                table.chessboard .wK:before   { content: "\2654"; }
                table.chessboard .wQ:before  { content: "\2655"; }
                table.chessboard .wR:before   { content: "\2656"; }
                table.chessboard .wB:before { content: "\2657"; }
                table.chessboard .wN:before { content: "\2658"; }
                table.chessboard .wP:before   { content: "\2659"; }
    
                table.chessboard .k:before   { content: "\265A"; }
                table.chessboard .q:before  { content: "\265B"; }
                table.chessboard .r:before   { content: "\265C"; }
                table.chessboard .b:before { content: "\265D"; }
                table.chessboard .n:before { content: "\265E"; }
                table.chessboard .p:before   { content: "\265F"; }
            </style>
        </head>
        <body> )");
}

void PrintHtmlBottom() {
    fprintf(outfile,R"(
        </body>
        </html>)");
}

void PrintBoardHtml() {
fprintf(outfile,R"(<table class="chessboard"> )");
  PrintLog();
  for (int i=7;i>=0;i--) {
    fprintf(outfile,"<tr>\n");
    for (int j=7;j>=0;j--) {
        char tmp[2];
        tmp[0] = board[j][i];
        tmp[1] = ' ';
        if (tmp[0]>='A' && tmp[0]<='Z') {
            tmp[1] = tmp[0];
            tmp[0] = 'w';
        }
        if (tmp[0]!=' ') fprintf(outfile,"<td><span class=%s></span></td>\n",tmp);
            else fprintf(outfile,"<td></td>\n");
    }
    fprintf(outfile,"</tr>\n");
  }
  fprintf(outfile,"</table>");
}
