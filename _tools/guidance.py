# -*- coding: utf-8 -*-

import sys
import os

TITLE = 'プログラミング演習Ａ（2016年・３セメ）'

def read_markdown(fi):
    header = 0
    content = ''
    for line in fi:
        line = line.strip('\r\n')
        if line == '---':
            header += 1
            continue
        # Skip header lines.
        if header % 2 == 1:
            continue

        # Skip style declarations.
        if line.startswith('{: '):
            continue
        content += line + '\n'

    return content

if __name__ == '__main__':
    content  = '---\n'
    content += 'layout: page\n'
    content += 'title: {}\n'.format(TITLE)
    content += '---\n'
    content += '\n'
    content += read_markdown(open('../about.md'))
    content += '\n'
    content += '## 日程\n'
    content += read_markdown(open('../schedule.md'))
    content += '\n'
    content += """
※ １号館別館１階大演習室は，夜間（22:00-7:00）及び休日の入室が可能です．
入館する際は，別館１階東側（１号館側）のドア右側に設置されているカードリーダーに学生証を読み取らせて入館してください．
夜間・休日に入館ができるのは，１号館別館１階（大演習室があるフロア）のみです．それ以外の部分には立ち入らないでください（ただし，女子学生のみ別館２階の女子トイレまでの立ち入りを許可します）．
"""
    with open('../guidance.md', 'w') as fo:
        fo.write(content)
