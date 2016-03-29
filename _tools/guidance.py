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
    with open('../guidance.md', 'w') as fo:
        fo.write(content)
