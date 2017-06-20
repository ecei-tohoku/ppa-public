import sys
import json

d = json.load(sys.stdin)
DT = d['stdout_eval']
DR = d['stdout_gold']

check = DT == DR

#
# Special treatment for t05 (ugly solution. To be modified next year).
if DR == """MHPL ILAFVGAAAVAFPSDY
MNPLLILTFV AALAAF DDI
=R==I==R==D==RR==DR=R
""":
    DR2 = """MHP LILAFVGAAAVAFPSDY
MNPLLILTFV AALAAF DDI
=R=I===R==D==RR==DR=R
"""
    check |= DT == DR2

sys.exit(0 if check else 1)
