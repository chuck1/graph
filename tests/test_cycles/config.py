import pbs2

e = pbs2.Executable(self, "test_cycles", __file__)

e.add_dep("graph")

#e.args.append('--no-pie')
#e.args.append('-fPIC')
e.args.args.append('-lglpk')

self.parts.append(e)

