import sys
import json

d = json.load(sys.stdin)
DT = d['stdout_eval']
DR = d['stdout_gold']

check = DT == DR

# Special treatment for t05 (ugly solution. To be modified next year).
if DR == """MHPL ILAFVGAAAVAFPSDY
MNPLLILTFV AALAAF DDI
=R==I==R==D==RR==DR=R
""":
    DT = DT.split("\n")

    # Is the output well-formed?
    assert(len(DT) == 4)

    src, dest, ops, _ = DT

    # The number of edit operations should be 9.
    assert(len(list(filter(lambda x: x!="=", ops))) == 9)
    
    src = src.ljust(len(ops))
    dest = dest.ljust(len(ops))

    for i in range(len(ops)):
        judge = False

        if ops[i] == "=" and src[i] == dest[i]:
            judge = True
            
        if ops[i] == "D" and src[i] != " " and dest[i] == " ":
            judge = True
            
        if ops[i] == "I" and src[i] == " " and dest[i] != " ":
            judge = True
            
        if ops[i] == "R" and src[i] != " " and dest[i] != " " and src[i] != dest[i]:
            judge = True

        if not judge:
            sys.exit(1)

    sys.exit(0)
    
sys.exit(0 if check else 1)
