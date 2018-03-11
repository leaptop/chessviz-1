#include "board_print_html.h"

#include "funcs.h"
#include "board.h"

#include <stdlib.h>
#include <stdio.h>

void PrintHtmlHead() {
    fprintf(outfile,
R"(<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>chessviz</title>
        <style type="text/css">
            table.chessboard {
                border: 5px solid #333;
                border-collapse: collapse;
                height: 320px;
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
            table.chessboard .wK:before { content: "\2654"; }
            table.chessboard .wQ:before { content: "\2655"; }
            table.chessboard .wR:before { content: "\2656"; }
            table.chessboard .wB:before { content: "\2657"; }
            table.chessboard .wN:before { content: "\2658"; }
            table.chessboard .wP:before { content: "\2659"; }
            table.chessboard .bk:before { content: "\265A"; }
            table.chessboard .bq:before { content: "\265B"; }
            table.chessboard .br:before { content: "\265C"; }
            table.chessboard .bb:before { content: "\265D"; }
            table.chessboard .bn:before { content: "\265E"; }
            table.chessboard .bp:before { content: "\265F"; }
        </style>
    </head>
    <body>
)");
}

void PrintHtmlBottom() {
    fprintf(outfile,R"(
    </body>
</html>)");
}

void PrintBoardHtml(int last) {
  fprintf(outfile,"        ");
  if (html_page-2>=0) {
    fprintf(outfile,"<a href=\"output_%d.html\">Prev</a>",html_page-2);
    if (!last) fprintf(outfile,"|");
  }
  if (!last) {
    fprintf(outfile,"<a href=\"output_%d.html\">Next</a>",html_page);
  }
  fprintf(outfile,"\n");
  fprintf(outfile,R"(        <table class="chessboard"> )");
  PrintLog();
  for (int i=7;i>=0;i--) {
    fprintf(outfile,"            <tr>\n");
    for (int j=7;j>=0;j--) {
        char tmp[2];
        tmp[0] = ' ';
        tmp[1] = board[j][i];
        if (tmp[1]>='A' && tmp[1]<='Z') {
            tmp[0] = 'w';
        } else if (tmp[1]>='a' && tmp[1]<='z') {
            tmp[0] = 'b';
        }
        if (tmp[0]!=' ') fprintf(outfile,
            "                <td><span class=%s></span></td>\n",tmp);
        else fprintf(outfile,
            "                <td></td>\n");
    }
    fprintf(outfile,"            </tr>\n");
  }
  fprintf(outfile,"        </table>");
}
