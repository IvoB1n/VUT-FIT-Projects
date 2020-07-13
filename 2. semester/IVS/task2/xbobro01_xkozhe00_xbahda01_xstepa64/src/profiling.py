from mathlib import MathLib as m

s = list(map(int, input().split()))
n = len(s)

std_deviation = m.root_n(m.div(m.a_sum(m.pow_x_y((m.sub(x,m.div(m.a_sum(s),n))),2) for x in s),(m.sub(n,1))),2)

print(std_deviation)